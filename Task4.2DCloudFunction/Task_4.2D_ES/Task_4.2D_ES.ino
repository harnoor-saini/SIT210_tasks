#define BLYNK_TEMPLATE_ID "TMPL327ojS8st"
#define BLYNK_TEMPLATE_NAME "Arduino Nano 33 Iot"
#define BLYNK_AUTH_TOKEN "L3HlVB0-6GT_6Q2htuY20U2weB59G7c1"


#define BLYNK_PRINT Serial

#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

char ssid[] = "Noor";
char pass[] = "123456789";

const int livingRoomLED = 2;
const int bathroomLED = 3;
const int closetLED = 4;

void controlLight(String room, bool state) {

  if (room == "living room") {
    digitalWrite(livingRoomLED, state ? HIGH : LOW);
  }

  else if (room == "bathroom") {
    digitalWrite(bathroomLED, state ? HIGH : LOW);
  }

  else if (room == "closet") {
    digitalWrite(closetLED, state ? HIGH : LOW);
  }
}

BLYNK_WRITE(V0) {
  controlLight("living room", param.asInt());
}

BLYNK_WRITE(V1) {
  controlLight("bathroom", param.asInt());
}

BLYNK_WRITE(V2) {
  controlLight("closet", param.asInt());
}

void setup() {
  Serial.begin(9600);

  pinMode(livingRoomLED, OUTPUT);
  pinMode(bathroomLED, OUTPUT);
  pinMode(closetLED, OUTPUT);

  digitalWrite(livingRoomLED, LOW);
  digitalWrite(bathroomLED, LOW);
  digitalWrite(closetLED, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
