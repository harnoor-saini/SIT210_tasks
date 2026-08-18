# Task 1.1P: Smart Lights for Elderly Care

**SIT210: Embedded Systems Development**

===

## **Overview**

Arduino Nano 33 IoT system that activates porch (30s) and hallway (60s) lights when button is pressed. Demonstrates modular programming with three independent functions.

===

## **Hardware**

- Arduino Nano 33 IoT
- Push button, 2 × Red LEDs, 2 × 330Ω resistors
- Breadboard, jumper wires

**Connections:**
- Pin 3 -> Button -> GND
- Pin 16 -> 330Ω -> Porch LED -> GND  
- Pin 17 -> 330Ω -> Hallway LED -> GND

===

## **Code Structure**

**readButton()** - Detects button press, starts timers (300 & 600 iterations)

**updateTimers()** - Decreases timers every loop (100ms delay = correct timing)

**updateLEDs()** - Controls LED pins based on timer values

===

## **How It Works**

1. Button press -> both timers start
2. Loop runs every 100ms, timers count down
3. Porch LED off at 30 sec, hallway at 60 sec
4. Button press during countdown resets timers

===

## **Testing**

1. Upload to Arduino (Board: Nano 33 IoT)
2. Open Serial Monitor (9600 baud)
3. Press button -> both LEDs light
4. At 30s -> porch LED off
5. At 60s -> hallway LED off

===

## **Why Modular?**

Each function does ONE thing: easy to read, test, and modify. 
Adding sensors or alerts doesn't require rewriting core code.

===

**Author:** Harnoor Saini 
**Semester:** 3, 2026