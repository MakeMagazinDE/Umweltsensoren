/*
 * Sensor TX 20
 * Windrichtung und Geschwindigkeit
 * Nutzt invertierte Signalpegel, da mit Transistor Pegel von 2V auf 5V angehoben werden
 * 
 * Make: www.make-magazin.de
 * Florian Schäffer
 *
 * https://www.john.geek.nz/2011/07/la-crosse-tx20-anemometer-communication-protocol/
 * http://fabrizio.zellini.org/decoding-la-crosse-tx20-anemometer-with-arduino
 * https://github.com/bunnyhu/ESP8266_TX20_wind_sensor/blob/master/tx20_v3.ino
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
 
unsigned int icr1;
volatile int rx=0;
volatile int bitcount=0;
volatile char pin;
volatile unsigned char sa,sb,sd,se;
volatile unsigned int sc,sf;
char* wind[] = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};
  
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
 
  EICRA  = _BV(ISC01);    // set INT0 to trigger on falling edge
  EIMSK = _BV(INT0);     // Turns on INT0
 
  icr1 = 19500;
 
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B
  OCR1A = icr1;
}
 
void loop(){
  char a[90];
  unsigned char chk;
  char str_temp[6];
 
  // Main code loop
  // TODO: Put your regular (non-ISR) logic here
 
  if (rx){
    chk= ( sb + (sc&0xf) + ((sc>>4)&0xf) + ((sc>>8)&0xf) );chk&=0xf;
    if (sa==4 && sb==se && sc==sf && sd==chk){      
      dtostrf((float)(sc*.1), 4, 2, str_temp);      // %f not included in Arduino's sprintf
      sprintf (a,"Dir.: %d = %s\t\tSpeed:\t%d = %s m/s\n", sb, wind[sb], sc, str_temp);
      Serial.write (a);
    }
    rx=0;
  }
}
 
// pin change interrupt ( start of frame )
ISR (INT0_vect){
 
  // reset accumulators
  sa=sb=sd=se=0;
  sc=0;sf=0;
 
  EIMSK &= ~_BV(INT0);     // disable pin interrupt
 
  bitcount=41;
 
  TCCR1B = 0; // stop timer
  TCNT1 = icr1>>1; // set counter
  TIFR1 |= _BV(OCF1A); // clear timer interrupt
  TCCR1B = _BV(WGM12)| _BV(CS10); // start timer
  TIMSK1 |= _BV(OCIE1A);  // enable timer interrupt
 
}
 
// timer irq ( bit accumulator )
ISR(TIMER1_COMPA_vect){
 
  if (bitcount==1){
    TIMSK1 &= ~_BV(OCIE1A); // disable timer interrupt
    EIFR |= _BV(INTF0);     // clear pin interrupt flag
    EIMSK = _BV(INT0);      // enable pin interrupt flag for next frame
 
  }
  if (bitcount>0){
    pin = digitalRead(2);
 
    if (bitcount > 41-5){
      // start
      sa = (sa<<1)|pin;
    } else
    if (bitcount > 41-5-4){
      // wind dir
      sb = sb>>1 | (pin<<3);
    } else
    if (bitcount > 41-5-4-12){
      // windspeed
      sc = sc>>1 | (pin<<11);
    } else
    if (bitcount > 41-5-4-12-4){
      // checksum
      sd = sd>>1 | (pin<<3);
    } else 
    if (bitcount > 41-5-4-12-4-4){
      // wind dir, inverted
      se = se>>1 | ((pin^1)<<3);
    } else {
      // windspeed, inverted
      sf = sf>>1 | ((pin^1)<<11);
    }     
 
    bitcount--;
    if (bitcount==0){
      // all data received:
      rx=1;
    }
  } 
}
