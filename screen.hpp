#pragma once

#include <GxEPD2_BW.h>
#include <SPI.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

#define BIG_FONT &FreeSansBold12pt7b
#define SMALL_FONT &FreeSansBold9pt7b

#define BLACK GxEPD_BLACK
#define WHITE GxEPD_WHITE

#define PIN_CS 5
#define PIN_DC 17
#define PIN_RST 16
#define PIN_BUSY 26
#define PIN_SCK 18 //CLK
#define PIN_MISO 19 //NOT CONNECTED
#define PIN_MOSI 23 //DIN

typedef GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display_t;

class Screen {
    public:
    Screen();
    void init();
    void clear(int color);
    void sleep();
    bool next_page() { return _display.nextPage(); }
    display_t& get_display() { return _display; }
    private:
    display_t _display;
};
