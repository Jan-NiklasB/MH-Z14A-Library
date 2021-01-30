#include <Arduino.h>
#include "MH-Z14A.h"

MHZ14A sensor(Serial1, Serial);                                                                     //Creating instance of MHZ14A class

void setup() {
  Serial.begin(115200);                                                                             //Initialising Serial class for communication with PC (log output over console)
  Serial.println("Setup running...");                                                               //Printing "Setup running..." to Serial console
  sensor.begin(4000);                                                                               //Initialising instance of MHZ14A class with timeout of 4000 ms
  sensor.setDebug(true);                                                                            //Enabling debug output to serial console over Serial1 (Serial1 is initialized in method)
  Serial.println("Setup finished!");                                                                //Printing "Setup finished!" to Serial console
}

void loop() {
  Serial.println("CO2 concentration: " + String(sensor.readConcentrationPPM(0x01)) + " ppm");       //Reading CO2 value in PPM from sensor-id 0x01 (default) ant print it to Serial console
  delay(5000);                                                                                      //Wait 5000 ms
}
