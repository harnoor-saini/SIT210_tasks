#include <Wire.h>
#include <BH1750.h>
#include "DHT.h"
#include <WiFiNINA.h>
#include "secrets.h"
#include "ThingSpeak.h"

//DHT22
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

//BH1750
BH1750 lightMeter;

//WiFi
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient client;

//ThingSpeak
unsigned long myChannelNumber = SECRET_CH_ID;
const char *myWriteAPIKey = SECRET_WRITE_APIKEY;


//SETUP
void setup() {

  Serial.begin(115200);

  while (!Serial) {
    ;
  }

  //Start I2C
  Wire.begin();

  //Start DHT22
  dht.begin();

  //Start BH1750
  if (lightMeter.begin()) {
    Serial.println("BH1750 started successfully.");
  }
  else {
    Serial.println("Error starting BH1750.");
  }

  //Start ThingSpeak
  ThingSpeak.begin(client);

  Serial.println("System ready.");
}

//CONNECT TO WIFI
void connectWiFi() {

  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  Serial.print("Connecting to WiFi: ");
  Serial.println(SECRET_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    WiFi.begin(ssid, pass);

    Serial.print(".");

    delay(5000);
  }

  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

//READ SENSORS
void readSensors() {

  //Read DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  //Read BH1750
  float lux = lightMeter.readLightLevel();

  //Check DHT readings
  if (isnan(humidity) || isnan(temperature)) {

    Serial.println("Failed to read from DHT22 sensor!");

    return;
  }

  //Display sensor readings
  Serial.println("-----------------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  Serial.println("-----------------------------");


  //ThingSpeak fields

  //Field 1 = Humidity
  ThingSpeak.setField(1,humidity);

  //Field 2 = Temperature
  ThingSpeak.setField(2,temperature);

  //Field 3 = Light intensity
  ThingSpeak.setField(3,lux);


  //Upload data
  int response = ThingSpeak.writeFields(
    myChannelNumber,
    myWriteAPIKey
  );

  if (response == 200) {

    Serial.println("ThingSpeak update successful.");

  }
  else {

    Serial.print("ThingSpeak update failed. HTTP error code: ");
    Serial.println(response);
  }
}

//LOOP
void loop() {

  //Make sure WiFi is connected
  connectWiFi();

  //Read sensors and upload values
  readSensors();

  //ThingSpeak requires at least 30 seconds
  //between channel updates
  delay(30000);
}