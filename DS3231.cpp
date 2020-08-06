#include "DS3231.h"
#include <Wire.h>

//void readRTC();
//void printHex(unsigned char);

void DS3231::readRTC() {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0X00);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS, 7);
  uint8_t c0 = Wire.available() ? Wire.read() : 0;
  uint8_t c1 = Wire.available() ? Wire.read() : 0;
  uint8_t c2 = Wire.available() ? Wire.read() : 0;
  uint8_t c3 = Wire.available() ? Wire.read() : 0;
  uint8_t c4 = Wire.available() ? Wire.read() : 0;
  uint8_t c5 = Wire.available() ? Wire.read() : 0;
  uint8_t c6 = Wire.available() ? Wire.read() : 0;
  printHex(c2); Serial.print(":");
  printHex(c1); Serial.print(":");
  printHex(c0); Serial.print("\t");
  printHex(c6); Serial.print("/");
  printHex(c5); Serial.print("/");
  printHex(c4);
}

void DS3231::enableInterrupt() {
  Wire.beginTransmission(DS3231_ADDRESS);
  uint8_t t = readStatus();
  writeStatus(t | INT_ENABLE);
}

void DS3231::disableInterrupt() {
  Wire.beginTransmission(DS3231_ADDRESS);
  uint8_t t = readStatus();
  writeStatus(t & ~INT_ENABLE);
}

void DS3231::setAlarm1(uint8_t day, uint8_t hours, uint8_t mint, uint8_t sec = 0)
{
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(ALARM1);
  Wire.write(sec);
  Wire.write(mint);
  Wire.write(hours);
  Wire.write(day);
  Wire.endTransmission();
  enableInterruptAlarm(1);
}

void DS3231::setAlarm2(uint8_t day, uint8_t hours, uint8_t mint, uint8_t sec = 0) {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(ALARM2);
  //Wire.write(sec);
  Wire.write(mint);
  Wire.write(hours);
  Wire.write(day);
  Wire.endTransmission();
  enableInterruptAlarm(2);
}

void DS3231::printHex(uint8_t c) {
  uint8_t lower = c & 0X0F;
  uint8_t upper = (c >> 4) & 0X0F;
  switch (upper)
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      Serial.print(upper);
      break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
      Serial.print(upper - 10 + 'A');
      break;
    default:
      Serial.print("X");
  }
  switch (lower)
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      Serial.print(lower);
      break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
      Serial.print(lower - 10 + 'A');
      break;
    default:
      Serial.print("X");
  }

}

void DS3231::clearAlarm(uint8_t t) {
  uint8_t a = readStatus();
  if (t == 1) {
    writeStatus(a & ~ALARM1_IF);
  } else if (t == 2) {
    writeStatus(a & ~ALARM2_IF);
  }
}

void DS3231::enableInterruptAlarm(uint8_t t) {
  uint8_t a = readControl();
  if (t == 1) {
    writeControl(a | ALARM1_IE);
  } else if (t == 2) {
    writeControl(a | ALARM2_IE);
  }
}

void DS3231::disableInterruptAlarm(uint8_t t) {
  uint8_t a = readControl();
  if (t == 1) {
    writeControl(a & ~ALARM1_IE);
  } else if (t == 2) {
    writeControl(a & ~ALARM2_IE);
  }
}

uint8_t DS3231::readRegister(uint8_t t) {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(t);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS, 1);
  return Wire.available() ? Wire.read() : (uint8_t)0;
}

void DS3231::writeRegister(uint8_t t, uint8_t d) {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(t);
  Wire.write(d);
  Wire.endTransmission();
}

uint8_t DS3231::readControl() {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(CONTROL_REG);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS, 1);
  return Wire.available() ? Wire.read() : (uint8_t)0;
}

void DS3231::writeControl(uint8_t d) {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(CONTROL_REG);
  Wire.write(d);
  Wire.endTransmission();
}


uint8_t DS3231::readStatus() {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(STATUS_REG);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS, 1);
  return Wire.available() ? Wire.read() : (uint8_t)0;
}

void DS3231::writeStatus(uint8_t d) {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(STATUS_REG);
  Wire.write(d);
  Wire.endTransmission();
}
