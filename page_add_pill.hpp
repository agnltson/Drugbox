#pragma once

#include "page.hpp"

class PageAddPill: public Page {
    public:
    PageAddPill();
    void draw(Screen& screen, int bg, int fg) override;
    void handle_input(input_type_e type) override;
};
