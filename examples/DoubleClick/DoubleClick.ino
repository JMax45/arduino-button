#include <ArduinoButton.h>

#define BUTTON_PIN 7

ArduinoButton button(BUTTON_PIN);

void setup() {
  Serial.begin(9600);
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