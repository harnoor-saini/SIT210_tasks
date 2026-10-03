# House Lights Controller

A simple Python application that lets users control room lights through a graphical interface using a Raspberry Pi.

## Description

House Lights Controller is a small project built to make controlling room lights easier without relying on physical switches. It uses Python and Tkinter to provide a simple interface where users can select which room's light they want to turn on.

The application connects three LEDs to the Raspberry Pi's GPIO pins, with each LED representing a different room: the living room, bathroom, and closet. Only one light can be turned on at a time.

## Technologies Used

- **Python** – Handles the application logic and controls the lights.
- **Tkinter** – Creates the graphical interface.
- **RPi.GPIO** – Allows Python to interact with the Raspberry Pi's GPIO pins.
- **Raspberry Pi** – Runs the application and controls the connected LEDs.

## Features

- Simple graphical interface for controlling room lights.
- Radio buttons for selecting between three rooms.
- GPIO-based control of individual LEDs.
- Automatically turns off the previous light when another room is selected.
- Exit button to close the application and clean up GPIO resources.

## Project Structure

```text
House-Lights-Controller/
│
├── main.py
└── README.md
```

### Prerequisites

Before running the application, make sure you have:

- A Raspberry Pi running Raspberry Pi OS.
- Python 3 installed.
- Tkinter and RPi.GPIO libraries.
- Three LEDs, 330Ω resistors, jumper wires, and a breadboard.

## Usage

### 1. Hardware Setup

Connect the three LEDs to the Raspberry Pi using the following GPIO pin configuration:

- **Living Room:** GPIO 17
- **Bathroom:** GPIO 27
- **Closet:** GPIO 22

Connect a 330Ω resistor in series with each LED and ensure that the circuit is properly connected to ground.

### 2. Run the Application

Open a terminal in the project directory and run:

```bash
python3 main.py
```

### 3. Control the Lights

Once the application opens:

- Select **Living Room** to turn on its corresponding LED.
- Select **Bathroom** to switch on the bathroom LED.
- Select **Closet** to turn on the closet LED.
- Selecting a different room automatically turns off the previously selected light.
- Click **Exit** to close the application and release the GPIO resources.
