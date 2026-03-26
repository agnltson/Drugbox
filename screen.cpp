#include "screen.hpp"

Screen::Screen(): _display(GxEPD2_213_B72(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY)) {}

void Screen::init() {
    this->_display.init(115200);
    this->_display.setRotation(1);
    this->_display.setPartialWindow(0, 0, this->_display.width(), this->_display.height());
    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_CS);
}

void Screen::clear(int color) {
    this->_display.setFullWindow();
    this->_display.firstPage();
    do {
        this->_display.fillScreen(color);
    } while (this->_display.nextPage());
}

void Screen::sleep() {
    this->_display.hibernate();
}


/*int Screen::get_text_height() {
    int16_t x1, y1;
    uint16_t w, h;

    _display.getTextBounds("A", 0, 0, &x1, &y1, &w, &h);
    return h;
}*/
