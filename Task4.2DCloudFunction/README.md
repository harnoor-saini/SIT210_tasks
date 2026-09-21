# Task 4.2D – Calling a Function from the Web

## Description

This project is developed for **Embedded Systems Development – Task 4.2D: Calling a Function from the Web**.

The task focuses on using a web interface to remotely control three lights connected to an Arduino Nano 33 IoT. The three LEDs represent the **Living Room, Bathroom and Closet** and can be controlled independently.

The system demonstrates communication between a web interface, backend server, cloud platform and embedded hardware.

## Task Requirements

The task requires:

- Three LEDs connected to separate Arduino digital pins.
- A web interface with controls for each light.
- Independent ON/OFF control of the three lights.
- An Arduino function that accepts the room name as a string argument.
- Communication between the web interface and Arduino.
- A demonstration of the complete system and data flow.
- Discussion of possible improvements using other technologies or libraries.

## Implementation

For this implementation, **Blynk Cloud** is used as the cloud communication layer.

The system follows this communication flow:

**Web Interface → JavaScript → Node.js Backend → Blynk Cloud → Arduino → LED**

### Hardware

- Arduino Nano 33 IoT
- 3 LEDs
- 3 Resistors
- Breadboard
- Jumper wires

### Pin Configuration

| Room        | Arduino Pin | Blynk Virtual Pin |
| ----------- | ----------- | ----------------- |
| Living Room | D2          | V0                |
| Bathroom    | D3          | V1                |
| Closet      | D4          | V2                |

### Technologies Used

- HTML
- CSS
- JavaScript
- Node.js
- Express
- Blynk Cloud
- Arduino IDE

## Project Files

```text
Task4.2DCloudFunction/
├── index.html
├── script.js
├── Task4.2DCloudFunction.ino
├── flowchart.png
├── README.md
├── .gitignore
│
└── backend/
    ├── server.js
    ├── package.json
    └── package-lock.json
```

## How It Works

The user selects a light using the web interface. JavaScript identifies the selected room and ON/OFF state and sends the request to the Node.js backend.

The backend sends the command to Blynk Cloud using the corresponding virtual pin. The Arduino receives the update and uses the `controlLight()` function to control the appropriate digital pin.

The physical LED then turns ON or OFF according to the user's selection.

## Setup

Install the backend dependencies:

```bash
npm install
```

Create a `.env` file inside the `backend` folder:

```text
BLYNK_AUTH_TOKEN=your_blynk_token
```

Upload the `.ino` file to the Arduino Nano 33 IoT and ensure that it is connected to Wi-Fi and Blynk Cloud.

Start the Node.js backend:

```bash
node server.js
```

The web interface can then be accessed through:

```text
http://localhost:3000
```

## Flowchart

The included `flowchart.png` shows the complete system communication:

**Carer → Web Interface → Node.js Backend → Blynk Cloud → Arduino + LED**

## Security

The Blynk authentication token is stored in the `.env` file and is not included in the GitHub repository.

The `.env` and `node_modules` folders are excluded using `.gitignore`.

**The Blynk authentication token must not be uploaded to GitHub.**

## Testing

The system was tested by controlling each LED through the web interface.

- Living Room ON/OFF — Passed
- Bathroom ON/OFF — Passed
- Closet ON/OFF — Passed
- Independent light control — Passed
- Web-to-Arduino communication — Passed
- Blynk virtual pin communication — Passed
