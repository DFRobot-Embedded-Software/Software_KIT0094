/*!
 * @file example.ino
 * @brief This example  reads data from sensor and temperature and humidity from SHT1x Humidity and Temperature Sensor.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.0
 * @date  2023-12-14
 */

#include "public.h"

#include "dht.h"
#include <Wire.h>
//#include <BMP085.h>
#include "DFRobot_BMP280.h"
//#include "DS3231.h"
#include "LiquidCrystal_I2C.h"

#include "WeatherStation.h"

/**Config sensors of weather station**/
DataConfig a_dataConfigList[]=
{
    /* Date Type     ,    Sensor Type       , Pin   */
    {DATA_TEMPERATURE, FUNCTION_SENSOR_DHT22, 9},           //config temperature sensor
    {DATA_HUMIDITY, FUNCTION_SENSOR_DHT22, 9},              //config Humidity sensor
    {DATA_AIR_PRESSURE, FUNCTION_SENSOR_BMP280, PIN_I2C},   //config barmeter sensor
    //{DATA_PM10, FUNCTION_SENSOR_GP2Y1010, A0, A1},            //config dust sensor. if you add dust sensor,  remove the comment '//'  at the start of the line
};


/**main program**/
void setup() 
{           
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
//    DBG_BEGIN(9600);
//    DBG_PRINTLN("init");
  g_station.init(a_dataConfigList, sizeof(a_dataConfigList)/sizeof(DataConfig));
}

void loop() 
{   
  g_station.run();
}
