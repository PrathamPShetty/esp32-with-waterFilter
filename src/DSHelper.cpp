#include "DSHelper.h"
#include <Arduino.h>

const int oneWireBus = 4;

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void initSensor() {
  sensors.begin();
}

float readTemperatureC() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

float readTemperatureF() {
  sensors.requestTemperatures();
  return sensors.getTempFByIndex(0);
}
