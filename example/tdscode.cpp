
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// SPI OLED pins (GPIO numbers)
#define OLED_MOSI 23   // D23
#define OLED_CLK 18    // D18
#define OLED_DC 14     // D14
#define OLED_CS 5      // D5
#define OLED_RESET 13  // D13 or D17 depending on your board

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// -------- TDS Sensor Pin --------
#define TDS_PIN 32       // ADC pin (change to your actual analog pin)
float tdsValue = 0;

void setup() {
  Serial.begin(115200);
  delay(200);

  // OLED Init
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println("OLED NOT FOUND!");
    while (1) delay(10);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println("Starting...");
  display.display();

  delay(1000);
}

void loop() {

  // ----- READ TDS -----
  int adcValue = analogRead(TDS_PIN);        // Raw ADC
  float voltage = adcValue * (3.3 / 4095.0); // ESP32 ADC conversion

  // Simple TDS formula
  tdsValue = voltage * 500;                  // Adjust to your sensor calibration

  // ----- DEBUG -----
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | TDS: ");
  Serial.print(tdsValue, 1);
  Serial.println(" ppm");

  // ----- DISPLAY -----
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Water TDS Sensor");

  display.setTextSize(2);
  display.setCursor(0, 25);
  display.print("TDS:");
  display.print(tdsValue, 1);
  display.println("ppm");

  display.display();

  delay(1000); // update every second
}
