#include <Light.h>
#include "Arduino.h"

void Light::init(int pins[],int timeout)
{
     int i;
	for(i=0;i<8;i++)
	{
		_pins[i]=pins[i];
	}
	maxValue=timeout;
}

long Light::readSensor(int n)
{
  pinMode(_pins[n],OUTPUT);
  digitalWrite(_pins[n],HIGH);
  delayMicroseconds(15);
  pinMode(_pins[n],INPUT);
  digitalWrite(_pins[n],LOW);
  unsigned long startTime=micros();
  while(digitalRead(_pins[n])!=LOW){
  }
  return micros()-startTime;
}

int Light::readSensors(long times[])
{
    int i;
    for(i=0;i<8;i++)
    {
        times[i]=maxValue;
        digitalWrite(_pins[i], HIGH);   
        pinMode(_pins[i], OUTPUT);      
    }
    delayMicroseconds(10);              
    for(i=0;i<8;i++)
    {
        pinMode(_pins[i], INPUT);     
        digitalWrite(_pins[i], LOW);        
    }
    unsigned long startTime = micros();
    while (micros()-startTime<maxValue)
    {
        unsigned int time= micros()-startTime;
        for (i=0;i<8;i++)
        {
            if (digitalRead(_pins[i])==LOW&& time<times[i])
                times[i] = time;
        }
    }
}
