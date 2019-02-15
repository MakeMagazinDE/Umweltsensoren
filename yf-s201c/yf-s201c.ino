/*
 * Sensor YF-S201C
 * Durchflussmenge
 * gelb: Pin 2 
 * GND + VCC (5V)
 * 
 * Achtung: Konvertierungsfaktor anpassen
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * https://forum.seeedstudio.com/viewtopic.php?f=4&t=989&p=3632
 * 
 */

int signalInput = 2;
long count = 0;
long countPerSecond;
long timePreviousMeassure = 0;
float LiterMinute;

void countPulse(){
  detachInterrupt(0);
  count++;
  while(!digitalRead(signalInput));
  attachInterrupt(digitalPinToInterrupt(signalInput), countPulse, FALLING);
}

void setup() 
{
  pinMode(signalInput, INPUT_PULLUP);     // Pullup aktiv
  attachInterrupt(digitalPinToInterrupt(signalInput), countPulse, FALLING);
  Serial.begin(115200);
}

void loop() 
{
  if (millis()-timePreviousMeassure >= 500)             // alle 0,5 Sekunden
  {
    countPerSecond = count * 2;     // = Hz
    LiterMinute = countPerSecond / 5.0;
    timePreviousMeassure = millis();
    Serial.print(countPerSecond, DEC);
    Serial.print(" Hz \t=\t"); 
    Serial.print(LiterMinute,2);      
    Serial.println(" L/min");
    count = 0;
  }
}
