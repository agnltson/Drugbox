#include "page_add_pill.hpp"
#include "uielement.hpp"
#include "uitext.hpp"

PageAddPill::PageAddPill():Page("Add pill") {
    _elements.push_back(new UIText(10, 10, WHITE, BLACK, _name));
}

void PageAddPill::draw(Screen& screen, BoxState& state, int bg, int fg) {
    for (UIElement* e: _elements) {
        e->draw(screen, state, bg, fg);
    }
}

UIMessage PageAddPill::handle_input(input_type_e type) {
    UIMessage ans;
    return ans;
}
