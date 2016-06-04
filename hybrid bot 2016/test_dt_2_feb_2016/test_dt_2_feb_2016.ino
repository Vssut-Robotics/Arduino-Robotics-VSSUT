#include<Servo.h>
#include <PS3USB.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
PS3USB PS3(&Usb);
Servo e0, e1, e2;    //THREE OBJECTS OF SERVO CLASS


  //MOTOR PINS
  int fld = 12;
  int flp = 13;
  int bld = 8;
  int blp = 9;

  int frd = 23;
  int frp = 11;
  int brd = 6;
  int brp = 7;

  //PINS FOR 3 EDFS
  int edf = 0, edf1 = 0, edf2 = 0,g=0;

  //MODE CHANGING VARIABLES
  bool but = false, mode = true;
  static int oldR2Value = 0, oldL2Value = 0;

  //MAPPING VARIABLES
  int vel = 0;
  static int i = 0;

  //PS3 VARIABLES
  int xco, yco, rxco, ryco;
  int frco, flco;


  //Global Direction pin
  boolean dir1 = HIGH, dir2 = HIGH, dir3 = HIGH, dir4 = HIGH;

  //linear actuator
  int upd1 = 25;
  int upd2 = 33;

  //ultrasonic;
  int trig = 5;
  int echo = 17;
  int duration;
  int dis;


void setup()              //SETUP ONLY USED FOR PINMODE AND COMMUNICATION
{
  pinMode(fld, OUTPUT);       //MOTOR PIN MODE
  pinMode(flp, OUTPUT);
  pinMode(bld, OUTPUT);
  pinMode(blp, OUTPUT);
  pinMode(frd, OUTPUT);
  pinMode(frp, OUTPUT);
  pinMode(brd, OUTPUT);
  pinMode(brp, OUTPUT);

  pinMode(upd1, OUTPUT);    //pinmode linear actuator
  pinMode(upd2, OUTPUT);

  pinMode(trig, OUTPUT);    //ULTRASONIC
  pinMode(echo, INPUT);

  e0.attach(3);
  e1.attach(2);
  e2.attach(45);
  e0.write(0);
  e1.write(0);
  e2.write(0);


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


void loop()
{
  condition();
}
