#ifndef FLOW_HELPER_H
#define FLOW_HELPER_H

void initFlowSensor(int pin);
float getFlowRate();       // L/min
float getTotalLiters();    // cumulative L

#endif


// | Flow Sensor Wire | ESP32 Pin        | Notes                                             |
// | ---------------- | ---------------- | ------------------------------------------------- |
// | Red (VCC)        | 3.3V or 5V       | Check sensor voltage rating (YF-S201 supports 5V) |
// | Black (GND)      | GND              | Common ground with ESP32                          |
// | Yellow (Signal)  | GPIO14 (example) | Attach interrupt-capable pin                      |
