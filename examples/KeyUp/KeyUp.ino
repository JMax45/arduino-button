#include "ArduinoButton.h"

#define BUTTON_PIN 6

// This example uses the internal pull-up resistor in the Arduino
ArduinoButton button(BUTTON_PIN, true);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  button.onKeyUp([]() {
    Serial.println("Button key up callback");
  });
}

void loop() {
  button.loop();
}