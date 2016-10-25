#ifndef LineFinder_H
#define LineFinder_H

#include "Arduino.h"

class LineFinder
{
   private:
     int _pins[8];
     float sumRap,sumVal,error;
     int i,_maxValue;
     long _min_vals[8],_max_vals[8];
   public:
   	 void init(int line_pins[],int maxValue,long min_vals[],long max_vals[]);
     float FindError(long vals[],float rap[],int* typ);
     void ReadSensors(long times[]);
};

#endif
