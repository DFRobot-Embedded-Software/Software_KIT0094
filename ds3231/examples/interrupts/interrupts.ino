/*!
 * @file interrupts.ino
 * @brief Interrupts for Battery management/saving using MCU power down mode. /INT from DS3231 is connected to INT0 of MCU.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.0
 * @date  2023-12-14
 */
#include <avr/sleep.h>
#include <Wire.h>
#include "DS3231.h"

DS3231 RTC; //Create the DS3231 object
static uint8_t prevSecond=0; 

#define INT_PIN 10

void setup () 
{
     /*Initialize INT0 for accepting interrupts */
#if 0
     PORTD |= 0x04; 
     DDRD &=~ 0x04;
#endif
     uint8_t regValue;
     Serial.begin(57600);
     Wire.begin();
    
     RTC.begin();
     //attachInterrupt(INT_PIN, INT0_ISR, FALLING); 


     regValue = RTC.readRegister(DS3231_CONTROL_REG);
     RTC.writeRegister(DS3231_CONTROL_REG, (regValue | 0b01000000));
     Serial.println(RTC.readRegister(DS3231_CONTROL_REG), BIN);
     
     //Enable Interrupt 
     RTC.enableInterrupts(EverySecond); //interrupt at  EverySecond, EveryMinute, EveryHour

     pinMode(INT_PIN, INPUT);
     PCattachInterrupt(INT_PIN);

     // or this
     //RTC.enableInterrupts(18,4,0);    // interrupt at (h,m,s)
}


void loop () 
{

    DateTime now = RTC.now(); //get the current date-time    
    if((now.second()) !=  prevSecond )
    {
    //print only when there is a change in seconds
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
    Serial.println(' ');
    }
    prevSecond = now.second();
    RTC.clearINTStatus();
 
} 

  
//Interrupt service routine for external interrupt on INT0 pin conntected to /INT
void INT0_ISR()
{
  //Keep this as short as possible. Possibly avoid using function calls
  
   Serial.println(" External Interrupt detected ");
}


void PCattachInterrupt(uint8_t pin) {
  uint8_t bit;
  uint8_t port;

  port = digitalPinToPort(pin);
  // map pin to PCIR register

  bit = digitalPinToBitMask(pin);

  switch (port)
  {
    case 2:  //PB
        PCMSK0 |= bit;       
        PCICR |= 0x01 << 0;
        break;

    default:
        ;//nothing
  }
  
}



/***ISR thread***/

ISR(PCINT0_vect)
{
    if ( digitalRead(INT_PIN) == LOW )
    {
       Serial.println("INT");
    }
}
