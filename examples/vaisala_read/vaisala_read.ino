#include "HMP155.h"

HMP155 vaisala(Serial2, 24);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_7E1);
  pinMode(24, OUTPUT);

  vaisala.begin();
}

void loop() {
  Serial.println(F("reading"));
  vaisala.read();
  Serial.println(F("Temperature of additonal sensor"));
  Serial.println(vaisala.ta());
  Serial.println(F("Temperature of wet-bulb"));
  Serial.println(vaisala.tw());
  Serial.println(F("Relative humidity"));
  Serial.println(vaisala.rh());
  Serial.println(F("VPD"));
  Serial.println(vaisala.vpd());
  delay(5000);
}
