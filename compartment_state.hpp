#pragma once

#include "time.hpp"

class CompartmentState {
    public:
    CompartmentState();
    void set_reminder(Time t); // set a reminder to take a pill at time t
    void set_forbidden_until(Time t); // forbid you to take a pill until t
    Time get_reminder_time();
    Time get_forbidden_time();
    bool is_configured();
    private:
    Time _reminder_time;
    Time _forbidden_time;
    bool _is_configured; // if not configured you shouldn't whatch it
};
