#pragma once

#include <vector>

#include "compartment_state.hpp"

#define DEF_NB_COMPARTMENT 1

class BoxState {
    public:
    BoxState();
    ~BoxState();
    CompartmentState get_compartment(int id);
    private:
    int _nb_compartment;
    std::vector<CompartmentState> _compartment_state;
};
