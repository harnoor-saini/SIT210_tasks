# Smart Home Lighting Controller

A Python-based graphical interface for controlling room lights and adjusting LED brightness using a Raspberry Pi.

## Description

Smart Home Lighting Controller is a simple application that allows users to control the lights in three different rooms through a graphical interface. Built using Python and Tkinter, it provides an easy way to switch lights on and adjust the brightness of the living room light.

The system uses three LEDs connected to a Raspberry Pi. The living room light uses Pulse Width Modulation (PWM) to adjust its brightness, while the bathroom and closet lights use basic ON/OFF control.

## Technologies Used

- **Python** – Handles the application logic and light control.
- **Tkinter** – Provides the graphical user interface.
- **RPi.GPIO** – Manages the Raspberry Pi GPIO pins.
- **PWM** – Controls the brightness of the living room LED.
- **Raspberry Pi** – Runs the application and controls the connected LEDs.

## Features

- Simple graphical interface for controlling room lights.
- Individual controls for the living room, bathroom, and closet.
- Adjustable living room light intensity using a slider.
- PWM-based brightness control with a range of 0% to 100%.
- Automatic switching off of other lights when a different room is selected.
- Exit button to close the application and clean up GPIO resources.

## Project Structure

```text
Smart-Home-Lighting-Controller/
│
├── main.py
└── README.md
```

## Usage

### 1. Hardware Setup

Connect the three LEDs to the Raspberry Pi using the following GPIO pin configuration:

- **Living Room:** GPIO 18 (PWM)
- **Bathroom:** GPIO 27 (ON/OFF)
- **Closet:** GPIO 22 (ON/OFF)

Use a 330Ω resistor in series with each LED and ensure that the circuit is properly connected to ground.

### 2. Run the Application

Open a terminal in the project directory and run:

```bash
python3 main.py
```

### 3. Control the Lights

Once the application opens:

- Select **Living Room** to turn on its LED.
- Use the **Living Room Intensity** slider to adjust its brightness from 0% to 100%.
- Select **Bathroom** to turn on the bathroom LED and switch off the other lights.
- Select **Closet** to turn on the closet LED and switch off the other lights.
- Click **Exit** to close the application and release the GPIO resources.
