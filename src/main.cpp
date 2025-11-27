#include <Arduino.h>
#include <HTTPClient.h>

#include "wifi_helper.h"
#include "DSHelper.h"
#include "tds_helper.h"
#include "flow_helper.h"
#include "float_helper.h"
#include "display_helper.h"
#include "current_helper.h"


const char* ssid = "PRATHAM";
const char* password = "pratham99";


String serverURL = "https://major-project-backend.envisionsit.com/temp";

String waterlevelMessage = ""; 

void setup() {
  Serial.begin(115200);

  connectWiFi(ssid, password);
  initSensor();
  initTDS();
  initFlowSensor(14);
  initFloatSwitch(5); 
  initDisplay();
  showStartingScreen();
  initCurrentSensor();
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

  float tdsValue = readTDS();
  Serial.print("TDS Value: ");
  Serial.print(tdsValue);
  Serial.println(" ppm");

  float flowRate = getFlowRate();
  float total = getTotalLiters();

  Serial.print("Flow Rate: "); Serial.print(flowRate); Serial.print(" L/min   |   Total: ");
  Serial.print(total); Serial.println(" L");

  if (isWaterLevelHigh()) {
    Serial.println("🚰 Water level reached (Float Switch CLOSED)");
    waterlevelMessage = "HIGH";
  } else {
    Serial.println("⬇️ Water level low (Float Switch OPEN)");
    waterlevelMessage = "LOW";
  }

    float currentA = readCurrent();
     Serial.print("Current: ");
  Serial.print(currentA, 3);
  Serial.println(" A");

  Serial.println("--------------------------");

  showTemperature(tempC, tempF);
  delay(2000);

  showTDS(tdsValue);
  delay(2000);

  showFlow(flowRate, total);
  delay(2000);

  showWaterLevel(waterlevelMessage);
  delay(2000);

  // SEND DATA
  if (isWiFiConnected()) {
    HTTPClient http;

    String url = serverURL + "?tempC=" + String(tempC)
                 + "&tempF=" + String(tempF)
                 + "&tds=" + String(tdsValue)
                 + "&flowRate=" + String(flowRate)
                 + "&totalLiters=" + String(total)
                 + "&waterlevel=" + waterlevelMessage
                 + "&currentA=" + String(currentA);

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
