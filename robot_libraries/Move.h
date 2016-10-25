#ifndef Move_H
#define Move_H

#include "Arduino.h";

class Move
{
  private:
    int _pinA_1,_pinA_2,_pinB_1,_pinB_2,_maxspeed;
  public:
    void init(int pinA_1,int pinA_2,int pinB_1,int pinB_2,int maxspeed);
    void setspeeds(int v1,int v2);
    void sprint();
    void stop();
    void clock();
    void counterclock();
};

#endif
