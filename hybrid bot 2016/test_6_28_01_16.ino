#include<Servo.h>
#include <PS3USB.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
PS3USB PS3(&Usb);
Servo myservo;

int r2, edf = 0;
const int p = 0;
bool but=false;
//MAPPING VARIABLES
int yl = 0, yr = 0, fr = 0, bk = 0, l = 0, r = 0, vel = 0;
static int i = 0;

//PS3 VARIABLES
int xco, yco, rxco, ryco;
int frco, flco;

//MOTOR PINS
int fld = 12;
int flp = 13;
int bld = 8;
int blp = 9;

int frd = 23;
int frp = 11;
int brd = 6;
int brp = 7;

//Global Dir pin
boolean dir1 = HIGH, dir2 = HIGH, dir3 = HIGH, dir4 = HIGH;

//linear actuator
int upd1 = 37;
int upd2 = 45;

//ultrasonic;
int trig = 5;
int echo = 17;
int duration;
int dis;

static int oldR2Value = 0;
bool mode = false;

void ultrasonic()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH, 32760);
  dis = duration / 58;
  Serial.print("\tDis=");
  Serial.println(dis);
  if ((dis > 30) && (dis > 0))
    down();
  else if ((dis < 25) && (dis > 0))
    up();
  else if (dis < 0)
    stpup();
  else stpup();

  //delay(10);

}

void down()
{
  digitalWrite(upd1, LOW);
  digitalWrite(upd2, HIGH);
  Serial.println("down");
}
void up()
{
  digitalWrite(upd2, LOW);
  digitalWrite(upd1, HIGH);
  Serial.println("up for the actuator");
}

//SETUP
void setup()
{
  digitalWrite(A0, HIGH);
  //MOTOR PIN MODE
  pinMode(fld, OUTPUT);
  pinMode(flp, OUTPUT);
  pinMode(bld, OUTPUT);
  pinMode(blp, OUTPUT);
  pinMode(frd, OUTPUT);
  pinMode(frp, OUTPUT);
  pinMode(brd, OUTPUT);
  pinMode(brp, OUTPUT);

  //pinmode linear a0ctuator
  pinMode(upd1, OUTPUT);
  pinMode(upd2, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  myservo.attach(3);
  myservo.write(0);
  //  pos=p;
  vel = 50;
  Serial.begin(115200);
  while (!Serial);
  if (Usb.Init() == -1)
  {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}

//MAPPING FUN()
/*void map_ps3()
  {
  fr = map(yco,115,0,0,100);
  bk = map(yco,135,255,0,100);
  l  = map(xco,115,0,0,100);
  r  = map(xco,135,255,0,100);
  yl = map(rxco,119,0,0,100);
  yr = map(rxco,135,255,0,100);
  //edf=map(ch[3],1000,2000,0,180);
  }*/

void stpup()
{
  digitalWrite(upd1, LOW);
  digitalWrite(upd2, LOW);
  Serial.println("stop up");
}
void stp()
{
  i = 0;
  analogWrite(blp, 0);
  analogWrite(brp, 0);
  analogWrite(flp, 0);
  analogWrite(frp, 0);
  digitalWrite(fld, LOW);
  digitalWrite(frd, LOW);
  digitalWrite(bld, LOW);
  digitalWrite(brd, LOW);
  Serial.print("   STOP!!!");
}
//GLOBAL MOTION FUN for pwm signals()
void motion_pwm(int val)
{
  if (i != val)
  {
    for (i = 0; i < val; i++)
    {
      analogWrite(blp, i);
      analogWrite(brp, i);
      analogWrite(flp, i);
      analogWrite(frp, i);
      delay(1);
      Serial.print("Speed=");
      Serial.println(i);
    }
  }
  Serial.print("Speed=");
  Serial.println(i);
}

//GLOBAL MOTION FUN for directions
void motion_dir(boolean d1, boolean d2, boolean d3, boolean d4)
{
  digitalWrite(fld, d1);
  digitalWrite(frd, d2);
  digitalWrite(bld, d3);
  digitalWrite(brd, d4);
}

//CONDITION TEST
void condition()
{
  //ultrasonic();
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected)
  {

    xco = PS3.getAnalogHat(LeftHatX);
    yco = PS3.getAnalogHat(LeftHatY);
    rxco = PS3.getAnalogHat(RightHatX);


    if (oldR2Value < PS3.getAnalogButton(R2))
    {
      oldR2Value = PS3.getAnalogButton(R2);
      edf = map(oldR2Value, 0, 255, 0, 178);
      myservo.write(edf);
      Serial.print("\tEdf Speed=");
      Serial.println(edf);
    }
    /*else if(PS3.getButtonPress(R1))
      {
         for(int i=edf;i>0;i--)
         {
            myservo.write(i);
            Serial.print("\t\tEdf Speed=");
      Serial.println(i);
      delay(25);
         }
         edf=0;
         oldR2Value=0;
      }*/

    else if (PS3.getButtonPress(R1))
    {
      if (edf)  edf -= 2;
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf);
      delay(5);
      myservo.write(edf);

      //edf=0;
      oldR2Value = 0;
    }


    Serial.print("\tEdf Speed=");
    Serial.println(edf);
    if (PS3.getButtonPress(UP))
    {
      if (vel < 250) vel = vel + 5;
      Serial.print("\tVel=");
      Serial.print(vel);
      delay(100);
    }
    if (PS3.getButtonPress(DOWN)) {
      if (vel > 5) vel = vel - 5;
      Serial.print("\tVel=");
      Serial.print(vel);
      delay(100);
    }


      
 if(but)
     { 
       Serial.print("change");
       if(PS3.getButtonClick(L1))
         but=!but;
        if (PS3.getButtonPress(TRIANGLE)) 
        up();
      else if (PS3.getButtonPress(CROSS))
        down();
      else stpup(); 
      } 
  else 
    {
     Serial.print("same");
     if(PS3.getButtonClick(L1))
       but=!but;
     if (PS3.getButtonPress(TRIANGLE))
        up();
      else if (PS3.getButtonPress(CROSS))
        down();
  
     else ultrasonic();  
     }
    if (rxco > 160)
    {
      //ultrasonic();
      dir1 = LOW;
      dir2 = LOW;
      dir3 = LOW;
      dir4 = LOW;
      motion_dir(dir1, dir2, dir3, dir4);
      motion_pwm(vel);
      Serial.print("YAWRIGHT");

    }
    else if (rxco < 97)
    {
      //ultrasonic();
      dir1 = HIGH;
      dir2 = HIGH;
      dir3 = HIGH;
      dir4 = HIGH;
      motion_dir(dir1, dir2, dir3, dir4);
      motion_pwm(vel);
      Serial.print("YAWLEFT");

    }
    else if (yco > 157 && xco > 32 && xco < 200)
    {
      //ultrasonic();
      dir1 = HIGH;
      dir2 = LOW;
      dir3 = HIGH;
      dir4 = LOW;
      motion_dir(dir1, dir2, dir3, dir4);
      motion_pwm(vel);
      Serial.print("BACKWARD");

    }

    else if (xco < 117 && yco > 32 && yco < 200)
    {
      //ultrasonic();
      
      dir1 = HIGH;
      dir2 = HIGH;
      dir3 = LOW;
      dir4 = LOW;
      motion_dir(dir1, dir2, dir3, dir4);
      motion_pwm(vel);
      Serial.print("LEFT");

    }
    else if (xco > 157 && yco > 32 && yco < 200)
    {
      //ultrasonic();
      dir1 = LOW;
      dir2 = LOW;
      dir3 = HIGH;
      dir4 = HIGH;
      motion_dir(dir1, dir2, dir3, dir4);
      motion_pwm(vel);
      Serial.print("RIGHT");

    }
    else if (yco < 97 && xco > 52 && xco < 200)
    {
      dir1 = LOW;
      dir2 = HIGH;
      dir3 = LOW;
      dir4 = HIGH;
      motion_dir(dir1, dir2, dir3, dir4);
      motion_pwm(vel);
      Serial.print("FORWARD");

    }
    else
    {

      stp();
    }
  }
  else
  {
    stp();
    stpup();
  }

}
void loop()
{
  condition();
}


