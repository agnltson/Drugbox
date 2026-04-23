#include "esp_sleep.h"
#include "box.hpp"
#include "input_type.hpp"

RTC_DATA_ATTR BoxState Box::_box_state{}; // to have presistant state across deepsleep

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
    Time t(12, 12);
    _box_state.get_compartment(0);
}

void Box::update() {
    //Serial.println("Box was updated");
    if (_should_update_screen) {
        update_screen();
    }
    Time current_time = _clock->get_time();
}

Screen& Box::get_screen() {
    return *_screen;
}

UIMessage Box::handle_input(input_type_e type) {
    UIMessage ans;
    if (type == IT_NULL) {
        return ans;
    }
    _should_update_screen = true;
    _menu->handle_input(type);

    return ans;
}

void Box::update_screen() {
    auto& d = _screen->get_display();

    d.setFullWindow();

    d.firstPage();
    do {
        d.fillScreen(WHITE);

        _menu->draw(*_screen, _box_state, WHITE, BLACK);

    } while (d.nextPage());

    _screen->sleep();
    _should_update_screen = false;
}
