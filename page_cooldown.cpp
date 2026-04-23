#include "page_cooldown.hpp"
#include "uielement.hpp"
#include "uitext.hpp"
#include "uitime.hpp"

PageCooldown::PageCooldown():Page("Watch cooldown") {
    _elements.push_back(new UIText(10, 10, WHITE, BLACK, _name));
    _elements.push_back(new UITime(10, 20, WHITE, BLACK, 0));
}

void PageCooldown::draw(Screen& screen, BoxState& state, int bg, int fg) {
    Serial.println("drawing pagecooldown");
    for (UIElement* e: _elements) {
        e->draw(screen, state, bg, fg);
    }
}

UIMessage PageCooldown::handle_input(input_type_e type) {
    UIMessage ans;
    return ans;
}
