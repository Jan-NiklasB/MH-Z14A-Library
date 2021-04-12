
/*
    MH-Z14A Library by Jan-Niklas Bogatka is licensed under CC BY-NC-SA 4.0.
    To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0
*/

#include "MH-Z14A.h"

typedef struct
{
    byte b1;
    byte b2;
    byte b3;
    byte b4;
} D_range;
 

MHZ14A::MHZ14A()
{
}

#if (defined _UART_CLASS_) && (defined _USART_CLASS_) && (defined _USBAPI_)
void MHZ14A::begin(UARTClass &serial, int timeout)
{
    ser = &serial;
    ser->setTimeout(timeout);
}

void MHZ14A::begin(USARTClass &serial, int timeout)
{
    ser = &serial;
    ser->setTimeout(timeout);
}

void MHZ14A::begin(UARTClass &serial, Serial_ &logSerial, int timeout)
{
    ser = &serial;
    logSer = &logSerial;
    canDebug = true;
    ser->setTimeout(timeout);
}

void MHZ14A::begin(UARTClass &serial, USARTClass &logSerial, int timeout)
{
    ser = &serial;
    logSer = &logSerial;
    canDebug = true;
    ser->setTimeout(timeout);
}

void MHZ14A::begin(USARTClass &serial, Serial_ &logSerial, int timeout)
{
    ser = &serial;
    logSer = &logSerial;
    canDebug = true;
    ser->setTimeout(timeout);
}

void MHZ14A::begin(USARTClass &serial, UARTClass &logSerial, int timeout)
{
    ser = &serial;
    logSer = &logSerial;
    canDebug = true;
    ser->setTimeout(timeout);
}

void MHZ14A::begin(USARTClass &serial, USARTClass &logSerial, int timeout)
{
    ser = &serial;
    logSer = &logSerial;
    canDebug = true;
    ser->setTimeout(timeout);
}

#else
#ifdef HardwareSerial_h

void MHZ14A::begin(HardwareSerial &serial, int timeout)
{
    ser = &serial;
    hwser = true;
    ser->setTimeout(timeout);
}

void MHZ14A::begin(HardwareSerial &serial, HardwareSerial &logSerial, int timeout)
{
    ser = &serial;
    logSer = &logSerial;
    canDebug = true;
    hwser = true;
    ser->setTimeout(timeout);
}

#endif
#endif

void MHZ14A::setDebug(bool state)
{
    if(canDebug) debug = state;
    else debug = false;
}

void MHZ14A::log(byte msg[9])
{
    if(debug) 
    {
        for(int i=0; i<9; i++) logSer->print(msg[i], HEX);
        logSer->println("");       
    }
}

byte MHZ14A::crc(byte msg[9])
{   
    byte chksum = 0;
    for(int i=1; i<8; i++)
    {
        chksum += msg[i];
    }
    chksum = 0xff - chksum;
    chksum += 1;
    return chksum;
}

int MHZ14A::readConcentrationPPM(byte sensor = 0x01)
{
    byte msg[] = {0xFF, sensor, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    byte msgr[] = {0,0,0,0,0,0,0,0,0};
    int concentrationPPM;
    msg[8] = crc(msg);
    log(msg);
    ser->write(msg, 9);
    //int timeout = 60;
    ser->readBytes(msgr, 9);
    log(msgr);
    if (msgr[0] != 0xFF) return -1;
    if(crc(msgr) == msgr[8]){
        concentrationPPM = int(msgr[2]) * 256 + int(msgr[3]);
    }
    else
    {
        concentrationPPM = -1;
    }
    
    return concentrationPPM;
}

void MHZ14A::calZeroPoint(byte sensor = 0x01)
{
    byte msg[9] = {0xFF, sensor, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    msg[8] = crc(msg);
    ser->write(msg, 9);
}

void MHZ14A::calSpanPoint(byte sensor = 0x01, uint32_t span_value_ppm = 2000)
{
    byte span_high = span_value_ppm / 256;
    byte span_low = span_value_ppm % 256;
    byte msg[9] = {0xFF, sensor, 0x88, span_high, span_low, 0x00, 0x00, 0x00, 0x00};
    msg[8] = crc(msg);
    ser->write(msg, 9);
}

void MHZ14A::setDetectionRange(byte sensor = 0x01)
{
    setDetectionRange(sensor, MR_5000);
}

void MHZ14A::setDetectionRange(byte sensor, D_range range)
{
    byte msg[9] = {0xFF, sensor, 0x99, 0x00, range.b1, range.b2, range.b3, range.b4, 0x00};
    msg[8] = crc(msg);
    ser->write(msg, 9);
}

void MHZ14A::setAutoCal(byte sensor, bool state)
{
    byte msg[9] = {0xFF, sensor, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    if (state)
    {
        msg[3] = 0xA0;
    }
    else
    {
        msg[3] = 0x00;
    }
    msg[8] = crc(msg);
    ser->write(msg, 9);
}
