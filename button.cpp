#include "button.hpp"

Button::Button(int pin):_pin(pin),_detect_val(DEFAULT_PRESSURE) {}

bool Button::is_pressed() {
    return touchRead(_pin) <= _detect_val;
}
