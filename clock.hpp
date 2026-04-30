#pragma once

#include <Wire.h>
#include <RtcDS3231.h>

#include "time.hpp"

class Clock {
    public:
    Clock();
    void begin();
    void clear_alarm();
    Time get_time();
    private:
    RtcDS3231<TwoWire> _rtc;
};
