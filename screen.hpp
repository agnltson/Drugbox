#pragma once

#include <GxEPD2_BW.h>
#include <SPI.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define BLACK GxEPD_BLACK
#define WHITE GxEPD_WHITE

#define PIN_CS 5
#define PIN_DC 17
#define PIN_RST 16
#define PIN_BUSY 26
#define PIN_SCK 18
#define PIN_MISO 19
#define PIN_MOSI 23

typedef GxEPD2_BW<GxEPD2_213_B72, GxEPD2_213_B72::HEIGHT> display_t;

class Screen {
    public:
    Screen();
    void init();
    void write_line(int x, int y, int bg, int fg, const char* s);
    void clear(int color);
    void sleep();
    private:
    display_t _display;
};
