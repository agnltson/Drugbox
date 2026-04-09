#pragma once

#include "esp_sleep.h"
#include "clock.hpp"

class PowerManager {
    public:
    void begin();
    void enable_button_wakeup(int button_pin);
    void sleep(uint64_t time_us);
    esp_sleep_wakeup_cause_t wake_up_cause();
    void update();
    void start_sleep_cooldown();
    void reset_sleep_cooldown();
    private:
    Clock _clock;
    int _button_pin;
    Time _last_activity = Time(0,0);
    int _cooldown_minutes = 1;
    bool _cooldown_started = false;
};
