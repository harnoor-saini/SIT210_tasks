#include <WiFiNINA.h>
#include <PubSubClient.h>

// Wi-Fi
const char* ssid = "Redmi Note 11S";
const char* password = "123456789";

// MQTT
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;

//Topic is the name used to identify where an MQTT message is sent
const char* waveTopic = "ES/Wave";
const char* patTopic = "ES/Pat";

const char* deviceName = "Harnoor";

// Pins
const int TRIG_PIN = 4;
const int ECHO_PIN = 7;

const int LED1_PIN = 2;
const int LED2_PIN = 3;

// WiFiClient is used to create the network connection
// PubSubClient is used to send and receive MQTT messages
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Stores the time when the last gesture was detected
unsigned long lastGestureTime = 0;

// Cooldown prevents the same gesture from being detected repeatedly
const unsigned long gestureCooldown = 2000;


// Connect to Wi-Fi
void connectWiFi() {

  Serial.print("Connecting to Wi-Fi");

  // Keep trying until Wi-Fi is connected
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.print(".");
    delay(2000);
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  // Print the IP address given to the Arduino
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


// This function runs when an MQTT message is received
// A callback is a function that runs automatically when an event happens
void mqttCallback(char* topic, byte* payload, unsigned int length) {

  String message = "";

  // Convert the received data into a readable string
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Print the received message
  Serial.print("Message received on ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message);


  // If a wave message is received turn the LEDs on
  if (strcmp(topic, waveTopic) == 0) {

    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);

    Serial.println("WAVE received - LEDs ON");
  }

  // If a pat message is received turn the LEDs off
  else if (strcmp(topic, patTopic) == 0) {

    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);

    Serial.println("PAT received - LEDs OFF");
  }
}


// Connect to the MQTT broker
void connectMQTT() {

  // Keep trying until MQTT is connected
  while (!mqttClient.connected()) {

    Serial.print("Connecting to MQTT broker...");

    // Create a random client ID for the Arduino
    // A client ID is a unique name used to identify an MQTT client
    String clientID = "ArduinoNano33IoT-";
    clientID += String(random(0xffff), HEX);

    if (mqttClient.connect(clientID.c_str())) {

      Serial.println("connected!");

      // Subscribe means the Arduino asks to receive
      // messages from these MQTT topics
      mqttClient.subscribe(waveTopic);
      mqttClient.subscribe(patTopic);

      Serial.println("Subscribed to:");
      Serial.println("ES/Wave");
      Serial.println("ES/Pat");
    }

    else {

      // Print the error if connection fails
      Serial.print("failed, state = ");
      Serial.println(mqttClient.state());

      // Wait before trying again
      delay(5000);
    }
  }
}


// Get the distance from the ultrasonic sensor
float getDistance() {

  // Make sure the trigger pin is LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a short ultrasonic pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // pulseIn measures how long the echo signal stays HIGH
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // Return -1 if no echo is received
  if (duration == 0) {
    return -1;
  }

  // Convert the echo time into distance in cm
  // 0.0343 is the speed of sound in cm per microsecond
  // Divide by 2 because the sound travels to the object and back
  float distance = duration * 0.0343 / 2;

  return distance;
}


// Setup function
void setup() {

  // Start Serial Monitor
  Serial.begin(9600);

  // Set ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set LED pins as outputs
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  // Start with both LEDs turned off
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  // Connect to Wi-Fi
  connectWiFi();

  // Set the MQTT broker and port
  mqttClient.setServer(mqttServer, mqttPort);

  // Set the callback function for received MQTT messages
  mqttClient.setCallback(mqttCallback);

  // Connect to MQTT
  connectMQTT();
}


// Main loop
void loop() {

  // Reconnect if MQTT connection is lost
  if (!mqttClient.connected()) {
    connectMQTT();
  }

  // Checks for incoming MQTT messages and keeps the MQTT connection active
  mqttClient.loop();

  // Get the current distance from the sensor
  float distance = getDistance();

  if (distance > 0) {

    // Print the distance on Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // millis() gives the time passed since the Arduino started
    // This checks if the cooldown time has passed
    if (millis() - lastGestureTime > gestureCooldown) {

      // Detect a wave when distance is between 10 and 30 cm
      if (distance >= 10 && distance <= 30) {

        Serial.println("WAVE detected");

        // Publish sends a message to the MQTT broker
        mqttClient.publish(waveTopic, "Wave Detected");

        // Save the time when the wave was detected
        lastGestureTime = millis();

        delay(300);
      }

      // Detect a pat when distance is less than 10 cm
      else if (distance > 0 && distance < 10) {

        Serial.println("PAT detected");

        // Publish the pat message to the MQTT broker
        mqttClient.publish(patTopic, "Pat Detected");

        // Save the time when the pat was detected
        lastGestureTime = millis();

        delay(300);
      }
    }
  }

  // Small delay before checking the sensor again
  delay(100);
}