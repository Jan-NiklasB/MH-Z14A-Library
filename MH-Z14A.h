
/*
    MH-Z14A Library by Jan-Niklas Bogatka is licensed under CC BY-NC-SA 4.0.
    To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0
*/
#if !defined(MHZ14A_lib)
#define MHZ14A_lib
#endif // MH-Z14A lib

#include "Arduino.h"


class MHZ14A{
    public:
        MHZ14A(HardwareSerial &serial);                             //Constructor only with UART
        MHZ14A(HardwareSerial &serial, HardwareSerial &logSerial);  //Constructor with UART and Hardwareserial port for debuging
        MHZ14A(HardwareSerial &serial, Serial_ &logSerial);         //Constructor with UART and nativ serial port for debuging (for example SerialUSB on Arduino Due)
        void begin(int timeout);                                    //Method for initializing the UART and debug port
        int readConcentrationPPM(byte sensor);                      //Function for reading the CO2-concentration in PPM
        void calZeroPoint(byte sensor);                             //Method to set the zero point (refere to manual)
        void calSpanPoint(byte sensor);                             //Method to set the zero span (refere to manual)
        void setDebug(bool state);                                  //Method to set the debug mode if debug port is specified
    private:
        byte crc(byte msg[9]);                                      //Function to calculate the checksum
        void log(byte msg[9]);                                      //Method to send the debug messages to the serial interface
        HardwareSerial* ser;
        HardwareSerial* logSer;
        Serial_* logSerUSB;
        bool serIsUSB;
        bool canDebug = true;
        bool debug = false;
};