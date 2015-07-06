/* DHT library 

MIT license
written by Adafruit Industries
*/

#include "CMDust.h"

 Dust::Dust(uint8_t pPin) {
  pin = pPin;
 
}

 Dust::Dust(uint8_t pPin,float pSampletime_ms) {
  pin = pPin;
  sampletime_ms = pSampletime_ms;
 
}



float Dust::  read_dust()
{
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy += duration;
  endtime = millis();  
  if ((endtime-starttime) > 1000)
  {
    Serial.print(duration);
       Serial.print(",");
  }
  if ((endtime-starttime) > sampletime_ms)
  {
    ratio = (lowpulseoccupancy-endtime+starttime + sampletime_ms)/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentrations = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    lowpulseoccupancy = 0;
    starttime = millis();      
  }
   return concentrations;
}


float Dust:: get_ratio()
{

   return ratio ;

}
