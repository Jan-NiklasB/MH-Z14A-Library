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
        MHZ14A();                             //Constructor only with UART
        #if (defined _UART_CLASS_) && (defined _USART_CLASS_) && (defined _USBAPI_)
            void begin(UARTClass &serial, int timeout);
            void begin(USARTClass &serial, int timeout);
            void begin(UARTClass &serial, Serial_ &logSerial, int timeout);                                    //Method for initializing the UART and debug port
            void begin(UARTClass &serial, USARTClass &logSerial, int timeout);
            void begin(USARTClass &serial, Serial_ &logSerial, int timeout);
            void begin(USARTClass &serial, UARTClass &logSerial, int timeout);
            void begin(USARTClass &serial, USARTClass &logSerial, int timeout);
        #else 
            #ifdef HardwareSerial_h
                void begin(HardwareSerial &serial, int timeout);
                void begin(HardwareSerial &serial, HardwareSerial &logSerial, int timeout);
            #else
                #error No serial-class available
            #endif
        #endif

        typedef struct
        {
            byte b1;
            byte b2;
            byte b3;
            byte b4;
        } D_range;
        
        int readConcentrationPPM(byte sensor);                      //Function for reading the CO2-concentration in PPM
        void calZeroPoint(byte sensor);                             //Method to set the zero point (refere to manual)
        void calSpanPoint(byte sensor, uint32_t span_value_ppm);     //Method to set the zero span (refere to manual), span_value_ppm should be above 1000
        void setDetectionRange(byte sensor);
        void setDetectionRange(byte sensor, D_range range);
        void setAutoCal(byte sensor, bool state);
        void setDebug(bool state);                                  //Method to set the debug mode if debug port is specified
        const D_range MR_2000 = {0x00, 0x00, 0x07, 0xD0};
        const D_range MR_5000 = {0x00, 0x00, 0x13, 0x88};
        const D_range MR_10000 = {0x00, 0x00, 0x27, 0x10}; 
    private:
        byte crc(byte msg[9]);                                      //Function to calculate the checksum
        void log(byte msg[9]);                                      //Method to send the debug messages to the serial interface
        Stream* ser;
        Stream* logSer;
        bool canDebug = false;
        bool debug = false;
        bool hwser = false;
};
