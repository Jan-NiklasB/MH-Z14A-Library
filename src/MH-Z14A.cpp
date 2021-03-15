
/*
    MH-Z14A Library by Jan-Niklas Bogatka is licensed under CC BY-NC-SA 4.0.
    To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0
*/

#include "MH-Z14A.h"

MHZ14A::MHZ14A(HardwareSerial &serial)
{
    ser = &serial;
    canDebug = false;
}

MHZ14A::MHZ14A(HardwareSerial &serial, HardwareSerial &logSerial)
{
    ser = &serial;
    serIsUSB = false;
    logSer = &logSerial;
}

#if defined(Serial_)
MHZ14A::MHZ14A(HardwareSerial &serial, Serial_ &logSerial)
{
    ser = &serial;
    serIsUSB = true;
    logSerUSB = &logSerial;
}
#endif

void MHZ14A::begin(int timeout)
{
    ser->begin(9600);
    ser->setTimeout(timeout);
}

void MHZ14A::setDebug(bool state)
{
    if(canDebug) debug = state;
    else debug = false;
}

void MHZ14A::log(byte msg[9])
{
    if(debug) 
    {
        if(!serIsUSB) for(int i=0; i<9; i++) logSer->print(msg[i], HEX);
        else
        {
            #if defined(Serial_)
                for(int i=0; i<9; i++) logSerUSB->print(msg[i], HEX);
            #endif
        }
        if(!serIsUSB) logSer->println("");
        else
        {
            #if defined(Serial_)
                logSerUSB->println("");
            #endif
        } 
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
    int timeout = 60;
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

void MHZ14A::calSpanPoint(byte sensor = 0x01, uint8_t span_value_ppm = 2000)
{
    byte span_high = span_value_ppm / 256;
    byte span_low = span_value_ppm % 256;
    byte msg[9] = {0xFF, sensor, 0x88, span_high, span_low, 0x00, 0x00, 0x00, 0x00};
    msg[8] = crc(msg);
    ser->write(msg, 9);
}

void MHZ14A::setDetectionRange(byte sensor = 0x01, byte Range[4])
{
    byte msg[9] = {0xFF, sensor, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i=4; i<8; i++)
    {
        msg[i] = Range[i-4];
    }
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
