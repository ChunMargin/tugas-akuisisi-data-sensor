#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(115200);

  Wire.begin(20, 21);  // SDA=20, SCL=21

  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("BH1750 siap.");
  } else {
    Serial.println("BH1750 tidak terdeteksi.");
  }
}

void loop() {
  float lux = lightMeter.readLightLevel();

  Serial.print("Cahaya: ");
  Serial.print(lux, 2);
  Serial.println(" lx");

  delay(1000);
}
