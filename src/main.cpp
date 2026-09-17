#include <Arduino.h>

const int POT_PIN = 1; // GPIO 1

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {
  int raw = analogRead(POT_PIN);
  float voltage = (raw / 4095.0f) * 3.3f;

  Serial.print("ADC: ");
  Serial.print(raw);
  Serial.print(" | Tegangan pendekatan: ");
  Serial.print(voltage, 3);
  Serial.println(" V");

  delay(500);
}
