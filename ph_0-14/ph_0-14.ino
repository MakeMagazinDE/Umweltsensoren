/*
 * Sensor PH 0-14
 * pH
 * 
 * T0: Temperatur Ausgang
 * D0: Alarm-Signal (Schwellwert mit Poti nahe Pinlkeiste einstellbar)
 * P0: pH-Wert, analog => A0
 * 2x GND
 * VCC: 5 V
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * https://www.nextiafenix.com/wp-content/uploads/2018/06/PH-4502C_9.jpg
 * https://www.botshop.co.za/how-to-use-a-ph-probe-and-sensor/
 * https://scidle.com/how-to-use-a-ph-sensor-with-arduino/
 * https://de.wikipedia.org/wiki/Glaselektrode
 * 
 */

const float calibration = 21.3;
int sensorValue;
float voltage;

void setup() {
  Serial.begin(115200);
}

void loop() {
  sensorValue = analogRead(A0);
  voltage = sensorValue * (5.0 / 1023.0);
  Serial.print (voltage);
  Serial.print (" V\tpH ");
  Serial.println (-5.70 * voltage + calibration);
  delay(500);
}
