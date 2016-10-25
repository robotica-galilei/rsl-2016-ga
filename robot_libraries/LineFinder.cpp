#include <LineFinder.h>
#include "Arduino.h"
#define WHT 0.2
#define BLK 0.5

void LineFinder::init(int line_pins[],int maxValue,long min_vals[],long max_vals[])
{
  _maxValue=maxValue;
	for(i=0;i<8;i++)
	{
    _pins[i]=line_pins[i];
		_min_vals[i]=min_vals[i];
		_max_vals[i]=max_vals[i];
	}
}


void LineFinder::ReadSensors(long times[]) {
  int i;
  for(i=0;i<8;i++)
  {
    times[i]=_maxValue;
    pinMode(_pins[i], OUTPUT);
    digitalWrite(_pins[i], HIGH);
  }
  delayMicroseconds(10);
  for(i=0;i<8;i++)
  {
    pinMode(_pins[i], INPUT);
    digitalWrite(_pins[i], LOW);
  }
  unsigned long startTime = micros();
  while (micros()-startTime<_maxValue)
  {
    unsigned int time= micros()-startTime;
    for (i=0;i<8;i++)
    {
      if (digitalRead(_pins[i])==LOW && time<times[i])
        times[i] = time;
    }
  }
}
float LineFinder::FindError(long vals[],float rap[], int* typ){
  sumRap=0;
  sumVal=0;
  for(i=0;i<8;i++)
  {
    long val= vals[i];
     rap[i]=(double)(val-_min_vals[i])/(_max_vals[i]-_min_vals[i]);

    //sumVal=sumVal+((i+1)*rap[i]);
    //Serial.print(rap[i]);
    //Serial.print("\t");
    //sumRap=sumRap+rap[i];
  }

  if(rap[0]<WHT&&rap[1]<WHT&&rap[2]<WHT&&rap[3]<WHT&&rap[4]<WHT&&rap[5]<WHT&&rap[6]<WHT&&rap[7]<WHT)
  {
  	error=0;
  	*typ=1;
	}
	else if(rap[0]>BLK&&rap[1]>BLK&&rap[2]>BLK&&rap[3]>BLK&&rap[4]>BLK&&rap[5]>BLK&&rap[6]>BLK&&rap[7]>BLK)
	{
      error=0;
      *typ=2;
  }
    /*
    else if(rap[0]>0.5&&rap[1]>0.5&&rap[2]>0.5&&rap[3]>0.5&&rap[6]<0.5&&rap[7]<0.5) //ATTENZIONE
    {
      *typ=3;
      error=-1;
    }
    else if(rap[4]>0.5&&rap[5]>0.5&&rap[6]>0.5&&rap[7]>0.5&&rap[0]<0.5&&rap[1]<0.5)//ATTENZIONE
    {
     *typ=3;
     error=1;
    }
    */
	else{

    for(int i=0;i<8;i++)
    {
     if(rap[i]<0)
       rap[i]=0;
    }


		//error =(float)(sumVal/sumRap)-4.5;
	error=-(float)((rap[0]*4+rap[1]*3+rap[2]*2+rap[3])-(rap[4]+rap[5]*2+rap[6]*3+rap[7]*4));
      *typ=0;
	}
	//Serial.print(*typ);
	//Serial.println();
  return error;

}
