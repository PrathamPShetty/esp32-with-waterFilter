#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include <WiFi.h>

void connectWiFi(const char* ssid, const char* password);
bool isWiFiConnected();

#endif
