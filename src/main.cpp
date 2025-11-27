#include <Arduino.h>
#include "DSHelper.h"

DSHelper ds(4);  // GPIO 4

DeviceAddress sensor1, sensor2;

void setup() {
  Serial.begin(115200);

  ds.begin();

  if (!ds.getSensorAddress(0, sensor1)) Serial.println("Sensor 1 not found!");
  if (!ds.getSensorAddress(1, sensor2)) Serial.println("Sensor 2 not found!");

  Serial.print("Sensor 1 Address: ");
  ds.printAddress(sensor1);

  Serial.print("Sensor 2 Address: ");
  ds.printAddress(sensor2);
}

void loop() {
  ds.requestTemps();

  float t1 = ds.readTemp(sensor1);
  float t2 = ds.readTemp(sensor2);

  Serial.print("Sensor 1: ");
  Serial.print(t1);
  Serial.println(" °C");

  Serial.print("Sensor 2: ");
  Serial.print(t2);
  Serial.println(" °C");

  Serial.println("----------------------");
  delay(2000);
}



