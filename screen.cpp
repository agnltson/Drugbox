#include "screen.hpp"

Screen::Screen(): _display(GxEPD2_213_B72(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY)) {}

void Screen::init() {
    this->_display.init(115200);
    this->_display.setRotation(1);
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

void Screen::write_line(int x, int y, int bg, int fg, const char* s) {
    this->_display.setFullWindow();
    this->_display.firstPage();
    do {
        this->_display.fillScreen(bg);

        this->_display.setTextColor(fg);
        //this->_display.setFont(FONT);
        this->_display.setCursor(x, y);

        this->_display.print(s);
    } while (this->_display.nextPage());
}
