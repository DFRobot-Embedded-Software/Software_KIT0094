/*!
 * @file now.ino
 * @brief Date and time functions using RX8025 RTC connected via I2C and Wire lib
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.0
 * @date  2023-12-14
 */
#include <Wire.h>
#include "DS3231.h"

char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

DS3231 RTC; //Create the R8025 object

void setup () 
{
    Serial.begin(57600);
    Wire.begin();
    RTC.begin();
}

void loop () 
{
    DateTime now = RTC.now(); //get the current date-time
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.date(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print(' ');
    Serial.print(weekDay[now.dayOfWeek()]);
    Serial.println();
    Serial.print("Seconds since 1/1/2000: "); 
    //print time stamp as 'long'. 
    Serial.print(now.get(),DEC);
    //This is useful token for datalogging 
    Serial.println();
    delay(1000);
}
