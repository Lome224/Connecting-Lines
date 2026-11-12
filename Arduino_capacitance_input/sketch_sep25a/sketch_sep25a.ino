#include <Adafruit_CircuitPlayground.h>

// --- Timer variables ---
// Store the time when the last "reset" occurred
unsigned long previousMillis = 0;
// Set the interval: 60 seconds * 1000 milliseconds/second = 60000 milliseconds
const long interval = 60000;
// Define variables to store the raw values of the capacitive sensors

int rawSensor0;  // Corresponds to pin 9
int rawSensor1;  // Corresponds to pin 2
int rawSensor2;  // Corresponds to pin 12
int rawSensor3;  // Corresponds to pin 0

// Define the capacitive sensor pins
int capacitancePin0 = 9;
int capacitancePin1 = 2;
int capacitancePin2 = 12;
int capacitancePin3 = 0;

void setup() {
  // Start serial communication at 9600 baud
  Serial.begin(9600);

  // Initialize CircuitPlayground
  CircuitPlayground.begin();

  Serial.println("--- CircuitPlayground Started ---");

    // Record the start time immediately
    previousMillis = millis();
}

void loop() {
// 1. **Timer check**
  unsigned long currentMillis = millis();

  // Check whether the specified interval has elapsed
  if (currentMillis - previousMillis >= interval) {
    // Record the current time as the starting point for the next reset
    previousMillis = currentMillis;

    //  Run once-per-minute "reset" or refresh code 
    
    // Example: Print a message
    Serial.println(); // Print a blank line to separate the data
    Serial.println(">>> 60 seconds have passed. Performing 'reset' logic now.");
    Serial.println();
  }

  // 1. Read the raw values from all sensors 
  rawSensor0 = CircuitPlayground.readCap(capacitancePin0);
  rawSensor1 = CircuitPlayground.readCap(capacitancePin1);
  rawSensor2 = CircuitPlayground.readCap(capacitancePin2);
  rawSensor3 = CircuitPlayground.readCap(capacitancePin3);

  // --- 2. Print all raw sensor values to the serial port ---
  Serial.print(rawSensor0);
  Serial.print(",");  // Separator
  Serial.print(rawSensor1);
  Serial.print(",");
  Serial.print(rawSensor2);
  Serial.print(",");
  Serial.print(rawSensor3);
  Serial.println();
  // --- 3. Add a delay to limit the reading rate and keep serial output readable ---
  delay(100);
}
