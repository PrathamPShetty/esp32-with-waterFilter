#ifndef CURRENT_HELPER_H
#define CURRENT_HELPER_H

#include <Arduino.h>

// ---- CONFIG ----
static const int CURRENT_SENSOR_PIN = 34;       // ESP32 ADC pin
static const float ACS712_ZERO_OFFSET = 2.5;    // Middle point voltage
static const float ACS712_SENSITIVITY = 0.185;  // For ACS712 5A model (185mV/A)
static const float ADC_VOLTAGE = 3.3;           // ESP32 ADC reference
static const int ADC_RESOLUTION = 4095;         // 12-bit ADC

// ---- INITIALIZATION ----
void initCurrentSensor() {
  pinMode(CURRENT_SENSOR_PIN, INPUT);
}

// ---- READ CURRENT ----
float readCurrent() {
  int raw = analogRead(CURRENT_SENSOR_PIN);

  float voltage = (raw / (float)ADC_RESOLUTION) * ADC_VOLTAGE;

  float current = (voltage - ACS712_ZERO_OFFSET) / ACS712_SENSITIVITY;

  return current; // in Amperes (A)
}

#endif


// | ACS712 Pin | ESP32             |
// | ---------- | ----------------- |
// | VCC        | 5V                |
// | GND        | GND               |
// | OUT        | GPIO 34 (ADC pin) |

