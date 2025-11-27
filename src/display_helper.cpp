#include "display_helper.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 14
#define OLED_CS 5
#define OLED_RESET 13

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC,
                         OLED_RESET, OLED_CS);

void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println("OLED init failed!");
    while (1);
  }
  display.clearDisplay();
  display.display();
}

void showStartingScreen() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("Starting...");
  display.display();
}

// ---------------------------------------------------------
// Show Temperature
// ---------------------------------------------------------
void showTemperature(float tempC, float tempF) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("TEMP SENSOR");

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print(tempC, 1); display.print("C");

  display.setCursor(0, 45);
  display.print(tempF, 1); display.print("F");

  display.display();
}

// ---------------------------------------------------------
// Show TDS
// ---------------------------------------------------------
void showTDS(float tdsValue) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("TDS LEVEL");

  display.setTextSize(2);
  display.setCursor(0, 25);
  display.print(tdsValue, 1);
  display.println(" ppm");

  display.display();
}

// ---------------------------------------------------------
// Show Flow Rate
// ---------------------------------------------------------
void showFlow(float flow, float total) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("FLOW SENSOR");

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print(flow, 1);
  display.println(" L/m");

  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Total: ");
  display.print(total, 1);
  display.print(" L");

  display.display();
}

// ---------------------------------------------------------
// Show Water Level
// ---------------------------------------------------------
void showWaterLevel(String status) {
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(10, 25);
  display.print("LEVEL: ");
  display.println(status);

  display.display();
}
