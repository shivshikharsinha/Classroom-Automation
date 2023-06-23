#include <Firebase.h>
//#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>

// Set these to run example.
#define FIREBASE_HOST "revamp1-7b80b-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "1EvC6Vj1GdEadXRePfIag9rsL4zncgfDcmmTL5NR"
#define WIFI_SSID "NIET"
#define WIFI_PASSWORD "12345678"

void setup() {
  Serial.begin(9600);

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
  pinMode(D1, OUTPUT);
  Firebase.set("LED_STATUS", 0);
}

int n = 0;

void loop() {
  // set value
  n = Firebase.getInt("LED_STATUS");
  // handle error
  if (n == 1) {
    Serial.print("LED is ON");
    digitalWrite(D1, HIGH);
    Serial.println(Firebase.error());
    return;
    delay(100);
  }
  else {
    Serial.print("LED is OFF");
    digitalWrite(D1, LOW);
  }

  // update value

}
