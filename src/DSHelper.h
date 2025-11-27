#ifndef DSHELPER_H
#define DSHELPER_H

#include <OneWire.h>
#include <DallasTemperature.h>

class DSHelper {
public:
    DSHelper(int pin);

    void begin();
    void printAddress(const DeviceAddress &addr);
    bool getSensorAddress(uint8_t index, DeviceAddress &addr);
    float readTemp(const DeviceAddress &addr);
    void requestTemps();
    int sensorCount();

private:
    OneWire oneWire;
    DallasTemperature sensors;
    int count;
};

#endif


// | DS18B20 Pin | Connect To     |
// | ----------- | -------------- |
// | GND         | GND            |
// | VCC         | 3.3V or 5V     |
// | DATA        | GPIO 4         |
// | DATA → VCC  | 4.7kΩ Resistor |