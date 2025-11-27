#ifndef DISPLAY_HELPER_H
#define DISPLAY_HELPER_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Function declarations
void initDisplay();
void showStartingScreen();
void showTDS(float tdsValue);
void showMessage(String msg);
void showTemperature(float tempC, float tempF);
void showFlow(float flowRate, float totalLiters);
void showWaterLevel(String levelMessage);

#endif


// | OLED Pin            | Connect To ESP32 Pin | Code Reference  |
// | ------------------- | -------------------- | --------------- |
// | **VCC**             | 3.3V                 | Power           |
// | **GND**             | GND                  | Ground          |
// | **D0 / SCK / CLK**  | **GPIO 18**          | `OLED_CLK 18`   |
// | **D1 / MOSI / SDA** | **GPIO 23**          | `OLED_MOSI 23`  |
// | **DC**              | **GPIO 14**          | `OLED_DC 14`    |
// | **CS**              | **GPIO 5**           | `OLED_CS 5`     |
// | **RES / RST**       | **GPIO 13**          | `OLED_RESET 13` |
