#include "box_state.hpp"

BoxState::BoxState() : _nb_compartment(DEF_NB_COMPARTMENT), _current_time(0, 0) {
    for (int i = 0; i < DEF_NB_COMPARTMENT; ++i) {
        _compartment_state[i].set_next_take(Time(12, 15));
    }
}

BoxState::~BoxState() {}

CompartmentState* BoxState::get_compartment(int id) {
    return &_compartment_state[id];
}

Time BoxState::get_next_take(Time now) {
    int now_min = now.hour() * 60 + now.minute();
    int best_diff = 24 * 60 + 1;
    Time next(0, 0);

    for (int i = 0; i < _nb_compartment; ++i) {
        Time comp_time = _compartment_state[i].get_next_take();
        int comp_min = comp_time.hour() * 60 + comp_time.minute();
        int diff = comp_min - now_min;
        if (diff <= 0) diff += 24 * 60;
        if (diff < best_diff) {
            best_diff = diff;
            next = comp_time;
        }
    }
    return next;
}

void BoxState::set_current_time(Time t) {
    _current_time = t;
}

Time BoxState::get_current_time() {
    return _current_time;
}
