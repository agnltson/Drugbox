#pragma once

#include "screen.hpp"
#include "menu.hpp"
#include "box_state.hpp"
#include "interactive.hpp"
#include "button.hpp"
#include "clock.hpp"

#define NB_BUTTON 3

#define MAX_INACTIVITY_TIME_MS 5000

class Box: public Interactive {
    public:
    Box();
    ~Box();
    void init();
    void update();
    void handle_input(input_type_e type) override;
    private:
    void update_screen();
    Screen* _screen;
    Menu* _menu;
    BoxState* _state;
    Clock* _clock;
    bool _should_update_screen;
    static unsigned long _last_button_pressed_time;
};
