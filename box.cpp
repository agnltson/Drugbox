#include "esp_sleep.h"
#include "box.hpp"
#include "input_type.hpp"


RTC_DATA_ATTR unsigned long Box::_last_button_pressed_time = 0;

Box::Box():_screen(new Screen),_menu(new Menu),_state(new BoxState),_should_update_screen(true),_clock(new Clock) {
}

Box::~Box() {
    delete _screen;
}

void Box::init() {
    _screen->init();
    _screen->clear(WHITE);
    _screen->sleep();
}

void Box::update() {
    update_screen();
}

void Box::handle_input(input_type_e type) {
    if (type == IT_NULL) {
        return;
    }
    _should_update_screen = true;
    _menu->handle_input(type);
}

void Box::update_screen() {
    if (!_should_update_screen) {
        return;
    }
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
