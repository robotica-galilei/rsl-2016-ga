#ifndef Light_H
#define Light_H

#include "Arduino.h"

class Light
{
   private:
      int _pins[8],maxValue;

   public:
      void init(int pins[],int timeout);
      int readSensors(long times[]);
      long readSensor(int n);
};

#endif
