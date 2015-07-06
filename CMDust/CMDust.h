
 #include "Arduino.h"



class Dust {

 private:
uint8_t pin;
byte _buff[2];
int pinDust = 14;//DSM501A input D8
unsigned long duration,starttime,endtime,sampletime_ms = 30000,lowpulseoccupancy = 0;
float ratio = 0,concentrations = 0;
int i=0;   


 public:


 Dust(uint8_t pPin);
 Dust(uint8_t pPin,float pSampletime_ms);
float read_dust(void);
float get_ratio(void);

};

