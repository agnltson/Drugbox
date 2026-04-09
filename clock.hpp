#pragma once

#include <RtcDS1302.h>

#include "time.hpp"

class Clock {
    public:
    Clock();
    void begin();
    Time get_time();
    private:
    ThreeWire _wire;
    RtcDS1302<ThreeWire> _rtc;
};
