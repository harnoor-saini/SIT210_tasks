# Task 4.1P – Handling Interrupts

## Overview

This project demonstrates the use of hardware interrupts with an Arduino Nano 33 IoT.

The system is designed to control two LEDs using a PIR motion sensor, a BH1750 light sensor and a push button. When motion is detected, the system checks the light intensity. If the environment is dark, both lights are turned on automatically.

The push button is used as a manual backup to toggle the lights when required.

## Hardware Used

- Arduino Nano 33 IoT
- PIR motion sensor
- BH1750 light sensor
- Push button
- 2 LEDs
- 2 × 330Ω resistors
- Breadboard
- Jumper wires

## Pin Connections

| Component   | Arduino Pin |
| ----------- | ----------- |
| PIR OUT     | D11         |
| Push Button | D10         |
| Porch LED   | D2          |
| Hallway LED | D3          |
| BH1750 SDA  | SDA         |
| BH1750 SCL  | SCL         |
| BH1750 VCC  | 5V          |
| BH1750 GND  | GND         |

The push button uses the Arduino's internal pull-up resistor, so the button is connected between D10 and GND.

Each LED is connected through a 330Ω resistor to protect the LED.

## How the System Works

The program uses two hardware interrupts.

### PIR Interrupt

The PIR sensor is connected to D11. When motion is detected, the PIR interrupt is triggered.

The program then reads the light level from the BH1750 sensor.

- If the light level is below the selected threshold, both LEDs are turned ON.
- If the light level is above the threshold, both LEDs are turned OFF.

### Button Interrupt

The push button is connected to D10.

When the button is pressed, its interrupt is triggered and the state of both LEDs is toggled. This provides a manual backup for controlling the lights.

## Interrupts

The program uses `attachInterrupt()` to connect the PIR and button inputs to their interrupt functions.

The interrupt functions only set flags. The main `loop()` checks these flags and performs the required processing.

This prevents sensor reading and LED control from being performed directly inside the interrupt service routines.

## Modular Programming

The program is divided into separate functions so that each function has a specific responsibility.

Some of the main functions are:

- `motionInterrupt()` – handles the PIR interrupt.
- `buttonInterrupt()` – handles the button interrupt.
- `checkMotion()` – processes the motion event and checks the light level.
- `checkButton()` – processes the button event.
- `turnLightsOn()` – turns both LEDs ON.
- `turnLightsOff()` – turns both LEDs OFF.

Using separate functions makes the program easier to understand, test and modify.

## BH1750 Light Sensor

The BH1750 sensor is used to measure the surrounding light intensity in lux.

The measured value is compared with the selected light threshold. This allows the system to determine whether the environment is dark or bright before automatically controlling the lights.

## Software Flow

```text
START
  ↓
Initialise Arduino and Sensors
  ↓
Attach Interrupts
  ↓
Enter Main Loop
  ↓
Check Interrupt Flags
  ↓
Motion Interrupt?
  ├── YES → Read BH1750
  │          ↓
  │       Is it dark?
  │        ├── YES → Lights ON
  │        └── NO  → Lights OFF
  │
  └── NO
  ↓
Button Interrupt?
  ├── YES → Toggle Lights
  └── NO
  ↓
Return to Main Loop
```
