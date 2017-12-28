//Run with an adafruit Feather HUZZAH ESP8266

//Arduino Libraries
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//Firebase Access Settings
#define FIREBASE_HOST "XXXXXXX.firebaseio.com"
#define FIREBASE_AUTH "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" //Secret Access Key
//WIFI Access Settings
#define WIFI_SSID "XXXXXXX"
#define WIFI_PASSWORD "XXXXXXXXXXXX"

void setup() {

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connection");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("connecté: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

  if(Serial.available())
  {
    String reader = Serial.readString();
    String path = reader + "/n_entrees";
    String path2 = reader + "/entrees";
    int n_entrees = Firebase.getInt(path) + 1;

      StaticJsonBuffer<50> jsonBuffer;
      JsonObject& timeStampObject = jsonBuffer.createObject();
      timeStampObject[".sv"] = "timestamp";

      Firebase.setInt(path, n_entrees);
      Firebase.push(path2, timeStampObject);
  }

  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
  return;
  }
  
  delay(1000);
}
