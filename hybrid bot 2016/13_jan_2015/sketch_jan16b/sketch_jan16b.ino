#include <PS2X_lib.h>  //for v1.6
#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
const int p=0; 
int pos=0;
int c=0;
PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;
int x1=127,y1=127,x2=127,y2=127;

int pwr1=14;
int pwr2=15;
int vel=60;

int fld=12;
int flp=13;
int bld=8;
int blp=9;

int frd=10;
int frp=11;
int brd=6;
int brp=7;
//---------------
//ultrasonic;
int trig=5;
int echo=17;
int duration;
int dis;

//linear actuator
int exd1=25;
int exd2=33;
int upd1=45;
int upd2=37;
//-------------

void stp()
{
  digitalWrite(exd1,LOW);
  digitalWrite(exd2,LOW);
  analogWrite(frp,0);
  digitalWrite(frd,LOW);
  analogWrite(flp,0);
  digitalWrite(fld,HIGH);
  analogWrite(brp,0);
  digitalWrite(brd,HIGH);
  analogWrite(blp,0);
  digitalWrite(bld,LOW);
  Serial.println("STOP MOTORS");
}

void forward(int f)
 {
   int pos1;
  int g;
   g=0;
  if(pos>100)
     g=map(pos,100,170,0,75);
  analogWrite(frp,f+g);
  digitalWrite(frd,LOW);
  analogWrite(flp,f);
  digitalWrite(fld,LOW);
  analogWrite(brp,f+g);
  digitalWrite(brd,HIGH);
  analogWrite(blp,f);
  digitalWrite(bld,LOW);
  Serial.println("FORWARD");
  c++;
 }

void backward(int b)
{
  //int pos2;
  int g1;
   g1=0;
  if(pos>100)
     g1=map(pos,100,170,0,40);
  analogWrite(frp,b);
  digitalWrite(frd,HIGH);
  analogWrite(flp,b-g1);
  digitalWrite(fld,HIGH);
  analogWrite(brp,b-g1);
  digitalWrite(brd,LOW);
  analogWrite(blp,b);
  digitalWrite(bld,HIGH);
  Serial.println("backward");
 c++;
}

void right(int r)
{
  int g2;
   g2=0;
  if(pos>100)
     g2=map(pos,100,170,0,30);
  analogWrite(frp,r+g2);
  digitalWrite(frd,HIGH);
  analogWrite(flp,r);
  digitalWrite(fld,LOW);
  analogWrite(brp,r+g2);
  digitalWrite(brd,HIGH);
  analogWrite(blp,r);
  digitalWrite(bld,HIGH);
  Serial.println("RIGHT");
  c++;
}

void left(int l)
{
  int g3;
  g3=0;
  if(pos>100)
     g3=map(pos,100,170,0,30);
  analogWrite(frp,l+g3);
  digitalWrite(frd,LOW);
  analogWrite(flp,l);
  digitalWrite(fld,HIGH);
  analogWrite(brp,l+g3);
  digitalWrite(brd,LOW);
  analogWrite(blp,l);
  digitalWrite(bld,LOW);
  Serial.println("LEFT");
  c++;
 }

void yawleft(int yl)
 {
  analogWrite(frp,yl);
  digitalWrite(frd,LOW);
  analogWrite(flp,yl);
  digitalWrite(fld,HIGH);
  analogWrite(brp,yl);
  digitalWrite(brd,HIGH);
  analogWrite(blp,yl);
  digitalWrite(bld,HIGH);
  Serial.println("YAWLEFT");
  c++;
 }

void yawright(int yr)
 {
  analogWrite(frp,yr);
  digitalWrite(frd,HIGH);
  analogWrite(flp,yr);
  digitalWrite(fld,LOW);
  analogWrite(brp,yr);
  digitalWrite(brd,LOW);
  analogWrite(blp,yr);
  digitalWrite(bld,LOW);
  Serial.println("YAWRIGHT");
  c++;
 }
void ultrasonic()
 {
  digitalWrite(trig,LOW);
  delay(3);
  digitalWrite(trig,HIGH);
  delay(5);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  dis=duration/29/2;
  Serial.println(dis);
  //dis=microseconds_to_cms(duration);
   
   if(dis<21)
      up();
   else if(dis>26)
    down();
   else
     stpup();
 }    
 
void setup()
{
 Serial.begin(57600);
 pinMode(trig,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(pwr1,OUTPUT);
 digitalWrite(pwr1,HIGH);
 pinMode(pwr2,OUTPUT);
 digitalWrite(pwr2,HIGH);
 myservo.attach(3);
 myservo.write(0);
 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(A8,A9,47,49, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
     
    pinMode(fld,OUTPUT);
    pinMode(flp,OUTPUT);
    pinMode(bld,OUTPUT);
    pinMode(blp,OUTPUT);
    pinMode(frd,OUTPUT);
    pinMode(frp,OUTPUT);
    pinMode(brd,OUTPUT);
    pinMode(brp,OUTPUT);
    ///////////
        //pinmode linear actuator
    pinMode(exd1,OUTPUT);
    pinMode(exd2,OUTPUT);
    pinMode(upd1,OUTPUT);
    pinMode(upd2,OUTPUT);
   
    //pinmode of ultrasonic
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    digitalWrite(3,LOW);
    stp();
    stpup();//////////
    pos=p;
  
}
///////////
void up()
 {
   digitalWrite(upd2,LOW);
  digitalWrite(upd1,HIGH);
  Serial.println("up for the actuator");
 }
void down()
{
  digitalWrite(upd1,LOW);
  digitalWrite(upd2,HIGH);
  Serial.println("down");
}
void high()
 {
   myservo.write(pos++);
   if(pos<0)
   {pos=0;}
   if(pos>179)
   {pos=179;}
  Serial.println("high");
  Serial.println(pos);
 }
void low()
{
  myservo.write(pos--);
  if(pos<0)
   {pos=0;}
   if(pos>180)
     {pos=180;}
  Serial.println("low");
Serial.println(pos);
}
void stpup()
 {
  digitalWrite(upd1,LOW);
  digitalWrite(upd2,LOW);
  Serial.println("stop up");
 }

//utlrasonic
 void expand()
 {
  digitalWrite(exd1,LOW);
  digitalWrite(exd2,HIGH);
  Serial.println("EXPAND");
 }

void contract()
 {
  digitalWrite(exd1,HIGH);
  digitalWrite(exd2,LOW);
  Serial.println("contract");
 }
 ////////////

void loop()
{
  //ultrasonic();
  c=0; 
  if(error == 1) 
  return; 
  
  
  //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
 //---rotate propeller   
    if(ps2x.Button(PSB_TRIANGLE))   
   { 
    Serial.println("TRIANGLE");
     high();
   }
   else if(ps2x.Button(PSB_CROSS))   
  { 
    Serial.println("cROSS");
     low();
   }
   else stpup();
   //--motion
      x1=ps2x.Analog(PSS_LX);
      y1=ps2x.Analog(PSS_LY);
      x2=ps2x.Analog(PSS_RX);
      y2=ps2x.Analog(PSS_RY);
      Serial.print("x1=");
      Serial.print(x1);
      Serial.print(" y1="); 
      Serial.print(y1);
      Serial.print(" x2=="); 
      Serial.print(x2);
      Serial.print(" y2=="); 
      Serial.print(y2);
 

 
 
 //GENERAL MOTION
   if(x2<105 && y2>0 && y2<255)  yawleft(vel);
  else if(x2>140 && y2>0 && y2<255)  yawright(vel); 
  else if(y1<105 && x1>0 && x1<255)  forward(vel);   
  else  if(x1<100 && y1>0 && y1<255)  left(vel);
  else  if(x1>140 && y1>0 && y1<255)  right(vel);
  else if(y1>140 && x1>0 && x1<255)  backward(vel);
  else stp();
 //--CHANGE SPEED   
  if(c=0)
  {
    if(ps2x.NewButtonState(PSB_PAD_UP)) 
    { 
      Serial.println("uuuuuuup"); 
      vel=vel+5;
    }
     else if(ps2x.Button(PSB_PAD_DOWN)) 
    {
     Serial.println("back");
     vel=vel-5;
    }
  }   
  //////////
   //Actuator Motion
 
  if(ps2x.Button(PSB_CIRCLE))   
  { 
    Serial.println("circle");
     up();
   delay(10);}
    
 else if(ps2x.Button(PSB_SQUARE)) 
   {
     Serial.println("square");
     down();
     delay(10);
   }
   delay(50);
 }
 
 
 
      
  /* */
   
      //Analog stick values
     /*else if(ps2x.Button(PSB_PAD_RIGHT)) 
{
  
Serial.println("right");
}
  else if(ps2x.Button(PSB_PAD_LEFT)) 
{

Serial.println("left");
}
  */
  
/*else       
    {
      if(rxco<105){  yawleft(vel);  Serial.print("    rxco=");  Serial.print(rxco); }
      else if(rxco>145){  yawright(vel); Serial.print("    rxco=");  Serial.print(rxco); }
      else if(yco < 105 && xco>0 && xco<255) { forward(vel); Serial.print("    yco="); Serial.print(yco);}
      else if(yco > 145 && xco>0 && xco<255){     backward(vel);Serial.print("    yco="); Serial.print(yco);}     
      else if(xco < 105 && yco>0 && yco<255)  { left(vel); Serial.print("    xco="); Serial.print(xco);}
      else if(xco > 145 && yco>0 && yco<255)  {right(vel);Serial.print("    xco="); Serial.print(xco);}
      else stp(); 
    }    
*/
