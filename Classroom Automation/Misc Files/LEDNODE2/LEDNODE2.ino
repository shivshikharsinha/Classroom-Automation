//FirebaseESP8266.h must be included before ESP8266WiFi.h

#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
//#include <DHT.h>    // Install DHT11 Library and Adafruit Unified Sensor Library
//#define PROJECT_ID "revamp1-7b80b"   


#define FIREBASE_HOST "revamp1-7b80b-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "1EvC6Vj1GdEadXRePfIag9rsL4zncgfDcmmTL5NR"
#define WIFI_SSID "NIET"
#define WIFI_PASSWORD "12345678"

//#define DHTPIN D2   
int led1 = D0;
int led2 = D1; 

//#define DHTTYPE    DHT11
//DHT dht(DHTPIN, DHTTYPE);

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;
FirebaseData led2Data;

FirebaseJson json;
//Firebase firebase("revamp1-7b80b");  


void setup()
{

  Serial.begin(9600);

//  dht.begin();
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

//void sensorUpdate(){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//  float h = dht.readHumidity();
//  // Read temperature as Celsius (the default)
//  float t = dht.readTemperature();
//  // Read temperature as Fahrenheit (isFahrenheit = true)
//  float f = dht.readTemperature(true);
//
//  // Check if any reads failed and exit early (to try again).
//  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println(F("Failed to read from DHT sensor!"));
//    return;
//  }
//
//  Serial.print(F("Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%  Temperature: "));
//  Serial.print(t);
//  Serial.print(F("°C  ,"));
//  Serial.print(f);
//  Serial.println(F("°F  "));
//
//  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/temperature", t))
//  {
//    Serial.println("PASSED");
//    Serial.println("PATH: " + firebaseData.dataPath());
//    Serial.println("TYPE: " + firebaseData.dataType());
//    Serial.println("ETag: " + firebaseData.ETag());
//    Serial.println("------------------------------------");
//    Serial.println();
//  }
//  else
//  {
//    Serial.println("FAILED");
//    Serial.println("REASON: " + firebaseData.errorReason());
//    Serial.println("------------------------------------");
//    Serial.println();
//  }
//
//  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/humidity", h))
//  {
//    Serial.println("PASSED");
//    Serial.println("PATH: " + firebaseData.dataPath());
//    Serial.println("TYPE: " + firebaseData.dataType());
//    Serial.println("ETag: " + firebaseData.ETag());
//    Serial.println("------------------------------------");
//    Serial.println();
//  }
//  else
//  {
//    Serial.println("FAILED");
//    Serial.println("REASON: " + firebaseData.errorReason());
//    Serial.println("------------------------------------");
//    Serial.println();
//  }
//}
void loop() {
//  sensorUpdate();
  
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
