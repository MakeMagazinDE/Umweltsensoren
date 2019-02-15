/*
 * Sensor M4011
 * Strahlung
 * INT: Pin 2 (auf der Platine steht "VIN")
 * GND + VCC (5V)
 * 
 * Achtung: Konvertierungsfaktor anpassen
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * https://drive.google.com/drive/folders/0B9itH-BnWE5sY2JGRkM4MWhSYkE
 * https://www.cooking-hacks.com/documentation/tutorials/geiger-counter-radiation-sensor-board-arduino-raspberry-pi-tutorial
 * https://github.com/RH-Electronics/Geiger_Counter_Serial_Arduino/blob/master/newGeiger.ino
 * 
 */

#define CONV_FACTOR 0.0066225     // Conversion factor - CPM to uSV/h     // The GM tube M4011 conversion index is 151, which means that: 151CPM=1μSv/h. => 1/CPM

int geiger_input = 2;
long count = 0;
long countPerMinute = 0;
long timePreviousMeassure = 0;
long countPrevious = 0;
float radiationValue = 0.0;

void countPulse(){
  detachInterrupt(0);
  count++;
  while(!digitalRead(geiger_input));
  attachInterrupt(digitalPinToInterrupt(geiger_input), countPulse, FALLING);
}

void setup() 
{
  pinMode(geiger_input, INPUT);
  attachInterrupt(digitalPinToInterrupt(geiger_input), countPulse, FALLING);
  Serial.begin(115200);
}

void loop() 
{
  if (millis()-timePreviousMeassure >= 5000)             // alle 5 Sekunden
  {
    countPerMinute = 12*count;                          // 60 Sekunden / alle 5 Sekunden = 12
    radiationValue = countPerMinute * CONV_FACTOR;
    timePreviousMeassure = millis();
    Serial.print(countPerMinute,DEC);
    Serial.print(" cpm \t=\t"); 
    Serial.print(radiationValue,4);      
    Serial.println(" µSv/h");
    count = 0;
  }
}
