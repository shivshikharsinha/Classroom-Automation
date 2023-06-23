
#include "DHT.h"
#define DHTPIN D2
#define DHTTYPE DHT11

#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>

DHT dht(DHTPIN, DHTTYPE);

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "NIET"
#define WIFI_PASSWORD "12345678"
#define FIREBASE_HOST "revamp1-7b80b-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "1EvC6Vj1GdEadXRePfIag9rsL4zncgfDcmmTL5NR"
int led1 = D0;
int led2 = D1;
// Insert Firebase project API Key
#define API_KEY "AIzaSyAmSzHFEtqcPKy6f3oh8ZJ4hMdQ14NvtWo"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "dht11-2023-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseData firebaseData;
FirebaseData ledData;
FirebaseData led2Data;
FirebaseJson json;
FirebaseAuth auth;
FirebaseConfig config;

//unsigned long sendDataPrevMillis = 0;
//int count = 0;
bool signupOK = false;

void setup() {
  pinMode(DHTPIN, INPUT);
  dht.begin();
  Serial.begin(115200);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  delay(1000);
  float h = dht.readHumidity();

  float t = dht.readTemperature();

  if (Firebase.ready() && signupOK ) {

    if (Firebase.RTDB.setFloat(&fbdo, "DHT/humidity", h)) {
      //      Serial.println("PASSED");
      Serial.print("Humidity: ");
      Serial.println(h);

    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "DHT/temperature", t)) {
      //      Serial.println("PASSED");
      Serial.print("Temperature: ");
      Serial.println(t);
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
  Serial.println("______________________________");
   if (Firebase.getString(ledData, "/FirebaseIOT/led1")){
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
      
        digitalWrite(led1, HIGH);
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(led1, LOW);
    }
  } 
  delay(100);
  
  if (Firebase.getString(led2Data, "/FirebaseIOT/led2")){
    Serial.println(led2Data.stringData());
    if (led2Data.stringData() == "1") {
    digitalWrite(led2, HIGH);
    
    }
  else if (led2Data.stringData() == "0"){
    digitalWrite(led2, LOW);
    }
  }
  delay(100);
}
