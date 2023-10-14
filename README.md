# ArduinoButton

Library for facilitating interfacing with buttons.

## Installation

1. Download the latest zip file from the [releases](https://github.com/JMax45/arduino-button/releases) page.
2. Install the zip file via Sketch->#include->Add library from .ZIP file.

## Usage

```cpp
#include <ArduinoButton.h>

#define BUTTON_PIN 7

ArduinoButton button(BUTTON_PIN);

void setup() {
  Serial.begin(9600);

  // Callback for key up event
  button.onKeyUp([]() {
    Serial.print("button click callback");
  });

  // Callback for key down event
  button.onKeyDown([]() {
    Serial.print("button down callback");
  });

  // Callback for double click event
  button.onDoubleClick([]() {
    Serial.print("double click callback");
  });

  // Callback for double click with a custom delay between two clicks (e.g., 1000ms)
  button.onDoubleClick([]() {
    Serial.print("double click callback with custom delay");
  }, 1000);
}

void loop() {
  button.loop();
}
```

**Current Limitation:** This library currently supports listening to only one event per button. In the future, there may be support for handling multiple events per button.
