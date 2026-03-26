#pragma once

#include "page.hpp"

class PageCooldown: public Page {
    public:
    PageCooldown();
    void draw(Screen& screen, int bg, int fg) override;
    void handle_input(input_type_e type) override;
};
