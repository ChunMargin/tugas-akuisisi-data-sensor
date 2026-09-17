#include <Arduino.h>

const int SWITCH_PIN = 3;

void setup() {
  Serial.begin(115200);
  // Mengaktifkan pull-down internal agar pin stabil di LOW saat mengambang
  pinMode(SWITCH_PIN, INPUT_PULLDOWN); 
}

void loop() {
  int state = digitalRead(SWITCH_PIN);

  if (state == HIGH) {
    Serial.println("SPDT = HIGH / ON");
  } else {
    Serial.println("SPDT = LOW / OFF");
  }

  delay(300);
}
