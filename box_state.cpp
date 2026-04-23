#include "box_state.hpp"

BoxState::BoxState():_nb_compartment(DEF_NB_COMPARTMENT),_compartment_state{} {
    for (int i = 0; i < DEF_NB_COMPARTMENT; ++i) {
        Time t(12, 15);
        CompartmentState cs;
        cs.set_reminder(t);
        _compartment_state.push_back(cs);
    }
}

BoxState::~BoxState() {}

CompartmentState BoxState::get_compartment(int id) {
    return _compartment_state[id];
}
