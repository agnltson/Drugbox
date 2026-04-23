#pragma once

#include "screen.hpp"
#include "box_state.hpp"

class Drawable {
    public:
    virtual void draw(Screen& screen, BoxState& state, int bg, int fg) = 0;
};
