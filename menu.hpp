#pragma once

#include <vector>

#include "page.hpp"
#include "drawable.hpp"

class Menu: public Drawable, public Interactive {
    public:
    Menu();
    ~Menu();
    void draw(Screen& screen, int fg, int bg) override;
    void handle_input(input_type_e type) override;
    private:
    std::vector<Page*> _pages;
    std::vector<UIElement*> _elements;
    Page* _selected;
    int _over;
};
