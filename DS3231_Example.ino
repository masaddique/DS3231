#include <ADXL355.h>
#include "DS3231.h"
#include <Wire.h>
#include <avr/sleep.h>

ADXL355 dev(0X1D);
DS3231 rtc;
bool printRes = true;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Started");
  attachInterrupt(digitalPinToInterrupt(2), intFunction, FALLING);
  dev.enable(0X00);
  rtc.setAlarm1(0X80, 0X80, 0X80, 0X48);
  rtc.setAlarm2(0X80, 0X80, 0X28);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);
  rtc.readRTC();
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void loop() {
  // put your main code here, to run repeatedly:
  //rtc.readRTC();
  //Serial.println();
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
  if (printRes) {
    printRes = true;
    printResults();
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
  }
  delay(1000);
}

void serialEvent()
{
  while (Serial.available())
  {
    Serial.println(Serial.read());
  }
}

void intFunction(void) {
  sleep_disable();
}

void printResults(void) {

  rtc.readRTC();
  Serial.println();
  Serial.print("Temperature: ");
  Serial.println(dev.readTemperature());

  Serial.print(dev.readX()); Serial.print(",");
  Serial.print(dev.readY()); Serial.print(",");
  Serial.print(dev.readZ());
  Serial.println();

  Serial.println(dev.tilt());
  Serial.println(dev.pitch());
  Serial.println(dev.roll());

  rtc.printHex(rtc.readStatus());
  Serial.println();

  rtc.clearAlarm(1);
  rtc.clearAlarm(2);
  //delay(1000);
}
