#pragma once

#include "screen.hpp"

class Drawable {
    public:
    virtual void draw(Screen& screen, int bg, int fg) = 0;
};
