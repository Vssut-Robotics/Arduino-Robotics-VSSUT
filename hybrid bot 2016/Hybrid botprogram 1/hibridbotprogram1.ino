//pinconfiguration
int fld=12;
int flp=13;
int bld=8;
int blp=9;

int frd=10;
int frp=11;
int brd=6;
int brp=7;

//EDF
int edf=3;
int sp=0;
//ultrasonic;
int trig=5;
int echo=17;
int duration;
int dis;

//linear actuator
int exd1=25;
int exd2=33;
int upd1=37;
int upd2=45;

//ps2
#include <PS2X_lib.h>
//#include <SoftwareSerial.h> 
#define PS2_DAT        50 //14    
#define PS2_CMD        51  //15
#define PS2_SEL        53  //16
#define PS2_CLK        52  //17

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

int error = 0;
byte type = 0;
byte vibrate = 0;
int rx,ry,lx,ly;
int val;
