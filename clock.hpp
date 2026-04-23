#pragma once

#include <Wire.h>
#include <RtcDS3231.h>

#include "time.hpp"

class Clock {
    public:
    Clock();
    void begin();
    Time get_time();
    void set_next_wakeup_int(Time t);
    private:
    RtcDS3231<TwoWire> _rtc;
};
