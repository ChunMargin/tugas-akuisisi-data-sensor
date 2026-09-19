#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>

constexpr uint8_t SWITCH_PIN = 3;
constexpr uint8_t POT_PIN = 1;
constexpr uint8_t DHT_PIN = 4;
constexpr uint8_t DHT_TYPE = DHT11;

BH1750 lightMeter;
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(SWITCH_PIN, INPUT_PULLDOWN);
  analogReadResolution(12);

  Wire.begin(20, 21);

  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("BH1750 siap.");
  } else {
    Serial.println("BH1750 tidak terdeteksi.");
  }

  dht.begin();
}

void loop() {
  static unsigned long lastPrint = 1000;
  const unsigned long interval = 1000;

  if (millis() - lastPrint >= interval) {
    lastPrint = millis();

    Serial.println("=== NODE AKUISISI IIoT ===");

    const int spdtState = digitalRead(SWITCH_PIN);
    const int raw = analogRead(POT_PIN);
    const float voltage = (raw / 4095.0f) * 3.3f;
    const float lux = lightMeter.readLightLevel();
    const float humidity = dht.readHumidity();
    const float temperature = dht.readTemperature();

    Serial.print("SPDT = ");
    Serial.println(spdtState == HIGH ? "HIGH / ON" : "LOW / OFF");

    Serial.print("Potensio ADC: ");
    Serial.print(raw);
    Serial.print(" | Tegangan pendekatan: ");
    Serial.print(voltage, 3);
    Serial.println(" V");

    if (isnan(lux)) {
      Serial.println("BH1750 gagal membaca cahaya.");
    } else {
      Serial.print("Cahaya: ");
      Serial.print(lux, 2);
      Serial.println(" lx");
    }

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Gagal membaca sensor DHT11!");
    } else {
      Serial.print("Kelembapan: ");
      Serial.print(humidity);
      Serial.print("% | Suhu: ");
      Serial.print(temperature);
      Serial.println("°C");
    }

    Serial.println("----------------------------------------");
  }

}
