#pragma once
#include <Arduino.h>

#define DEFAULT_PRESSURE 500

class Button {
    public:
    Button(int pin);
    bool is_pressed();
    private:
    int _pin;
    int _detect_val;
};
