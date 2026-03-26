#include "box.hpp"

Box::Box():_screen(new Screen),_menu(new Menu),_state(new BoxState),_should_update(true) {}

Box::~Box() {
    delete _screen;
}

void Box::init() {
    _screen->init();
    _screen->clear(WHITE);
    _screen->sleep();
}

void Box::update() {
    if (!_should_update) {
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
    _should_update = false;
}

void Box::handle_input(input_type_e type) {
    _should_update = true;
    _menu->handle_input(type);
}
