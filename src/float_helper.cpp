#include "float_helper.h"
#include <Arduino.h>

static int floatPin = 5;

// Initialize float switch pin
void initFloatSwitch(int pin) {
  floatPin = pin;
  pinMode(floatPin, INPUT_PULLUP);
  Serial.println("Float Switch Initialized...");
}

// Returns true if float is UP (water level reached)
bool isWaterLevelHigh() {
  return digitalRead(floatPin) == HIGH; // HIGH = float down → water low, LOW = float up
}

// Returns true if float is DOWN (water level low)
bool isWaterLevelLow() {
  return digitalRead(floatPin) == LOW; // LOW = float up → water high
}
