#pragma once

#include "drawable.hpp"
#include "interactive.hpp"
#include "uielement.hpp"

#include <vector>

class Page: public Drawable, public Interactive {
    public:
    Page(const char* name):_name(name){};
    String get_name() { return _name; };
    protected:
    String _name;
    std::vector<UIElement*> _elements;
    UIElement* _selected;
};
