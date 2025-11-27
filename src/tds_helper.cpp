#include "tds_helper.h"
#include <Arduino.h>

// ---- TDS Sensor Pin ----
const int tdsPin = 35; // Connect TDS analog output to GPIO 35 (ADC1)

// Calibration / conversion factor
const float VREF = 3.3;       // ESP32 ADC reference voltage
const float ADC_RESOLUTION = 4095.0; // 12-bit ADC

void initTDS() {
  analogReadResolution(12); // 12-bit ADC
  pinMode(tdsPin, INPUT);
}

// Read TDS value in ppm
float readTDS() {
  int analogValue = analogRead(tdsPin);
  float voltage = analogValue * (VREF / ADC_RESOLUTION);

  // Convert voltage to TDS (ppm)
  // Formula depends on your sensor; typical:
  // TDS(ppm) = (133.42 * V^3 - 255.86 * V^2 + 857.39 * V) * 0.5
  float tdsValue = (133.42 * voltage * voltage * voltage
                    - 255.86 * voltage * voltage
                    + 857.39 * voltage) * 0.5;

  return tdsValue;
}
