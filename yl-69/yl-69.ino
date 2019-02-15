/*
 * Sensor YL-69, YL-38 und andere
 * Feuchte
 * 
 * D0: Analoges Signal => A4
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * https://www.waveshare.com/wiki/Moisture_Sensor
 * https://randomnerdtutorials.com/guide-for-soil-moisture-sensor-yl-69-or-hl-69-with-the-arduino/
 * https://www.waveshare.com/wiki/Liquid_Level_Sensor
 * https://duckduckgo.com/?q=yl-38&t=ffsb&iax=images&ia=images
 * 
 */

const int feuchte = A4;

void setup() {
  Serial.begin(115200);
  pinMode(feuchte, INPUT);
}

void loop() {
  Serial.println (analogRead(feuchte));
  delay (500);
}
