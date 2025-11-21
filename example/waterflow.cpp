#include <Arduino.h>

const int flowSensorPin = 14;  // Yellow wire to GPIO14
volatile unsigned long pulseCount = 0;

unsigned long oldTime = 0;

void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);

  pinMode(flowSensorPin, INPUT_PULLUP);

  // Attach interrupt to count pulses
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, RISING);

  Serial.println("Water Flow Sensor Started...");
}

void loop() {
  if (millis() - oldTime > 1000) { // Update every 1 sec
    detachInterrupt(digitalPinToInterrupt(flowSensorPin));

    float frequency = pulseCount; // pulses per second
    float flowRate = frequency / 7.5; // L/min

    float litersPerSecond = flowRate / 60.0;
    static float totalLiters = 0;

    totalLiters += litersPerSecond;

    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.print(" L/min   |   Total: ");
    Serial.print(totalLiters);
    Serial.println(" L");

    pulseCount = 0;
    oldTime = millis();

    attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, RISING);
  }
}
