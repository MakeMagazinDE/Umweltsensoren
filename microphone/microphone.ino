/*
 * Electret Microphone
 * OPA344 
 * 
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * https://learn.sparkfun.com/tutorials/electret-mic-breakout-board-hookup-guide
 * 
 * 
 */

const int sensorPin = A0;    // select the input pin for the potentiometer

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print (1500);    // 2 Werte ausgeben, damit untere und obere Grenze definiert ist und sich die Skalierung der Y-Achse nicht immerzu ändert
  Serial.print (",");
  Serial.print (0);
  Serial.print (",");
  Serial.println (analogRead(sensorPin));
  delay(2);
}
