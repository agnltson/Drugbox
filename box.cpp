#include "esp_sleep.h"
#include "box.hpp"
#include "input_type.hpp"
#include "uitext.hpp"

RTC_DATA_ATTR BoxState Box::_box_state{}; // to have presistant state across deepsleep

Box::Box():_screen(new Screen),_menu(new FlatMenu),_should_update_screen(true),_clock(nullptr) {}

Box::~Box() {
    delete _screen;
    delete _menu;
}

void Box::init(Clock* clock) {
    _screen->init();
    _screen->clear(WHITE);
    _screen->sleep();
    _clock = clock;
}

void Box::update() {
    if (_should_update_screen) {
        update_screen();
    }
    _box_state.set_current_time(_clock->get_time());
}

void Box::show_standby(Time now, Time next) {
    char buf_now[8], buf_next[16];
    snprintf(buf_now,  sizeof(buf_now),  "%02d:%02d", now.hour(), now.minute());
    snprintf(buf_next, sizeof(buf_next), "Rappel %02d:%02d", next.hour(), next.minute());

    auto& d = _screen->get_display();
    d.setFullWindow();
    d.firstPage();
    do {
        d.fillScreen(WHITE);
        UIText t_now (20, 40, WHITE, BLACK, buf_now);
        UIText t_next(20, 70, WHITE, BLACK, buf_next);
        t_now .draw(*_screen, _box_state, WHITE, BLACK);
        t_next.draw(*_screen, _box_state, WHITE, BLACK);
    } while (d.nextPage());
    _screen->sleep();
}

Time Box::get_next_take(Time now) {
    return _box_state.get_next_take(now);
}

Screen& Box::get_screen() {
    return *_screen;
}

UIMessage Box::handle_input(input_type_e type) {
    if (type == IT_NULL)
        return UIMessage();

    _should_update_screen = true;
    UIMessage msg = _menu->handle_input(type);

    Time now = _clock->get_time();
    int total_minutes = now.hour() * 60 + now.minute()
                      + msg.get_offset().hour() * 60 + msg.get_offset().minute();
    Time result(total_minutes / 60 % 24, total_minutes % 60);

    switch (msg.get_type()) {
        case UIM_SET_NEXT_TAKE:
            _box_state.get_compartment(0)->set_next_take(result);
            break;
        default:
            break;
    }

    return msg;
}

void Box::update_screen() {
    auto& d = _screen->get_display();

    d.setPartialWindow(0, 0, d.width(), d.height());

    d.firstPage();
    do {
        d.fillScreen(WHITE);

        _menu->draw(*_screen, _box_state, WHITE, BLACK);

    } while (d.nextPage());

    _screen->sleep();
    _should_update_screen = false;
}
