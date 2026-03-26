#pragma once

#include "uielement.hpp"

class UIText: public UIElement {
    public:
    UIText(int x, int y, int bg, int fg, String text);
    ~UIText();
    void draw(Screen& screen, int bg, int fg) override;
    private:
    String _text;
};
