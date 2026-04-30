#include <Arduino.h>
#include <driver/rtc_io.h>

#include "power_manager.hpp"

void PowerManager::init(Clock* clock_p) {
    _clock = clock_p;
    _last_activity = _clock->get_time();
}

void PowerManager::enable_button_wakeup(int button_pin) {
    _wakeup_mask |= (1ULL << button_pin);
    _wakeup_button_pin.push_back(button_pin);
}

void PowerManager::enable_rtc_wakeup(int rtc_pin) {
    _rtc_pin = rtc_pin;
    rtc_gpio_init((gpio_num_t)rtc_pin);
    rtc_gpio_set_direction((gpio_num_t)rtc_pin, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en((gpio_num_t)rtc_pin);
    rtc_gpio_pulldown_dis((gpio_num_t)rtc_pin);
}

void setup_buttons(std::vector<int> buttons) {
    for (int i = 0; i < buttons.size(); ++i) {
        rtc_gpio_init((gpio_num_t)buttons[i]);
        rtc_gpio_set_direction((gpio_num_t)buttons[i], RTC_GPIO_MODE_INPUT_ONLY);
        rtc_gpio_pulldown_en((gpio_num_t)buttons[i]);
        rtc_gpio_pullup_dis((gpio_num_t)buttons[i]);
    }
}

void PowerManager::restore_buttons() {
    std::vector<int> buttons = this->_wakeup_button_pin;
    for (int i = 0; i < buttons.size(); ++i) {
        rtc_gpio_deinit((gpio_num_t)buttons[i]);
        pinMode((gpio_num_t)buttons[i], INPUT_PULLDOWN);
    }
}

void PowerManager::apply_wakeup_sources() {
    setup_buttons(_wakeup_button_pin);
    esp_sleep_enable_ext1_wakeup(_wakeup_mask, ESP_EXT1_WAKEUP_ANY_HIGH);
}

void PowerManager::sleep(uint64_t time_us) {
    apply_wakeup_sources();
    esp_deep_sleep_start();
}

void PowerManager::set_next_wakeup(Time t) {
    _clock->set_next_wakeup_int(t);
}

void PowerManager::update() {

    Time now = _clock->get_time();

    int now_min = now.hour() * 60 + now.minute();
    int last_min = _last_activity.hour() * 60 + _last_activity.minute();

    int diff = now_min - last_min;

    // gestion du passage minuit
    if (diff < 0) {
        diff += 24 * 60;
    }

    Serial.print("now="); Serial.print(now_min);
    Serial.print(" last="); Serial.print(last_min);
    Serial.print(" diff="); Serial.println(diff);

    if (diff >= _cooldown_minutes) {
        Serial.println("Cooldown finished -> sleeping");

        sleep(60ULL * 1000000ULL);
    }
}

void PowerManager::start_sleep_cooldown() {
    Serial.println("Cooldown started");
    _last_activity = _clock->get_time();
}

esp_sleep_wakeup_cause_t PowerManager::wake_up_cause() {
    return esp_sleep_get_wakeup_cause();
}
