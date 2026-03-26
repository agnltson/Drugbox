#pragma once

#include "screen.hpp"
#include "menu.hpp"
#include "box_state.hpp"
#include "interactive.hpp"

class Box: public Interactive {
    public:
    Box();
    ~Box();
    void init();
    void update();
    void handle_input(input_type_e type) override;
    private:
    Screen* _screen;
    Menu* _menu;
    BoxState* _state;
    bool _should_update;
};
