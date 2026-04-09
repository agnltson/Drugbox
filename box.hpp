#pragma once

#include <vector>

#include "screen.hpp"
#include "menu.hpp"
#include "box_state.hpp"
#include "interactive.hpp"
#include "button.hpp"
#include "compartment_state.hpp"
#include "clock.hpp"
#include "time.hpp"

#define NB_BUTTON 3

#define MAX_INACTIVITY_TIME_MS 5000

class Box: public Interactive {
    public:
    Box();
    ~Box();
    void init(Clock* clock_p);
    void update();
    void handle_input(input_type_e type) override;
    private:
    void update_screen();
    Screen* _screen;
    Menu* _menu;
    Clock* _clock;
    static int _nb_compartment;
    static std::vector<CompartmentState> _compartment_state;
    bool _should_update_screen;
};
