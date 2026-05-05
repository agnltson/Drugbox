#include "box.hpp"
#include "power_manager.hpp"
#include "input_manager.hpp"
#include "clock.hpp"
#include "input_type.hpp"

#define BUTTON1_PIN 27
#define BUTTON2_PIN 25
#define BUTTON3_PIN 32
#define BUZZER_PIN 19

Box box;
InputManager input;
PowerManager power;
Clock internal_clock;

// ---------- TODO ----------
// Anti rebond sur les boutons
// Configuration pour enlever activation module inutile (eg. wifi, bluetooth)

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);

  internal_clock.begin();

  box.init(&internal_clock);
  power.init(&internal_clock);
  esp_sleep_wakeup_cause_t cause = power.wake_up_cause();

  if (cause == ESP_SLEEP_WAKEUP_TIMER) {
      Serial.println("Réveil par timer");
      digitalWrite(BUZZER_PIN, HIGH); // ON
      delay(1000);
      digitalWrite(BUZZER_PIN, LOW);  // OFF
  } else if (cause == ESP_SLEEP_WAKEUP_EXT1) {
    uint64_t mask = esp_sleep_get_ext1_wakeup_status();
    if (mask & (1ULL << BUTTON1_PIN)) Serial.println("Réveil par bouton 1");
    if (mask & (1ULL << BUTTON2_PIN)) Serial.println("Réveil par bouton 2");
    if (mask & (1ULL << BUTTON3_PIN)) Serial.println("Réveil par bouton 3");
  } else {
    Serial.println("\nWake by regular poweron");
  }

  power.restore_buttons();

  power.start_sleep_cooldown();

  input.add_button(BUTTON1_PIN, IT_RETURN);
  input.add_button(BUTTON2_PIN, IT_SELECT);
  input.add_button(BUTTON3_PIN, IP_NEXT);

  power.enable_button_wakeup(BUTTON1_PIN);
  power.enable_button_wakeup(BUTTON2_PIN);
  power.enable_button_wakeup(BUTTON3_PIN);
}

void loop() {

  digitalWrite(BUZZER_PIN, HIGH); // ON
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);  // OFF

  input_type_e in_type = input.get_input_type();
  if (in_type != IT_NULL) {
    power.start_sleep_cooldown();
    box.handle_input(in_type);
  }
  box.update();
  power.update(box);
  delay(50);
}
