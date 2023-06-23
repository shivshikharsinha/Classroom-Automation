#include "FirebaseESP8266.h" 
#include <ESP8266WiFi.h>
//#include <DHT.h>    // Install DHT11 Library and Adafruit Unified Sensor Library
#define PROJECT_ID "revamp1-7b80b"
//#define PROJECT_ID "sca-project-niet"   


#define FIREBASE_HOST "revamp1-7b80b-default-rtdb.firebaseio.com/" 
//#define FIREBASE_HOST "sca-project-niet-default-rtdb.firebaseio.com"


#define FIREBASE_AUTH "1EvC6Vj1GdEadXRePfIag9rsL4zncgfDcmmTL5NR"
#define WIFI_SSID "NIET"
#define WIFI_PASSWORD "12345678"

//#define DHTPIN 2   
int led = D5;
   

//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;
//Firebase firebase("revamp1-7b80b");  


void setup()
{

  Serial.begin(9600);

//  dht.begin();
  pinMode(led,OUTPUT);
  
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


void loop() {
//  sensorUpdate();
  
  if (Firebase.getString(ledData, "/FirebaseIOT/led")){
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
    digitalWrite(led, HIGH);
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(led, LOW);
    }
  }
  delay(100);
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
