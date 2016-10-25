#include <PID.h>
#include "Arduino.h"

void PID::init(int Kp,int Ki, int Kd)
{
	_Kp=Kp;
	_Ki=Ki;
	_Kd=Kd;
	error=0;
	previous_error=0;
	P=0;
	I=0;
	D=0;
	PID_value=0;
}

float PID::Compute(float error)
{
	P = error;
	if((I>0&&error<0)||(I<0&&error>0))
	  I=0;
  I = I + error;
  D = error - previous_error;

  if(error<1&&error>-1)
   I=0;

  PID_value = (_Kp*P) + (_Ki*I) + (_Kd*D);

  previous_error=error;

  return PID_value;
}

void PID::ResetIntegral(void)
{
 I=0;
}
