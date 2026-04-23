#pragma once

#include "esp_sleep.h"
#include "clock.hpp"

class PowerManager {
    public:
    void init(Clock* clock_p);
    void enable_button_wakeup(int button_pin);
    void enable_rtc_wakeup(int rtc_pin);
    void sleep(uint64_t time_us);
    esp_sleep_wakeup_cause_t wake_up_cause();
    void set_next_wakeup(Time t);
    void update();
    void start_sleep_cooldown();
    private:
    Clock* _clock;
    int _button_pin;
    int _rtc_pin;
    uint64_t _wakeup_mask = 0;
    Time _last_activity = Time(0,0);
    int _cooldown_minutes = 1;
};
