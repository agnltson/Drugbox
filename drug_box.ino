#include "box.hpp"
#include "power_manager.hpp"
#include "input_manager.hpp"
#include "input_type.hpp"

#define BUTTON1_PIN 27
#define BUTTON2_PIN 25
#define BUTTON3_PIN 22

Box box;
InputManager input;
PowerManager power;

Clock c;

void setup() {
  Serial.begin(115200);

  power.begin();

  box.init();

  c.begin();

  esp_sleep_wakeup_cause_t cause = power.wake_up_cause();

  if (cause == ESP_SLEEP_WAKEUP_EXT0) {
    power.reset_sleep_cooldown();
    int i = 0;
  }

  input.add_button(27, IT_RETURN);
  input.add_button(25, IT_SELECT);
  input.add_button(22, IT_UP);

  power.enable_button_wakeup(BUTTON1_PIN);
}

void loop() {
  input_type_e in_type = input.get_input_type();
  if (in_type == IT_NULL) {
    power.start_sleep_cooldown();
  } else {
    power.reset_sleep_cooldown();
  }
  power.update();
  box.handle_input(in_type);
  box.update();
  delay(50);
}
