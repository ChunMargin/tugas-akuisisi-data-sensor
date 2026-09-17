#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4      // GPIO4, pin aman untuk DHT11 pada ESP32-C3
#define DHTTYPE DHT11 // sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000); // tunggu serial USB siap
  Serial.println("Monitoring sensor DHT11...");
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca sensor DHT11!");
  } else {
    Serial.print("Kelembapan: ");
    Serial.print(humidity);
    Serial.print("%\t");
    Serial.print("Suhu: ");
    Serial.print(temperature);
    Serial.println("°C");
  }

  delay(1000);
}
