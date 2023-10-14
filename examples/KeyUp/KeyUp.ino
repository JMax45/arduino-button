#include <ArduinoButton.h>

#define BUTTON_PIN 7

ArduinoButton button(BUTTON_PIN);

void setup() {
  Serial.begin(9600);
  button.onKeyUp([]() {
    Serial.println("Button key up callback");
  });
}

void loop() {
  button.loop();
}