# SIT210 Task 3.1P — Terrarium Sunlight Trigger & Notification System

## Overview
This project is part of **SIT210 (Embedded Systems Development) Task 3.1P**. It uses an **Arduino Nano 33 IoT** with a **BH1750 light sensor** to monitor sunlight exposure on a terrarium. When the light level crosses a defined threshold, the Arduino publishes a message over **MQTT** to a **HiveMQ Cloud** broker. A **Node-RED** flow subscribes to this MQTT topic and triggers an **email notification** (via Gmail) whenever the sunlight state changes.

This builds on the sensor setup from Task 2.1P, replacing the webhook/ThingSpeak logging with a real-time trigger-and-notify pipeline.

## How It Works
1. The BH1750 sensor continuously measures ambient light (in lux).
2. The Arduino compares the reading against `LUX_THRESHOLD` (500.0 lux).
3. On a state change (no sunlight → sunlight, or sunlight → no sunlight), it publishes a message to the MQTT topic `Harnoor/sunlight` on HiveMQ Cloud.
4. Node-RED, running on a PC, subscribes to that topic.
5. When Node-RED receives a "Sunlight detected" or "No sunlight detected" message, it sends an email notification via a connected Gmail account.

## Hardware
- Arduino Nano 33 IoT
- BH1750 ambient light sensor (I2C)
- Wiring: BH1750 connected via I2C (SDA/SCL) to the Nano 33 IoT

## Software / Tools
- Arduino IDE
- Libraries: `WiFiNINA`, `PubSubClient`, `Wire`, `BH1750`
- Node-RED (running locally on Windows, Node.js installed)
- HiveMQ Cloud (MQTT broker over TLS, port 8883)
- Gmail (for email notifications via Node-RED)

## Arduino Sketch
The main sketch (`sunlight_monitor.ino`) does the following:
- Connects to WiFi
- Connects to the HiveMQ broker over a secure (`WiFiSSLClient`) MQTT connection
- Reads lux values from the BH1750 every 5 seconds
- Publishes `"Sunlight detected"` or `"No sunlight detected"` to `Harnoor/sunlight` only on a state change (avoids repeated/spammy messages)

### Configuration
```cpp
#define WIFI_SSID     "Redmi Note 11S"
#define WIFI_PASSWORD "123456789"
#define MQTT_SERVER   "35b1c0e875f84667a0a523cce824af37.s1.eu.hivemq.cloud"
#define MQTT_USER     "Harnoor"
```

## Node-RED Flow
The Node-RED flow:
1. **MQTT In** node — subscribes to `Harnoor/sunlight` on the HiveMQ broker (TLS enabled, port 8883)
2. **Switch/Function** node — checks the payload string (`"Sunlight detected"` / `"No sunlight detected"`)
3. **Email (Gmail)** node — sends a notification email with the corresponding message

## Testing
- Verified via Serial Monitor that lux readings update correctly.
- Verified MQTT messages arrive at the HiveMQ broker (checked via HiveMQ Cloud console / MQTT Explorer).
- Verified Node-RED receives the message and triggers a Gmail notification on state change.
