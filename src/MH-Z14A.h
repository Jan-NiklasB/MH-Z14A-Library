
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
        #if defined(Serial_)
            MHZ14A(HardwareSerial &serial, Serial_ &logSerial);         //Constructor with UART and nativ serial port for debuging (for example SerialUSB on Arduino Due)
        #endif
        void begin(int timeout);                                    //Method for initializing the UART and debug port
        int readConcentrationPPM(byte sensor);                      //Function for reading the CO2-concentration in PPM
        void calZeroPoint(byte sensor);                             //Method to set the zero point (refere to manual)
        void calSpanPoint(byte sensor, uint8_t span_value_ppm);     //Method to set the zero span (refere to manual), span_value_ppm should be above 1000
        void setDetectionRange(byte sensor, byte Range[4]);
        void setAutoCal(byte sensor, bool state);
        void setDebug(bool state);                                  //Method to set the debug mode if debug port is specified
        const byte MR_2000[4] = {0x00, 0x00, 0x07, 0xD0};
        const byte MR_5000[4] = {0x00, 0x00, 0x13, 0x88};
        const byte MR_10000[4] = {0x00, 0x00, 0x27, 0x10}; 
    private:
        byte crc(byte msg[9]);                                      //Function to calculate the checksum
        void log(byte msg[9]);                                      //Method to send the debug messages to the serial interface
        HardwareSerial* ser;
        HardwareSerial* logSer;
        #if defined(Serial_)
            Serial_* logSerUSB;
        #endif
        bool serIsUSB;
        bool canDebug = true;
        bool debug = false;
};
