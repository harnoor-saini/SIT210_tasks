# Task 2.1P: Sending Temperature and Light Data to the Web

## Overview

This project extends Task 1.1P by connecting an Arduino Nano 33 IoT to a DHT22 temperature/humidity sensor and a BH1750 light sensor. Sensor readings are pushed to the web using a webhook-based HTTP request via the ThingSpeak IoT platform, allowing room conditions to be monitored remotely through a simple web dashboard.

This solution supports Linda, who lives in an assisted living home, by giving her or her caregiver a way to check temperature and light levels in the room without needing to be physically present.

## Hardware Used

- Arduino Nano 33 IoT
- Breadboard and jumper wires
- DHT22 Temperature and Humidity Sensor
- BH1750 Digital Light Sensor

## Libraries Required

- `DHT sensor library` (Adafruit)
- `BH1750`
- `WiFiNINA`
- `ThingSpeak`

Install these via **Arduino IDE → Tools → Manage Libraries**.

## Circuit Connections

**DHT22**

- VCC → 5V
- GND → GND
- Data → D2

**BH1750** (I2C)

- VCC → 5V
- GND → GND
- SDA → SDA
- SCL → SCL

## How It Works

The Arduino reads temperature and humidity from the DHT22, and light intensity (lux) from the BH1750. These values are assigned to ThingSpeak fields and uploaded via `ThingSpeak.writeFields()`, which sends an HTTP POST request to the ThingSpeak server. This happens every 30 seconds, in line with ThingSpeak's minimum update interval.

**ThingSpeak Fields**

- Field 1 – Temperature (°C)
- Field 2 – Humidity (%)
- Field 3 – Light Intensity(lux)

## Code Structure (Modular Programming)

The code is split into independent functions, each handling a specific task:

- `setup()` – Initialises Serial, I2C, the DHT22, the BH1750, and ThingSpeak
- `connectWiFi()` – Connects to WiFi and reconnects only if the connection drops
- `readSensors()` – Reads sensor values and uploads them to ThingSpeak
- `loop()` – Runs the above functions every 30 seconds

## Notes

- `secrets.h` is excluded from version control to protect WiFi credentials and the ThingSpeak API key.
- The BH1750 was used instead of an analogue light sensor for more accurate lux readings via I2C.

## Author

Harnoor Saini – SIT210 Embedded Systems Development
