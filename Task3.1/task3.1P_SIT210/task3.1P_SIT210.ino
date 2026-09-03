#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <BH1750.h>

// WiFi Credentials
#define WIFI_SSID "Redmi Note 11S"
#define WIFI_PASSWORD "123456789"

// MQTT Broker Credentials
#define MQTT_SERVER "35b1c0e875f84667a0a523cce824af37.s1.eu.hivemq.cloud"
#define MQTT_PORT 8883
#define MQTT_TOPIC "Harnoor/sunlight"
#define MQTT_USER "Harnoor"
#define MQTT_PASSWORD "123456789"

// Light Sensor Configuration
BH1750 lightMeter;
const float LUX_THRESHOLD = 500.0;

// Sunlight state tracker
int sunlightDetected = 0;

// Use SSL Client instead of regular WiFiClient
WiFiSSLClient wifiSSLClient;
PubSubClient mqttClient(wifiSSLClient);

// Function to Connect to MQTT Broker
void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    if (mqttClient.connect("ArduinoNanoIoT", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT Broker!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
void setup() {
  Serial.begin(9600);

  // Wait for Serial Monitor
  while (!Serial) {
    delay(100);
  }
  Serial.println();
  Serial.println("==============================");
  Serial.println("Terrarium Sunlight Monitor");
  Serial.println("==============================");

  // Start I2C communication and BH1750 sensor
  Wire.begin();
  lightMeter.begin();

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set MQTT Server
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);

  // Connect to MQTT
  connectMQTT();
}
void loop() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.loop(); // Keep MQTT connection alive
  // Read light level from BH1750
  float lux = lightMeter.readLightLevel();
  Serial.print("Lux: ");
  Serial.println(lux);
  
  // Detect sunlight
  if (lux > LUX_THRESHOLD && sunlightDetected == 0) {
    sunlightDetected = 1;
    Serial.println("SUNLIGHT DETECTED!");
    mqttClient.publish(MQTT_TOPIC, "Sunlight detected");
  } else if (lux <= LUX_THRESHOLD && sunlightDetected == 1) {
    sunlightDetected = 0;
    Serial.println("SUNLIGHT STOPPED!");
    mqttClient.publish(MQTT_TOPIC, "No sunlight detected");
  }
  delay(5000); // Send data every 5 seconds
}