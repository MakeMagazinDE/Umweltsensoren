/*
 * Niederschlagsmenge
 * 
 * GND
 * Pin 2
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * https://www.mysensors.org/build/rain
 * https://www.instructables.com/id/Arduino-Rain-Gauge-Calibration/
 * 
 */

const uint8_t RainPin = 2;
const uint8_t LEDPin = 13;

void setup(void) {
  pinMode(LEDPin, OUTPUT);
  pinMode(RainPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RainPin), ISR_BucketFull, FALLING );
}

void ISR_BucketFull () {
  digitalWrite(LEDPin, !digitalRead(LEDPin));   // LED bei jedem Kippen umschalten
}

void loop(void){
  // noting to do
}

