#include "compartment_state.hpp"

CompartmentState::CompartmentState() : _next_take_time(0, 0), _is_configured(false) {}

void CompartmentState::set_next_take(Time t) {
    _next_take_time = t;
    _is_configured = true;
}

Time CompartmentState::get_next_take() {
    return _next_take_time;
}

bool CompartmentState::is_configured() {
    return _is_configured;
}
