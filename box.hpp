#pragma once

#include <vector>

#include "screen.hpp"
#include "flat_menu.hpp"
#include "box_state.hpp"
#include "interactive.hpp"
#include "button.hpp"
#include "box_state.hpp"
#include "clock.hpp"
#include "time.hpp"

#define NB_BUTTON 3

#define MAX_INACTIVITY_TIME_MS 5000

class Box: public Interactive {
    public:
    Box();
    ~Box();
    void init(Clock* clock);
    void update();
    Screen& get_screen();
    UIMessage handle_input(input_type_e type) override;
    Time get_next_take(Time now);
    void show_standby(Time now, Time next);
    private:
    void update_screen();
    Clock* _clock;
    Screen* _screen;
    FlatMenu* _menu;
    static BoxState _box_state;
    bool _should_update_screen;
};
