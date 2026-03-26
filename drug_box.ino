#include "esp_sleep.h"

#include "box.hpp"
#include "input_type.hpp"

#define BUTTON_PIN 27
#define MAX_INACTIVITY_TIME_MS 5000

RTC_DATA_ATTR unsigned long last_pressed_time = 0;

Box box;

int loop_nb = 0;

void setup() {
  box.init();
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // verify wake up reason
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("Woke up by button !");
  }

   if (last_pressed_time == 0) {
      last_pressed_time = millis();
   }
}

void loop() {
  int button_state = digitalRead(BUTTON_PIN);

  if (button_state == LOW) {
    Serial.println("Button pressed");
    last_pressed_time = millis();
    delay(50); // simple anti bounce
  }

  if (millis() - last_pressed_time >= MAX_INACTIVITY_TIME_MS) {
    Serial.println("Going in deep sleep after a long anactivity");
    esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, 0);
    esp_deep_sleep_start();
  }

  if (loop_nb == 2) {
    box.handle_input(IT_SELECT);
  } else if (loop_nb == 4) {
    box.handle_input(IT_RETURN);
  } else {
    box.handle_input(IT_UP);
  }
  loop_nb++;
  box.update();
  delay(50);
}
