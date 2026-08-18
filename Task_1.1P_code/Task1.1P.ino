/*
  Task 1.1P: Smart Lights for Linda
*/

const int PORCH_PIN = 16; //porch light
const int HALLWAY_PIN = 17; //halway light
const int BUTTON_PIN = 3; //button to toggle 

//time initialized
int porchTimeLeft = 0; 
int hallwayTimeLeft = 0;

void setup() {
  Serial.begin(9600);
  delay(500);

  pinMode(PORCH_PIN, OUTPUT);
  pinMode(HALLWAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  digitalWrite(PORCH_PIN, LOW);
  digitalWrite(HALLWAY_PIN, LOW);
  
  Serial.println("System initialized");
}

void loop() {
  //reads current state
  readButton();
  //updates time based on current states
  updateTimers();
  //updates the states of led's
  updateLEDs();
  delay(100);
}

//reads the state of button
void readButton() {
  int buttonState = digitalRead(BUTTON_PIN);
  //if the button is off i.e. it is not pressed/clicked
  if (buttonState == LOW) {
    //set initial times
    porchTimeLeft = 300;
    hallwayTimeLeft = 600;
    Serial.println("Button pressed - lights on");
  }
}

//time is left i.e. greater than zero reduce by 1s
void updateTimers() {
  if (porchTimeLeft > 0) {
    porchTimeLeft--;
  }
  
  if (hallwayTimeLeft > 0) {
    hallwayTimeLeft--;
  }
} 

//update the led's based on the time left
void updateLEDs() {
  if (porchTimeLeft > 0) {
    digitalWrite(PORCH_PIN, HIGH);
  } else {
    digitalWrite(PORCH_PIN, LOW);
  }
  
  if (hallwayTimeLeft > 0) {
    digitalWrite(HALLWAY_PIN, HIGH);
  } else {
    digitalWrite(HALLWAY_PIN, LOW);
  }
}