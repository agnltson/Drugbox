#include "clock.hpp"

#define CLK_PIN 4
#define DAT_PIN 0
#define RST_PIN 2

Clock::Clock():_wire(DAT_PIN, CLK_PIN, RST_PIN),_rtc(_wire) {}

void Clock::begin() {
    _rtc.Begin();
    _rtc.SetIsRunning(true);
    if (!_rtc.IsDateTimeValid()) {
        _rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
    }
}

Time Clock::get_time() {
    RtcDateTime now = _rtc.GetDateTime();
    Time nowT(now.Hour(), now.Minute());
    return nowT;
}
