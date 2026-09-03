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

| Component | Arduino Pin |
| Ultrasonic TRIG | D4 |
| Ultrasonic ECHO | D7 |
| LED 1 | D2 |
| LED 2 | D3 |

## MQTT Configuration

The system uses the EMQX public MQTT broker.

- **Broker:** `broker.emqx.io`
- **Port:** `1883`

### MQTT Topics

| Gesture | Topic | Action |
| Wave | `ES/Wave` | Both LEDs turn ON |
| Pat | `ES/Pat` | Both LEDs turn OFF |

## MQTT Communication

The Arduino acts as both an MQTT publisher and subscriber.

### Publisher

When a gesture is detected, the Arduino publishes a message to the corresponding MQTT topic.

For example:

```text
ES/Wave → Harnoor - Wave detected
ES/Pat  → Harnoor - Pat detected
```
