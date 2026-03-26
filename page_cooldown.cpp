#include "page_cooldown.hpp"
#include "uielement.hpp"
#include "uitext.hpp"

PageCooldown::PageCooldown():Page("Watch cooldowns") {
    _elements.push_back(new UIText(10, 10, WHITE, BLACK, _name));
}

void PageCooldown::draw(Screen& screen, int bg, int fg) {
    for (UIElement* e: _elements) {
        e->draw(screen, bg, fg);
    }
}

void PageCooldown::handle_input(input_type_e type) {}
