#pragma once

#include <vector>

#include "button.hpp"
#include "input_type.hpp"

class InputManager {
    public:
    InputManager();
    void add_button(int pin, input_type_e t);
    input_type_e get_input_type();
    private:
    std::vector<Button*> _buttons;
    std::vector<input_type_e> _buttons_types;
};
