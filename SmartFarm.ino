#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin Definitions
const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;

const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;

const int fan = 12;
const int SMS = A0;
const int LDR = A1;

// DHT Sensor setup
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// OLED display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Timing Variables
unsigned long lastBlinkTime = 0;
unsigned long lastSwitchTime = 0;
const unsigned long blinkInterval = 2000;
const unsigned long screenSwitchInterval = 5000;  // 5 seconds for screen switching

// Sensor Values
int SMS_sensorValue = 0;
int LDRValue = 0;
bool led3State = HIGH;
bool led1State = HIGH;

int screenMode = 0;  // 0: Sensor Text Display, 1: Graph Display

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Initialize relay pins and LEDs as outputs
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(fan, OUTPUT);

  // Set initial states
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.display();
}

// Non-blocking blink function for led1 and led3
void blinkingLed(int ledPin, bool &ledState) {
  if (millis() - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = millis();
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

// Relay control functions
void relayControl(int relayPin, bool state, int delayMs = 0) {
  if (delayMs > 0) delay(delayMs);
  digitalWrite(relayPin, state ? LOW : HIGH);  // LOW to turn ON, HIGH to turn OFF
}

// Function to display sensor values on the OLED screen
void displaySensorData(float temperature, float humidity, int moisturePercent, int lightPercent) {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.println(" ");

  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.println(" ");

  display.print("Soil Moist: ");
  display.print(moisturePercent);
  display.println(" %");

  display.println(" ");

  display.print("Light: ");
  display.print(lightPercent);
  display.println(" %");

  display.display();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print humidity and temperature
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\tTemperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Soil Moisture Sensor
  SMS_sensorValue = analogRead(SMS);
  int moisturePercent = map(SMS_sensorValue, 800, 400, 0, 100);
  Serial.print(SMS_sensorValue);
  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  if (moisturePercent < 20) {
    digitalWrite(led2, LOW);
    digitalWrite(relay3, LOW);
  } else if (moisturePercent > 60) {
    digitalWrite(led2, HIGH);
    digitalWrite(relay3, HIGH);
  }

  // Control led4 based on humidity and temperature
  digitalWrite(led4, (humidity < 76 && temperature < 33 && moisturePercent > 59) ? LOW : HIGH);

  // LED3 behavior based on humidity
  if (humidity > 70) {
    blinkingLed(led3, led3State);
  } else if (humidity < 20){
    digitalWrite(led3, LOW);
  } else {
    digitalWrite(led3, HIGH);
  }

  // Temperature and relay control
  if (temperature > 35) {
    blinkingLed(led1, led1State);
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    delay(2500);
    digitalWrite(relay1, LOW);
  } else if (temperature > 33) {
    digitalWrite(led1, LOW);
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    delay(2500);
  } else {
    digitalWrite(led1, HIGH);
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  }

  // Light Sensor (LDR)
  LDRValue = analogRead(LDR);
  int lightPercent = map(LDRValue, 1023, 0, 0, 100);
  Serial.print("Light: ");
  Serial.print(lightPercent);
  Serial.println("%");

  if (screenMode == 0) {
    displaySensorData(temperature, humidity, moisturePercent, lightPercent);
  } else {
    displaySensorData(temperature, humidity, moisturePercent, lightPercent);
  }

  // Small delay to avoid flooding the Serial Monitor
  delay(500);
}