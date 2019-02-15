/*
 * Sensor VEML6075
 * UV
 * I²C
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * https://learn.adafruit.com/adafruit-veml6075-uva-uvb-uv-index-sensor?view=all
 * https://www.vishay.com/docs/84304/veml6075.pdf
 * 
 */
 
 
 /*!
 * @file veml6075_fulltest.ino
 *
 * A complete test of the library API with various settings available
 * 
 * Designed specifically to work with the VEML6075 sensor from Adafruit
 * ----> https://www.adafruit.com/products/3964
 *
 * These sensors use I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface with the breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */
 
#include <Wire.h>
#include "Adafruit_VEML6075.h"

Adafruit_VEML6075 uv = Adafruit_VEML6075();

void setup() {
  Serial.begin(115200);
  if (! uv.begin()) {
    Serial.println("Failed to communicate with VEML6075 sensor, check wiring?");
  }
  Serial.println("Found VEML6075 sensor");
  
  uv.setIntegrationTime(VEML6075_100MS);          // Set the integration constant
  uv.setHighDynamic(false);                         // Set the high dynamic mode
  uv.setForcedMode(false);                        // Set the mode

  // Set the calibration coefficients
  uv.setCoefficients(2.22, 1.33,  // UVA_A and UVA_B coefficients
                     2.95, 1.74,  // UVB_C and UVB_D coefficients
                     0.001461, 0.002591); // UVA and UVB responses
}


void loop() {
  Serial.print("UVA: "); Serial.print(uv.readUVA());
  Serial.print("\tUVB: "); Serial.print(uv.readUVB());
  Serial.print("\tUV Index: "); Serial.println(uv.readUVI());
  delay(1000);
}
