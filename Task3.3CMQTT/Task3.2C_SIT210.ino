#include <WiFiNINA.h>
#include <PubSubClient.h>

// Wi-Fi
const char* ssid = "Redmi Note 11S";
const char* password = "123456789";

// MQTT
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;

const char* waveTopic = "ES/Wave";
const char* patTopic = "ES/Pat";

// Pins
const int trigPin = 4;
const int echoPin = 7;

const int Bathroom_LED = 2;
const int Hallway_LED = 3;

// Wi-Fi and MQTT
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Used to stop repeated detections
unsigned long lastGesture = 0;

void setup() {

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(Bathroom_LED, OUTPUT);
  pinMode(Hallway_LED, OUTPUT);

  digitalWrite(Bathroom_LED, LOW);
  digitalWrite(Hallway_LED, LOW);

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");

  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(2000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  // Connect to MQTT
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(messageReceived);

  connectMQTT();
}


void connectMQTT() {

  while (!mqttClient.connected()) {

    Serial.println("Connecting to MQTT...");

    if (mqttClient.connect("HarnoorArduino")) {

      Serial.println("MQTT connected!");

      mqttClient.subscribe(waveTopic);
      mqttClient.subscribe(patTopic);

      Serial.println("Subscribed to ES/Wave");
      Serial.println("Subscribed to ES/Pat");

    } else {

      Serial.println("MQTT connection failed");
      delay(5000);
    }
  }
}


// This runs when an MQTT message is received
void messageReceived(char* topic, byte* message, unsigned int length) {

  Serial.print("Message received: ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }

  Serial.println();


  // Wave = lights ON
  if (strcmp(topic, waveTopic) == 0) {

    digitalWrite(Bathroom_LED, HIGH);
    digitalWrite(Hallway_LED, HIGH);

    Serial.println("Wave received - LEDs ON");
  }


  // Pat = lights OFF
  if (strcmp(topic, patTopic) == 0) {

    digitalWrite(Bathroom_LED, LOW);
    digitalWrite(Hallway_LED, LOW);

    Serial.println("Pat received - LEDs OFF");
  }
}


// Get distance from ultrasonic sensor
float getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long time = pulseIn(echoPin, HIGH);

  float distance = time * 0.0343 / 2;

  return distance;
}


void loop() {

  // Make sure MQTT is connected
  if (!mqttClient.connected()) {
    connectMQTT();
  }

  mqttClient.loop();


  // Get distance
  float distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // Wait 2 seconds between gestures
  if (millis() - lastGesture > 2000) {

    // Wave
    if (distance >= 10 && distance <= 30) {

      Serial.println("WAVE detected");

      mqttClient.publish(
        waveTopic,
        "Harnoor - Wave detected");

      lastGesture = millis();
    }


    // Pat
    else if (distance > 0 && distance < 10) {

      Serial.println("PAT detected");

      mqttClient.publish(
        patTopic,
        "Harnoor - Pat detected");

      lastGesture = millis();
    }
  }

  delay(100);
}