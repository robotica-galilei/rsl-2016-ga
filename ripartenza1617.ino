#include <NewPing.h>
#include <LineFinder.h>
#include <Move.h>
#include <PID.h>
#include <Servo.h>

/*************************************/
//         COSTANTI GLOBALI          //
/*************************************/
#define basespeed 0 //Velocità base

#define pinA_1 0    //Pin motori
#define pinA_2 0
#define pinB_1 0
#define pinB_2 0

#define maxspeed 100   //Velocità massima in percentuale

#define maxValue 5000   //Valore massimo che i sensori di luce possono leggere

#define FRONTTRIGGER 0
#define FRONTECHO 0
#define MAXSONARDISTANCE 500
#define MINOBSTACLEDISTANCE 0
/*************************************/

/*************************************/
//        VARIABILI GLOBALI          //
/*************************************/
float error;
int pidVal;
int cases;
int conGreen=0;
/*************************************/

/*************************************/
//         VETTORI GLOBALI           //
/*************************************/
int line_pins[8]={0,0,0,0,0,0,0,0};
long times[8];
long minvals[8]={0,0,0,0,0,0,0,0};
long maxvals[8]={0,0,0,0,0,0,0,0};
float rap[8];
/*************************************/

/************************************/
//             VERDE                //
/************************************/
const float costanteverde1 = 0.4;
const float costanteverde2 = 0.4;

const byte sclPin = A7;  // pin scl                 I PIN NON VANNO CAMBIATI
const byte sdaPin = A4;  // pin sda

const byte sclPin2 = A5;  // pin scl
const byte sdaPin2 = A6;  // pin sda

bool verde1 = false;                  //1 SX, 2 DX
bool verde2 = false;
/************************************/


/*************************************/
//       ISTANZIAMENTO CLASSI       //
/*************************************/
LineFinder line;
PID pidous;
Move movements;
NewPing FrontSonar(FRONTTRIGGER,FRONTECHO,MAXSONARDISTANCE);
/************************************/


void verde(){   //1 SX, 2 DX
  int meta,o,v;
  leggiNANO(o,v);
  if(verde2){         //RIGHT
    if(o<=150)       //al massimo meta puo' essere 180 (positivo, altrimenti -180)
      meta=o+30;
    else
      meta=-330+o;  /////////////////////////////-180+30-(180-o)
    //rotateto(meta);
    movements.clock();
    while(o!=meta)  //o!=meta     FORSE E' MEGLIO UN RANGE!!
      leggiNANO(o,v);
    movements.stop();
  }

  else{                //LEFT
    if(o>-150)       //meta non sara' mai -180
      meta=o-30;
    else
      meta=330+o;     //////////////////////////180-(30-(o+180))
    //rotateto(meta);
    movements.counterclock();
    while(o!=meta)
      leggiNANO(o,v);
    movements.stop();
  }
}


bool isobstacle(){
  movements.sprint();
  delay(500);
  movements.setspeeds(-basespeed,-basespeed);
  delay(30);
  movements.stop();
  if(FrontSonar.convert_cm(FrontSonar.ping_median(3))>MINOBSTACLEDISTANCE)
    return true;
  return false;
}



void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  movements.init(pinA_1,pinA_2,pinB_1,pinB_2,maxspeed);
  line.init(line_pins,maxValue,minvals,maxvals);
  pidous.init(0,0,0);
}

void loop() {
  if(isobstacle());
  line.ReadSensors(times);
  error=line.FindError(times,rap,&cases);
  
  if(cases==0){
    pidVal=pidous.Compute(error);
    movements.setspeeds(basespeed+pidVal,basespeed-pidVal);
  }
  
  else if(cases==1){
    movements.sprint();
  }
  
  else{
    movements.stop();
    verde1=false;
    verde2=false;
    if(conGreen<5){
        for(int i=0;i<50 && !verde1 && !verde2;i++) {
          movements.setspeeds(-basespeed,-basespeed);
          get_Colors();
          get_Colors2();
        }
        conGreen++;
        if(verde1||verde2) {                   //se hai visto il verde ...
          conGreen=0;
          movements.setspeeds(basespeed,basespeed);
          delay(50);
          verde();
        }
      }
    else {                                //altrimenti vai dritto
      movements.setspeeds(basespeed,basespeed);
      delay(50);
      conGreen=0;
    }
  }
}
