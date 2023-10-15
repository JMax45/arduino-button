#include <ArduinoButton.h>

#define BUTTON_PIN 6

// This example uses the internal pull-up resistor in the Arduino
ArduinoButton button(BUTTON_PIN, true);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  button.onDoubleClick([]() {
    Serial.println("Button double click callback");
  });

  /*
  Custom delay between clicks (in this case 1000ms):

  button.onDoubleClick([]() {
    Serial.println("Button key up click callback");
  }, 1000);
  */
}

void loop() {
  button.loop();
}