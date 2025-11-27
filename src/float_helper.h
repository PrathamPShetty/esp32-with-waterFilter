#ifndef FLOAT_HELPER_H
#define FLOAT_HELPER_H

void initFloatSwitch(int pin);
bool isWaterLevelHigh();  // Returns true if float is UP (water level reached)
bool isWaterLevelLow();   // Returns true if float is DOWN (water level low)

#endif


// | Sensor           | ESP32 Pin     | Notes                                                                   |
// | ---------------- | ------------- | ----------------------------------------------------------------------- |
// | **Float Switch** | GPIO5         | Use `INPUT_PULLUP`                                                      |
// | **3.3V / 5V**    | VCC           | Power supply for sensors (check each sensor’s rating)                   |
// | **GND**          | GND           | Common ground for all sensors                                           |
