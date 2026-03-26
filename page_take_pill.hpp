#pragma once

#include "page.hpp"

class PageTakePill: public Page {
    public:
    PageTakePill();
    void draw(Screen& screen, int bg, int fg) override;
    void handle_input(input_type_e type) override;
};
