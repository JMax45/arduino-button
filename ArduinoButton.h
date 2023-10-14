/*
  ArduinoButton.h - Library for facilitating interfacing with buttons.

  Created by JMax, October 14, 2023.

  Released into the public domain.
*/

#ifndef ArduinoButton_h
#define ArduinoButton_h

#include "Arduino.h"

enum clickType { KEY_UP, KEY_DOWN, DOUBLE_CLICK };

class ArduinoButton
{
  private:
    int buttonPin;
    clickType type; 
    bool prevState;
    void (*clickCallback)();
    unsigned long lastKeyDown;
    int doubleClickDelay;
    int debounceDelay;
    unsigned long lastDebounceTime;
    bool lastReading;
  public:
    ArduinoButton(int buttonPin);
    void loop();
    void onKeyUp(void (*cb)());
    void onKeyDown(void (*cb)());
    void onDoubleClick(void (*cb)(), int delay = 500);
    void setButtonPin(int pin);
    void setClickType(clickType type);
    void setCallback(void (*cb)());
    void setLastKeyDown(unsigned long lastKeyDown);
    void setDoubleClickDelay(int delay);
    void setDebounceDelay(int delay);
    void setLastDebounceTime(unsigned long time);
};

#endif
