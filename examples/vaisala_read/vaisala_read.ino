#include "HMP155.h"

HMP155 vaisala(Serial, 24);

void setup() {
  vaisala.begin();
}

void loop() {
  vaisala.read();
  Serial.print(F("Temperature of additonal sensor"));
  Serial.println(vaisala.ta());
  Serial.print(F("Temperature of wet-bulb"));
  Serial.println(vaisala.tw());
  Serial.print(F("Relative humidity"));
  Serial.println(vaisala.rh());
  Serial.print(F("VPD"));
  Serial.println(vaisala.vpd());
  delay(1000);
}
