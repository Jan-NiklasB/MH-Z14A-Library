#include <Arduino.h>
#include <src/MH-Z14A.h>



MHZ14A sensor;  //Creating instance of MHZ14A class

void setup() 
{
  Serial.begin(115200);                 //Initialising Serial for communication with PC (log output over console)
  Serial.println("Setup running...");   //Printing "Setup running..." to Serial console
  Serial1.begin(9600);                  //Initialising Serial1 at 9600 baud for intercom with sensor
  sensor.begin(Serial1, Serial, 4000);  //Initialising instance of MHZ14A class with Serial1 as interface to the sensor and Serial as log output to console, with a sensor timeout of 4000 ms
  
  // Syntax: sensor.begin(SerialCOM to the sensor,(opt.) SerialCOM to console, timeout for the sensor in ms)  
  
  sensor.setDebug(true);                //Enabling debug output to serial console over Serial1 
  Serial.println("Setup finished!");    //Printing "Setup finished!" to Serial console

  // sensor.calZeroPoint(0x01);                       Calibrate Zero-Point (refere to manual V 1.2)
  // sensor.calSpanPoint(0x01, 2000);                 Calibrate Span-Point with 2000 ppm CO2 environment (refere to manual V 1.2)
  // sensor.setAutoCal(0x01, false);                  Enable / Disable the autocalibration (refere to manual V 1.2)
  // sensor.setDetectionRange(0x01, sensor.MR_5000);  Set the measuring / detection range of the sensor in ppm (5000 ppm in this case)
}

void loop() {
  Serial.println("CO2 concentration: " + String(sensor.readConcentrationPPM(0x01)) + " ppm");    //Reading CO2 value in PPM from sensor-id 0x01 (default) and print it to Serial console
  delay(5000);  //Wait 5000 ms
}
