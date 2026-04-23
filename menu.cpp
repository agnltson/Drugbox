#include "menu.hpp"
#include "uitext.hpp"
#include "page_add_pill.hpp"
#include "page_cooldown.hpp"
#include "page_box_option.hpp"
#include "page_take_pill.hpp"

#define LINE_GAP 25

Menu::Menu():_pages{},_selected(nullptr),_over(0) {
    //_pages.push_back(new PageAddPill());
    _pages.push_back(new PageCooldown());
    _pages.push_back(new PageTakePill());
    _pages.push_back(new PageBoxOption());
    for (int i = 0; i < _pages.size(); ++i) {
        String name = _pages[i]->get_name();
        _elements.push_back(new UIText(10, LINE_GAP*(i+1), WHITE, BLACK, name));
    }
}

Menu::~Menu() {}

void Menu::draw(Screen& screen, BoxState& state, int bg, int fg) {
    Serial.println("drawing menu");
    if (_selected != nullptr) {
        _selected->draw(screen, state, bg, fg);
        return;
    }
    for (int i = 0; i < _elements.size(); ++i) {
        UIElement* e = _elements[i];
        if (i == _over) {
            e->draw(screen, state, fg, bg);
        } else {
            e->draw(screen, state, bg, fg);
        }
    }
}

UIMessage Menu::handle_input(input_type_e type) {
    if (_selected != nullptr && type != IT_RETURN) {
        return _selected->handle_input(type);
    }
    switch(type) {
        case IT_UP:
            _over = (_over+1) % _pages.size();
            break;
        case IT_SELECT:
            _selected = _pages[_over];
            break;
        case IT_RETURN:
            _selected = nullptr;
            break;
        default:
            UIMessage ans;
            return ans;
    }
    UIMessage ans;
    return ans;
}
