#include <Arduino.h>

#include "power_manager.hpp"

void PowerManager::begin() {
    _clock.begin();
}

void PowerManager::enable_button_wakeup(int button_pin) {
    _button_pin = button_pin;
    esp_sleep_enable_ext0_wakeup((gpio_num_t)_button_pin, 0);
}

void PowerManager::sleep(uint64_t time_us) {
    esp_sleep_enable_timer_wakeup(time_us);
    delay(200);
    esp_deep_sleep_start();
}

void PowerManager::update() {
    if (!_cooldown_started) return;

    Time now = _clock.get_time();

    int now_min = now.hour() * 60 + now.minute();
    int last_min = _last_activity.hour() * 60 + _last_activity.minute();

    int diff = now_min - last_min;

    // gestion du passage minuit
    if (diff < 0) {
        diff += 24 * 60;
    }

    //Serial.print("diff = ");
    //Serial.println(diff);

    if (diff >= _cooldown_minutes) {
        Serial.println("Cooldown finished -> sleeping");

        sleep(60ULL * 1000000ULL);
    }
}

void PowerManager::start_sleep_cooldown() {
    if (_cooldown_started) {
        return;
    }

    Serial.println("Cooldown started");
    _last_activity = _clock.get_time();
    _cooldown_started = true;
}

void PowerManager::reset_sleep_cooldown() {
    _last_activity = _clock.get_time();
    _cooldown_started = false;
}

esp_sleep_wakeup_cause_t PowerManager::wake_up_cause() {
    return esp_sleep_get_wakeup_cause();
}
