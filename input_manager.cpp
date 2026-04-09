#include "Arduino.h"

#include "input_manager.hpp"

InputManager::InputManager():_buttons{},_buttons_types{} {}

void InputManager::add_button(int pin, input_type_e t) {
    _buttons.push_back(new Button(pin));
    _buttons_types.push_back(t);
}

input_type_e InputManager::get_input_type() {
    for (int i = 0; i < _buttons.size(); ++i) {
        if (_buttons[i]->is_pressed()) {
            Serial.print("Button pressed: ");
            Serial.println(i+1);

            return _buttons_types[i];
        }
    }
    return IT_NULL;
}
