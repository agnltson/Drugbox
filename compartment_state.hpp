#pragma once
#include "time.hpp"

class CompartmentState {
    public:
    CompartmentState();
    void set_next_take(Time t);
    Time get_next_take();
    bool is_configured();
    private:
    Time _next_take_time;
    bool _is_configured;
};
