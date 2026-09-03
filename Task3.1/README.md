# SIT210 Task 3.2C – MQTT

## Overview

This project implements an MQTT-based gesture-controlled lighting system using an Arduino Nano 33 IoT.

An ultrasonic sensor is used to detect two hand gestures:

- **Wave:** Hand detected between 10 cm and 30 cm.
- **Pat:** Hand detected less than 10 cm from the sensor.

The detected gesture is published using MQTT and is used to control two LEDs.

## Hardware

The system uses:

- Arduino Nano 33 IoT
- Ultrasonic sensor
- Two LEDs
- Resistors
- Breadboard
- Jumper wires

### Pin Connections

| Component       | Arduino Pin |
| --------------- | ----------- |
| Ultrasonic TRIG | D4          |
| Ultrasonic ECHO | D7          |
| LED 1           | D2          |
| LED 2           | D3          |

## MQTT Configuration

The system uses the EMQX public MQTT broker.

- **Broker:** `broker.emqx.io`
- **Port:** `1883`

### MQTT Topics

| Gesture | Topic     | Action             |
| ------- | --------- | ------------------ |
| Wave    | `ES/Wave` | Both LEDs turn ON  |
| Pat     | `ES/Pat`  | Both LEDs turn OFF |

## MQTT Communication

The Arduino acts as both an MQTT publisher and subscriber.

### Publisher

When a gesture is detected, the Arduino publishes a message to the corresponding MQTT topic.

For example:

```text
ES/Wave → Harnoor - Wave detected
ES/Pat  → Harnoor - Pat detected
```

### Subscriber

The Arduino also subscribes to the same topics (`ES/Wave` and `ES/Pat`). When a message arrives on either topic, the corresponding LED action is triggered — this allows the LEDs to be controlled locally by the sensor and remotely by anyone publishing to the same topics on the broker.

## How It Works

1. The ultrasonic sensor continuously measures distance by sending a pulse via TRIG and timing the echo received on ECHO.
2. The measured distance is checked against the gesture ranges:
   - Distance < 10 cm → **Pat**
   - 10 cm ≤ Distance ≤ 30 cm → **Wave**
3. On detecting a gesture, the Arduino publishes the corresponding message to `ES/Wave` or `ES/Pat`.
4. The Arduino's MQTT subscriber callback receives the message and updates the LED state accordingly:
   - Wave → both LEDs ON
   - Pat → both LEDs OFF

## Testing

- Verified distance readings via Serial Monitor across the Wave and Pat ranges.
- Verified MQTT messages published to `ES/Wave` and `ES/Pat` are received on the EMQX broker (checked via MQTT Explorer / MQTTX).
- Verified LEDs respond correctly to both locally detected gestures and externally published MQTT messages on the same topics.
