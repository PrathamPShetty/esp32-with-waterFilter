#include "DSHelper.h"
#include <Arduino.h>

DSHelper::DSHelper(int pin) 
    : oneWire(pin), sensors(&oneWire) {}

void DSHelper::begin() {
    sensors.begin();
    count = sensors.getDeviceCount();
    Serial.print("Devices found: ");
    Serial.println(count);
}

int DSHelper::sensorCount() {
    return count;
}

bool DSHelper::getSensorAddress(uint8_t index, DeviceAddress &addr) {
    return sensors.getAddress(addr, index);
}

void DSHelper::requestTemps() {
    sensors.requestTemperatures();
}

float DSHelper::readTemp(const DeviceAddress &addr) {
    return sensors.getTempC(addr);
}

void DSHelper::printAddress(const DeviceAddress &addr) {
    for (uint8_t i = 0; i < 8; i++) {
        if (addr[i] < 16) Serial.print("0");
        Serial.print(addr[i], HEX);
    }
    Serial.println();
}
