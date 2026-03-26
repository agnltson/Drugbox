#include "page_take_pill.hpp"
#include "uielement.hpp"
#include "uitext.hpp"

PageTakePill::PageTakePill():Page("Take pill") {
    _elements.push_back(new UIText(10, 10, WHITE, BLACK, _name));
}

void PageTakePill::draw(Screen& screen, int bg, int fg) {
    for (UIElement* e: _elements) {
        e->draw(screen, bg, fg);
    }
}

void PageTakePill::handle_input(input_type_e type) {}
