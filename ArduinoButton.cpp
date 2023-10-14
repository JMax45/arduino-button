/*
  ArduinoButton.cpp - Library for facilitating interfacing with buttons.

  Created by JMax, October 14, 2023.

  Released into the public domain.
*/

#include "Arduino.h"
#include "ArduinoButton.h"

ArduinoButton::ArduinoButton(int buttonPin) {
  setButtonPin(buttonPin);
  setCallback(NULL);
  setClickType(KEY_UP);
  prevState = digitalRead(buttonPin);
  setLastKeyDown(millis());
  setDoubleClickDelay(0);
  setDebounceDelay(20);
  setLastDebounceTime(millis());
}

void ArduinoButton::loop() {
  if(clickCallback == NULL) return;
  bool val = digitalRead(buttonPin);

  if(val != lastReading) {
    lastReading = val;
    setLastDebounceTime(millis());
    return;  
  }

  if(val == lastReading &&  millis() - lastDebounceTime >= debounceDelay) {
    switch(type) {
      case KEY_UP:
        if(val == LOW && prevState == HIGH) clickCallback();
        break;
      case KEY_DOWN:
        if(val == HIGH && prevState == LOW) clickCallback();
        break;
      case DOUBLE_CLICK:
        if(val == HIGH && prevState == LOW && millis() - lastKeyDown <= doubleClickDelay) clickCallback();
        else if(val == HIGH && prevState == LOW) lastKeyDown = millis();
        break;
      default:
        break;
    }
    prevState = val;
  }
  else return;
}

void ArduinoButton::onKeyUp(void (*cb)()) {
  setCallback(cb);
  setClickType(KEY_UP);
}

void ArduinoButton::onKeyDown(void (*cb)()) {
  setCallback(cb);
  setClickType(KEY_DOWN);
}

void ArduinoButton::onDoubleClick(void (*cb)(), int delay = 500) {
  setCallback(cb);
  setClickType(DOUBLE_CLICK);
  setDoubleClickDelay(delay);
}

void ArduinoButton::setButtonPin(int pin) {
  buttonPin = pin;  
}

void ArduinoButton::setClickType(clickType click_type) {
  type = click_type;
}

void ArduinoButton::setCallback(void (*cb)()) {
  clickCallback = cb;
}

void ArduinoButton::setLastKeyDown(unsigned long num) {
  lastKeyDown = num;
}

void ArduinoButton::setDoubleClickDelay(int delay) {
  doubleClickDelay = delay;  
}

void ArduinoButton::setDebounceDelay(int delay) {
  debounceDelay = delay;
}

void ArduinoButton::setLastDebounceTime(unsigned long time) {
  lastDebounceTime = time;
}
