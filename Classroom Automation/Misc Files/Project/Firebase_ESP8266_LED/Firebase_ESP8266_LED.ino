
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "smarthomeautomation-ec90d-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5sYWfUyPz3d0crdjxiNUfndpM3VI8cbDjD2vNG9e"
#define WIFI_SSID "Shiv's realme 8"
#define WIFI_PASSWORD "12345678"

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
//  pinMode(led,OUTPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("led", 0);
}
int ledDb;
void loop(){
  ledDb= Firebase.getInt("led");
  if (ledDb==1){
    digitalWrite(5, HIGH);
    }
  else{
     digitalWrite(5, LOW);
    }


//  sensorUpdate();
  
//  if (Firebase.getString(ledData, "/FirebaseIOT/led")){
//    Serial.println(ledData.stringData());
//    if (ledData.stringData() == "1") {
//    digitalWrite(led, HIGH);
//    }
//  else if (ledData.stringData() == "0"){
//    digitalWrite(led, LOW);
//    }
//  }
//  delay(100);
}
