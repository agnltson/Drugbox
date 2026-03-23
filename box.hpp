#pragma once

#include "screen.hpp"

#define NB_COMPARTEMENT 4

class Box {
    public:
    Box();
    ~Box();
    void init();
    void update();
    private:
    int _nb_compartment;
    Screen* _screen;
};
