/*
  ArduinoButton.h - Library for facilitating interfacing with buttons.

  Created by JMax, October 14, 2023.

  Released into the public domain.
*/

#ifndef ArduinoButton_h
#define ArduinoButton_h

#include "Arduino.h"

class ArduinoButton
{
  private:
    int buttonPin;
    bool prevState;
    void (*keyUpCallback)();
    void (*keyDownCallback)();
    void (*doubleClickCallback)();
    void (*longKeyDownCallback)();
    unsigned long lastKeyDown;
    int doubleClickDelay;
    int debounceDelay;
    unsigned long lastDebounceTime;
    bool lastReading;
    bool isActiveLow;
    bool normalizeButtonState(bool state);
    int longKeyDownDelay;
    unsigned long longKeyDownLastReading;
    int longKeyDownInitialDelay;
    bool longKeyDownIsHeld;
  public:
    ArduinoButton(int buttonPin, bool isActiveLow);
    void loop();
    void onKeyUp(void (*cb)());
    void onKeyDown(void (*cb)());
    void onDoubleClick(void (*cb)(), int delay = 500);
    void onLongKeyDown(void (*cb)(), int initialDelay = 1000, int delay = 500);
    void setButtonPin(int pin);
    void setLastKeyDown(unsigned long lastKeyDown);
    void setDoubleClickDelay(int delay);
    void setDebounceDelay(int delay);
    void setLastDebounceTime(unsigned long time);
    void setIsActiveLow(bool aciveLow);
    void setLongKeyDownDelay(int delay);
    void setLongKeyDownLastReading(unsigned long time);
};

#endif
