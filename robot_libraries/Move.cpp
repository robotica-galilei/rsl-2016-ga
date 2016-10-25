#include <Move.h>
#include "Arduino.h"


void Move::init(int pinA_1,int pinA_2,int pinB_1,int pinB_2,int maxspeed){
  _pinA_1=pinA_1;
  _pinA_2=pinA_2;
  _pinB_1=pinB_1;
  _pinB_2=pinB_2;
  _maxspeed=map(maxspeed,0,100,0,255);
  pinMode(_pinA_1,OUTPUT);
  pinMode(_pinA_2,OUTPUT);
  pinMode(_pinB_1,OUTPUT);
  pinMode(_pinB_2,OUTPUT);
}

void Move::setspeeds(int v1,int v2) {
  int v1_abs=map(abs(v1),0,100,0,255);
  int v2_abs=map(abs(v2),0,100,0,255);
  if(v1_abs>_maxspeed) v1_abs=_maxspeed;
  if(v2_abs>_maxspeed) v2_abs=_maxspeed;
  if(v2<0){
    analogWrite(_pinA_1,v2_abs/*/divSPM0*/);
    analogWrite(_pinA_2,0);
  }
  else{
    analogWrite(_pinA_1,0);
    analogWrite(_pinA_2,v2_abs/*/divSPM0*/);
  }

  if(v1>0){
    analogWrite(_pinB_1,0);
    analogWrite(_pinB_2,v1_abs);
  }
  else{
    analogWrite(_pinB_1,v1_abs);
    analogWrite(_pinB_2,0);
  }
}

void Move::sprint(){
  Move::setspeeds(_maxspeed,_maxspeed);
}

void Move::stop(){
  Move::setspeeds(0,0);
}

void Move::clock(){
  Move::setspeeds(40,-40);
}

void Move::counterclock(){
  Move::setspeeds(-40,40);
}
