#include "compartment_state.hpp"

CompartmentState::CompartmentState():_is_configured(false),_reminder_time(0, 0),_forbidden_time(0, 0) {}

void CompartmentState::set_reminder(Time t) {
    _reminder_time = t;
    _is_configured = true;
}

void CompartmentState::set_forbidden_until(Time t) {
    _forbidden_time = t;
    _is_configured = true;
}

Time CompartmentState::get_reminder_time() {
    return _reminder_time;
}

Time CompartmentState::get_forbidden_time() {
    return _forbidden_time;
}

bool CompartmentState::is_configured() {
    return _is_configured;
}
