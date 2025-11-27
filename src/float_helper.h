#ifndef FLOAT_HELPER_H
#define FLOAT_HELPER_H

void initFloatSwitch(int pin);
bool isWaterLevelHigh();  // Returns true if float is UP (water level reached)
bool isWaterLevelLow();   // Returns true if float is DOWN (water level low)

#endif


