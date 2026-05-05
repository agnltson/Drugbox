#pragma once

#include <vector>

#include "esp_sleep.h"
#include "box.hpp"
#include "clock.hpp"

class PowerManager {
    public:
    void init(Clock* clock_p);
    void enable_button_wakeup(int button_pin);
    void enable_rtc_wakeup(int rtc_pin);
    void apply_wakeup_sources();
    void sleep(uint64_t time_us);
    esp_sleep_wakeup_cause_t wake_up_cause();
    void restore_buttons();
    void set_next_wakeup(Time t);
    void update(Box& box);
    void start_sleep_cooldown();
    private:
    Clock* _clock;
    std::vector<int> _wakeup_button_pin;
    int _rtc_pin = -1;
    uint64_t _wakeup_mask = 0;
    Time _last_activity = Time(0,0);
    int _cooldown_minutes = 1;
};
