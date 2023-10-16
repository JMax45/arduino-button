/*
  ArduinoButton.cpp - Library for facilitating interfacing with buttons.

  Created by JMax, October 14, 2023.

  Released into the public domain.
*/

#include "Arduino.h"
#include "ArduinoButton.h"

ArduinoButton::ArduinoButton(int buttonPin, bool isActiveLow) {
  setButtonPin(buttonPin);
  keyUpCallback = NULL;
  keyDownCallback = NULL;
  doubleClickCallback = NULL;
  prevState = digitalRead(buttonPin);
  setLastKeyDown(millis());
  setDoubleClickDelay(0);
  setDebounceDelay(20);
  setLastDebounceTime(millis());
  setIsActiveLow(isActiveLow);
  setLongKeyDownLastReading(millis());
  longKeyDownIsHeld = false;
}

void ArduinoButton::loop() {
  if(keyUpCallback == NULL && keyDownCallback == NULL && doubleClickCallback == NULL) return;
  bool val = digitalRead(buttonPin);

  if(val != lastReading) {
    lastReading = val;
    setLastDebounceTime(millis());
    return;  
  }

  if(val == lastReading &&  millis() - lastDebounceTime >= debounceDelay) {
    if(keyUpCallback != NULL && val == normalizeButtonState(LOW) && prevState == normalizeButtonState(HIGH)) keyUpCallback();
    if(keyDownCallback != NULL && val == normalizeButtonState(HIGH) && prevState == normalizeButtonState(LOW)) keyDownCallback();
    if(doubleClickCallback != NULL && val == normalizeButtonState(HIGH) && prevState == normalizeButtonState(LOW) && millis() - lastKeyDown <= doubleClickDelay) doubleClickCallback();
    else if (doubleClickCallback != NULL && val == normalizeButtonState(HIGH) && prevState == normalizeButtonState(LOW)) lastKeyDown = millis();
    if(longKeyDownCallback != NULL) {
      if(val == normalizeButtonState(HIGH) && prevState == normalizeButtonState(LOW) && !longKeyDownIsHeld) setLongKeyDownLastReading(millis());
      if(val == normalizeButtonState(HIGH) && prevState == normalizeButtonState(HIGH) && !longKeyDownIsHeld && millis() - longKeyDownLastReading >= longKeyDownInitialDelay) {
        setLongKeyDownLastReading(millis());
        longKeyDownIsHeld = true;
        longKeyDownCallback();
      } else if (val == normalizeButtonState(HIGH) && prevState == normalizeButtonState(HIGH) && longKeyDownIsHeld && millis() - longKeyDownLastReading >= longKeyDownDelay) {
        setLongKeyDownLastReading(millis());
        longKeyDownCallback();
      } else if (val == normalizeButtonState(LOW) && prevState == normalizeButtonState(HIGH) && longKeyDownIsHeld) {
        setLongKeyDownLastReading(millis());
        longKeyDownIsHeld = false;
      }
    }
    prevState = val;
  }
  else return;
}

void ArduinoButton::onKeyUp(void (*cb)()) {
  keyUpCallback = cb;
}

void ArduinoButton::onKeyDown(void (*cb)()) {
  keyDownCallback = cb;
}

void ArduinoButton::onDoubleClick(void (*cb)(), int delay = 500) {
  doubleClickCallback = cb;
  setDoubleClickDelay(delay);
}

void ArduinoButton::onLongKeyDown(void (*cb)(), int initialDelay = 1000, int delay = 500) {
  longKeyDownCallback = cb;
  longKeyDownInitialDelay = initialDelay;
  setLongKeyDownDelay(delay);
}

void ArduinoButton::setButtonPin(int pin) {
  buttonPin = pin;  
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

void ArduinoButton::setIsActiveLow(bool activeLow) {
  isActiveLow = activeLow;
}

bool ArduinoButton::normalizeButtonState(bool state) {
  return isActiveLow ? (state == HIGH ? LOW : HIGH) : state;
}

void ArduinoButton::setLongKeyDownDelay(int delay) {
  longKeyDownDelay = delay;
}

void ArduinoButton::setLongKeyDownLastReading(unsigned long time) {
  longKeyDownLastReading = time;  
}
