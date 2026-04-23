#pragma once

#include "screen.hpp"
#include "uielement.hpp"
#include "time.hpp"

class UITime : public UIElement {
public:
    UITime(int x, int y, int bg, int fg, int id);
    ~UITime();
    void draw(Screen& screen, BoxState& state, int bg, int fg) override;
private:
    int _compartment_id;
};
