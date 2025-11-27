#include "wifi_helper.h"
#include <Arduino.h>

void connectWiFi(const char* ssid, const char* password) {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}
