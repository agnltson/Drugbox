#pragma once

#include <vector>

#include "compartment_state.hpp"
#include "time.hpp"

#define DEF_NB_COMPARTMENT 1

class BoxState {
    public:
    BoxState();
    ~BoxState();
    CompartmentState* get_compartment(int id);
    Time get_next_take(Time now);
    void set_current_time(Time t);
    Time get_current_time();
    private:
    int _nb_compartment;
    CompartmentState _compartment_state[DEF_NB_COMPARTMENT];
    Time _current_time;
};
