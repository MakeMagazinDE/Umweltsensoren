/*
 * Sensor TSL2581
 * Lux
 * INT: Pin 13 (wird hier nicht genutzt!)
 * 
 * Achtung: Gain ist auf Faktor 1 eingestellt. Hier und in TSL2581.cpp anpassen
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * https://www.waveshare.com/wiki/Light_Sensor
 * 
 */

#include <Wire.h>
#include "TSl2581.h"

WaveShare_TSL2581 tsl = WaveShare_TSL2581();

void read_id(void)
{
  int   id;
  int a;
  id = tsl.TSL2581_Read_ID();
  a = id & 0xf0;      //The lower four bits are the silicon version number
  if (!(a == 144))    //ID = 90H = 144D
  {
    Serial.println("false ");
  } else {
    Serial.print("I2C DEV is working ,id = ");
    Serial.println(id);
    delay(500);
  }
}

void setup(void)
{
  Serial.begin(115200);
  Wire.begin();                     //i2c config

  read_id();
  tsl.TSL2581_power_on();           /* Setup the sensor power on */
  delay(2000);
  tsl.TSL2581_config();             //  /* Setup the sensor gain and integration time */
}

void loop(void)
{
  unsigned long Lux;
  tsl.TSL2581_Read_Channel();
  Lux = tsl.calculateLux(GAIN_1X, NOM_INTEG_CYCLE);     // Gain anpassen

  Serial.print("Lux = " );
  Serial.println(Lux);
  delay(50);
}

