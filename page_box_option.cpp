#include "page_box_option.hpp"
#include "uielement.hpp"
#include "uitext.hpp"

PageBoxOption::PageBoxOption():Page("Option") {
    _elements.push_back(new UIText(10, 10, WHITE, BLACK, _name));
}

void PageBoxOption::draw(Screen& screen, int bg, int fg) {
    for (UIElement* e: _elements) {
        e->draw(screen, bg, fg);
    }
}

void PageBoxOption::handle_input(input_type_e type) {}
