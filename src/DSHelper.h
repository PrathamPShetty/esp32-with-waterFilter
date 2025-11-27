#ifndef DSHELPER
#define DSHELPER
    
#include <OneWire.h>
#include <DallasTemperature.h>

void initSensor();
float readTemperatureC();
float readTemperatureF();

#endif


// | DS18B20 Pin | Connect To     |
// | ----------- | -------------- |
// | GND         | GND            |
// | VCC         | 3.3V or 5V     |
// | DATA        | GPIO 4         |
// | DATA → VCC  | 4.7kΩ Resistor |