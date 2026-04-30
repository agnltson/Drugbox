#include <Arduino.h>
#include "esp_sleep.h"

#include "button.hpp"

Button::Button(int pin):_pin(pin) {
  pinMode(pin, INPUT_PULLDOWN);
}

bool Button::is_pressed() {
    return digitalRead(_pin) == HIGH;
}
