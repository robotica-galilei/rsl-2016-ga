#ifndef PID_H
#define PID_H

#include "Arduino.h"

class PID
{
   private:
	float _Kp,_Ki,_Kd;
	float P,I,D,PID_value;
	float previous_error,error;

   public:
	void init(int Kp,int Ki, int Kd);
    float Compute(float error);
    void ResetIntegral(void);
};

#endif
