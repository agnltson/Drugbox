#include "esp_sleep.h"
#include "box.hpp"
#include "input_type.hpp"

#define DEF_NB_COMPARTEMENT 1

RTC_DATA_ATTR std::vector<CompartmentState> Box::_compartment_state = {}; // persistant state across deep sleep
RTC_DATA_ATTR int Box::_nb_compartment = DEF_NB_COMPARTEMENT; // persistant state across deep sleep

Box::Box():_screen(new Screen),_menu(new Menu),_should_update_screen(true),_clock(nullptr) {}

Box::~Box() {
    delete _screen;
    delete _menu;
}

void Box::init(Clock* clock_p) {
    _screen->init();
    _screen->clear(WHITE);
    _screen->sleep();
    _clock = clock_p;
}

void Box::update() {
    Serial.println("Box was updated");
    if (_should_update_screen) {
        update_screen();
    }
    Time current_time = _clock->get_time();
}

void Box::handle_input(input_type_e type) {
    if (type == IT_NULL) {
        return;
    }
    _should_update_screen = true;
    _menu->handle_input(type);
}

void Box::update_screen() {
    auto& d = _screen->get_display();

    d.setFullWindow();

    d.firstPage();
    do {
        d.fillScreen(WHITE);

        _menu->draw(*_screen, WHITE, BLACK);

    } while (d.nextPage());

    _screen->sleep();
    _should_update_screen = false;
}
