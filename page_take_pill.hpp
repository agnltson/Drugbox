#pragma once

#include "page.hpp"

class PageTakePill: public Page {
    public:
    PageTakePill();
    void draw(Screen& screen, BoxState& state, int bg, int fg) override;
    UIMessage handle_input(input_type_e type) override;
};
