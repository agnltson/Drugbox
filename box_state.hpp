#pragma once

#include <vector>

#define DEF_NB_COMPARTEMENT 1

class BoxState {
    public:
    BoxState();
    ~BoxState();
    private:
    int _nb_compartment;
    std::vector<int> _compartment_state;
};
