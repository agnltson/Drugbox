#pragma once

class Time {
    public:
    Time(char hour, char minute);
    char hour();
    char minute();
    bool operator==(Time& t);
    bool operator<(Time& t);
    bool operator>(Time& t);
    private:
    char _hour;
    char _minute;
};
