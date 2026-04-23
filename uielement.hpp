#pragma once

#include <Arduino.h>

#include "drawable.hpp"

class UIElement: public Drawable {
    public:
    UIElement(int x, int y, int bg, int fg):_x(x),_y(y),_bg(bg),_fg(fg),_is_selectable(true) {}
    bool is_selectable() { return _is_selectable; }
    void set_selectable() { _is_selectable = true; }
    void unset_selectable() { _is_selectable = false; }
    protected:
    bool _is_selectable;
    int _x;
    int _y;
    int _bg;
    int _fg;
};
