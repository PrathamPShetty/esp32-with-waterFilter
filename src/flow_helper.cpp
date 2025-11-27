#include "flow_helper.h"
#include <Arduino.h>

// --- Internal variables ---
static volatile unsigned long pulseCount = 0;
static unsigned long oldTime = 0;
static float totalLiters = 0;
static int sensorPin = 14; // default

// Interrupt function
void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

// Initialize the flow sensor
void initFlowSensor(int pin) {
  sensorPin = pin;
  pulseCount = 0;
  totalLiters = 0;
  oldTime = millis();

  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, RISING);

  Serial.println("Water Flow Sensor Initialized...");
}

// Call this every loop; returns current flow rate in L/min
float getFlowRate() {
  float flowRate = 0;

  if (millis() - oldTime > 1000) { // every 1 sec
    detachInterrupt(digitalPinToInterrupt(sensorPin));

    float frequency = pulseCount;        // pulses per second
    flowRate = frequency / 7.5;          // L/min (depends on sensor K-factor)

    float litersPerSecond = flowRate / 60.0;
    totalLiters += litersPerSecond;

    pulseCount = 0;
    oldTime = millis();

    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, RISING);
  }

  return flowRate;
}

// Returns cumulative liters since start
float getTotalLiters() {
  return totalLiters;
}
