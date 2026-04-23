#pragma once

#include "uielement.hpp"

class UIRectangle: public UIElement {
    public:
    UIRectangle(int x, int y, int bg, int fg, int height, int width);
    ~UIRectangle();
    void draw(Screen& screen, BoxState& state, int bg, int fg) override;
    private:
    int _height;
    int _width;
};
