#ifndef _DS3231_H_
#define _DS3231_H_

#include <Arduino.h>
//#include <inttypes.h>

#define DS3231_ADDRESS 0X68

#define CONTROL_REG 0X0E
#define STATUS_REG 0X0F
#define ALARM1_IE 0X01
#define ALARM2_IE 0X02
#define INT_ENABLE 0X04
#define ALARM1_IF 0X01
#define ALARM2_IF 0X02
#define CLOCK 0X00
#define DATE 0X03
#define ALARM1 0X07
#define ALARM2 0X0B


class DS3231 {

  public:
    void readRTC();
    void printHex(uint8_t);

    void  enableInterrupt();
    void disableInterrupt();

    void clearAlarm(uint8_t);
    void enableInterruptAlarm(uint8_t);
    void disableInterruptAlarm(uint8_t);
    void setAlarm1(uint8_t day, uint8_t hours, uint8_t mint, uint8_t sec = 0);
    void setAlarm2(uint8_t day,uint8_t hours, uint8_t mint, uint8_t sec=0);
    //void setAlarm2(unsigned char, unsigned char, unsigned char, unsigned char);

    uint8_t readRegister(uint8_t);
    void writeRegister(uint8_t, uint8_t);
    uint8_t readStatus();
    void writeStatus(uint8_t);
    uint8_t readControl();
    void writeControl(uint8_t);

};

#endif
