#include "clock.hpp"
#include <RtcUtility.h>

#define SDA_PIN 4
#define SCL_PIN 0

Clock::Clock() : _rtc(Wire) {}

void Clock::begin() {
    Wire.begin();
    _rtc.Begin();

    if (!_rtc.IsDateTimeValid()) {
        _rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
    }

    if (!_rtc.GetIsRunning()) {
        _rtc.SetIsRunning(true);
    }
}

void Clock::set_next_wakeup_int(Time t) {
    RtcDateTime now = _rtc.GetDateTime();

    RtcDateTime target(
        now.Year(),
        now.Month(),
        now.Day(),
        t.hour(),
        t.minute(),
        0
    );

    // ajoute 1 jour si horaire passé
    if (target <= now) {
        RtcDateTime nextDay(
            now.Year(),
            now.Month(),
            now.Day() + 1,
            t.hour(),
            t.minute(),
            0
        );
        target = nextDay;
    }

    _rtc.LatchAlarmsTriggeredFlags();

    DS3231AlarmOne alarm(
        target.Day(),
        target.Hour(),
        target.Minute(),
        target.Second(),
        DS3231AlarmOneControl_HoursMinutesSecondsMatch
    );

    _rtc.SetAlarmOne(alarm);

    _rtc.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmOne);
}

Time Clock::get_time() {
    RtcDateTime now = _rtc.GetDateTime();
    return Time(now.Hour(), now.Minute());
}
