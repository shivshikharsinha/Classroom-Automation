#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "revamp1-7b80b-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "1EvC6Vj1GdEadXRePfIag9rsL4zncgfDcmmTL5NR"
#define ssid "NIET"
#define password "12345678"

int RELAY_PIN = D0;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Serial.println("Connected to Firebase");
}

void loop() {
  int state = Firebase.getInt("bulbState");

  if (state == 1) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }
}
