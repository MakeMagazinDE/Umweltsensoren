/*
 * Sensor MQ-135
 * Gas
 * Analoge Messung: A0
 * Digitales Signal: D2
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * http://davidegironi.blogspot.com/2014/01/cheap-co2-meter-using-mq135-sensor-with.html
 * https://www.waveshare.com/wiki/MQ-135_Gas_Sensor
 * https://duckduckgo.com/?q=%22mq135%22+gas+sensor+filetype%3Apdf&ia=web
 * https://playground.arduino.cc/Main/MQGasSensors
 * 
 */

int gas_din=2;
int gas_ain=A0;
int ad_value;
void setup()
{
  pinMode(gas_din,INPUT);
  pinMode(gas_ain,INPUT);
  Serial.begin(9600);
}
void loop()
{
  ad_value=analogRead(gas_ain);
  Serial.print("Value:\t");
  Serial.print(ad_value);
  if(digitalRead(gas_din)==LOW)
    Serial.println("\tGas leakage");
  else
    Serial.println("\tGas not leak");
  delay(1000);
}
