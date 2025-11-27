#include <Arduino.h>
#include <HTTPClient.h>

#include "wifi_helper.h"
#include "DSHelper.h"

// ---- WiFi ----
const char* ssid = "PRATHAM";
const char* password = "pratham99";

// ---- API URL ----
String serverURL = "http://192.168.31.255:3000/temp";

void setup() {
  Serial.begin(115200);

  connectWiFi(ssid, password);
  initSensor();
}

void loop() {
  float tempC = readTemperatureC();
  float tempF = readTemperatureF();

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");

  Serial.print("Temperature: ");
  Serial.print(tempF);
  Serial.println(" °F");

  Serial.println("--------------------------");

  // SEND DATA
  if (isWiFiConnected()) {
    HTTPClient http;

    String url = serverURL + "?tempC=" + String(tempC) + "&tempF=" + String(tempF);

    http.begin(url);
    int code = http.GET();

    Serial.print("HTTP Response Code: ");
    Serial.println(code);

    if (code > 0)
      Serial.println(http.getString());

    http.end();
  } else {
    Serial.println("⚠ WiFi Not Connected!");
  }

  delay(5000);
}
