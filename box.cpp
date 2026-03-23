#include "box.hpp"


Box::Box():_nb_compartment(NB_COMPARTEMENT),_screen(new Screen) {
}

Box::~Box() {
    delete _screen;
}

void Box::init() {
    _screen->init();
    _screen->write_line(10, 10, WHITE, BLACK, "Hello from the drug box");
    _screen->sleep();
}

void Box::update() {}
