#pragma once

#include "page.hpp"

class PageAddPill: public Page {
    public:
    PageAddPill();
    void draw(Screen& screen, BoxState& state, int bg, int fg) override;
    UIMessage handle_input(input_type_e type) override;
};
