#include <Arduino.h>
#include "MH-Z14A.h"

MHZ14A sensor(Serial1, Serial);

void setup() {
  Serial.begin(115200);
  Serial.println("Setup running...");
  sensor.begin(4000);
  sensor.setDebug(true);
  Serial.println("Setup finished!");
}

void loop() {
  Serial.println("CO2 concentration: " + String(sensor.readConcentrationPPM(0x01)) + " ppm");
  delay(5000);
}
