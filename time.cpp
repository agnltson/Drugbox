#include "time.hpp"

Time::Time(char hour, char minute):_hour(hour),_minute(minute) {}

char Time::hour() {
    return _hour;
}

char Time::minute() {
    return _minute;
}

bool Time::operator==(Time& t) {
    return (_hour == t.hour()) && (_minute == t.minute());
}

bool Time::operator<(Time& t) {
    if (_hour < t._hour) {
        return true;
    }
    if (_hour == t._hour && _minute < t._minute) {
        return true;
    }
    return false;
}

bool Time::operator>(Time& t) {
    if (_hour <= t.hour()) {
        return false;
    }
    if (_minute <= t.minute()) {
        return false;
    }
    return true;
}
