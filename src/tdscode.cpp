#include <Arduino.h>

#include <esp32-hal-gpio.h>
const int floatSwitchPin = 5;

void setup() {
  Serial.begin(115200);

  // Configure pin as input with internal pull-up resistor
  pinMode(floatSwitchPin, INPUT_PULLUP);

  Serial.println("Float Switch Monitoring Started...");
}

void loop() {
  // Read the float switch state
  int sensorValue = digitalRead(floatSwitchPin);

  // Logic:
  // INPUT_PULLUP means pin stays HIGH until switch closes → becomes LOW.
  // LOW = Water level is HIGH (float up)
  // HIGH = Water level is LOW (float down)

  if (sensorValue == LOW) {
     Serial.println("⬇️ Water level low (Float Switch OPEN)");
    // TODO: Add your pump OFF / alert / relay action here
  } else {
   

    Serial.println("🚰 Water level reached (Float Switch CLOSED)");
    // TODO: Add your pump ON action here
  }

  delay(1000);  // Read every second
}
