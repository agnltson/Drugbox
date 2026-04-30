#include "clock.hpp"
#include <RtcUtility.h>

#define SDA_PIN 4
#define SCL_PIN 0

Clock::Clock() : _rtc(Wire) {}

void Clock::begin() {
    Wire.begin(SDA_PIN, SCL_PIN);
    _rtc.Begin();

    if (!_rtc.IsDateTimeValid()) {
        _rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
    }

    if (!_rtc.GetIsRunning()) {
        _rtc.SetIsRunning(true);
    }
}

void Clock::clear_alarm() {
    _rtc.LatchAlarmsTriggeredFlags();
}

Time Clock::get_time() {
    RtcDateTime now = _rtc.GetDateTime();
    return Time(now.Hour(), now.Minute());
}
