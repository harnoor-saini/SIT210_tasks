#include <Wire.h>
#include <BH1750.h>

#define PIR_PIN 11
#define PORCH_LED 3
#define HALLWAY_LED 2
#define BUTTON_PIN 10

BH1750 lightMeter;

volatile bool motionDetected = false;
volatile bool buttonPressed = false;

bool lightsOn = false;

// runs when motion is detected
void motionInterrupt() {
  motionDetected = true;
}

// runs when the button is pressed
void buttonInterrupt() {
  buttonPressed = true;
}

// turns both lights on
void turnLightsOn() {
  lightsOn = true;

  digitalWrite(PORCH_LED, HIGH);
  digitalWrite(HALLWAY_LED, HIGH);
}

// turns both lights off
void turnLightsOff() {
  lightsOn = false;

  digitalWrite(PORCH_LED, LOW);
  digitalWrite(HALLWAY_LED, LOW);
}

// checks the PIR sensor
void checkMotion() {

  if (motionDetected) {
    motionDetected = false;

    // read the current light level
    float lux = lightMeter.readLightLevel();

    Serial.println();
    Serial.println("Motion detected");

    Serial.print("Light level: ");
    Serial.print(lux);
    Serial.println(" lux");

    // turn lights on when light level is low
    if (lux < 600) {
      turnLightsOn();

      Serial.println("Lights: ON");
    } else {
      // turn lights off when light level is high
      turnLightsOff();

      Serial.println("Lights: OFF");
    }
  }
}

// checks the button
void checkButton() {

  if (buttonPressed) {
    buttonPressed = false;

    // read the current light level
    float lux = lightMeter.readLightLevel();

    // toggle the lights
    lightsOn = !lightsOn;

    digitalWrite(PORCH_LED, lightsOn);
    digitalWrite(HALLWAY_LED, lightsOn);

    Serial.println();
    Serial.println("Button pressed");

    Serial.print("Light level: ");
    Serial.print(lux);
    Serial.println(" lux");

    // print the current light state
    if (lightsOn) {
      Serial.println("Lights: ON");
    } else {
      Serial.println("Lights: OFF");
    }

    // small delay to prevent multiple button triggers
    delay(200);
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  // set the pins
  pinMode(PIR_PIN, INPUT);
  pinMode(PORCH_LED, OUTPUT);
  pinMode(HALLWAY_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // keep the lights off at the start
  turnLightsOff();

  // start I2C communication
  Wire.begin();

  // start the BH1750 sensor
  lightMeter.begin();

  // attach interrupt for PIR
  attachInterrupt(
    digitalPinToInterrupt(PIR_PIN),
    motionInterrupt,
    RISING);

  // attach interrupt for button
  attachInterrupt(
    digitalPinToInterrupt(BUTTON_PIN),
    buttonInterrupt,
    FALLING);

  Serial.println("Task 4.1P - Handling Interrupts");
  Serial.println("System ready");
  Serial.println("Waiting for motion or button press...");
}

void loop() {

  // check for motion
  checkMotion();

  // check for button press
  checkButton();
}