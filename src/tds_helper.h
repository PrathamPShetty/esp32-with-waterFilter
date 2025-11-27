#ifndef TDS_HELPER_H
#define TDS_HELPER_H

void initTDS();
float readTDS();

#endif


// | TDS Sensor Pin | ESP32 Pin     | Notes                        |
// | -------------- | ------------- | ---------------------------- |
// | VCC            | 3.3V or 5V    | Check your sensor spec       |
// | GND            | GND           | Common ground                |
// | SIG / Analog   | GPIO 34 (ADC) | Any analog-capable pin       |
// | (Optional) D0  | Digital GPIO  | Not used if only analog read |
