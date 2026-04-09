#pragma once

#include "input_type.hpp"

class Button {
    public:
    Button(int pin);
    bool is_pressed();
    private:
    int _pin;
};
