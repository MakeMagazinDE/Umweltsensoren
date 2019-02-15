/*
 * Sensor MQ-9
 * Gas
 * Analoge Messung an A0
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * http://wiki.seeedstudio.com/Grove-Gas_Sensor-MQ9/
 * https://duckduckgo.com/?q=%22mq-9%22+gas+sensor+filetype%3Apdf&ia=web
 * https://playground.arduino.cc/Main/MQGasSensors
 * 
 */

//#define REFERENCE   // einmal kalibrieren bei sauberer Luft und R0 auslesen. Dann auskommentieren und R0 in zweiten Programmblock einsetzen
#define GRAPH         // wenn definiert, wird ein Graph gezeichnet. Für ersten Test auskommentieren

 void setup() {
    Serial.begin(9600);
}


void loop() 
{
#ifdef REFERENCE
    float sensor_volt;
    float RS_air; //  Get the value of RS via in a clear air
    float R0;  // Get the value of R0 via in LPG
    float sensorValue;

    /*--- Get a average data by testing 100 times ---*/
    for(int x = 0 ; x < 100 ; x++)
    {
        sensorValue = sensorValue + analogRead(A0);
    }
    sensorValue = sensorValue/100.0;
    /*-----------------------------------------------*/

    sensor_volt = sensorValue/1024*5.0;
    RS_air = (5.0-sensor_volt)/sensor_volt; // omit *RL
    R0 = RS_air/9.9; // The ratio of RS/R0 is 9.9 in LPG gas from Graph (Found using WebPlotDigitizer)

    Serial.print("sensor_volt = ");
    Serial.print(sensor_volt);
    Serial.println("V");

    Serial.print("R0 = ");
    Serial.println(R0);
    delay(1000);
#endif 

#ifndef REFERENCE
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL

          /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
    float R0 = 2.76;
    ratio = RS_gas/R0;  // ratio = RS/R0
          /*-----------------------------------------------------------------------*/
#ifdef GRAPH
    Serial.println(RS_gas);
#else
    Serial.print("sensor_volt = ");
    Serial.println(sensor_volt);
    Serial.print("RS_ratio = ");
    Serial.println(RS_gas);
    Serial.print("Rs/R0 = ");
    Serial.println(ratio);

    Serial.print("\n\n");
#endif

    delay(1000);
#endif
}
