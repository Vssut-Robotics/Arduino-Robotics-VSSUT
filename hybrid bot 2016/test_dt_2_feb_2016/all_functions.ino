///************************///
///LINEAR ACTUATOR FUNCTION///
///************************///

void down()
{
  digitalWrite(upd1, LOW);
  digitalWrite(upd2, HIGH);
  Serial.println("down for the actuator");
}
void up()
{
  digitalWrite(upd2, LOW);
  digitalWrite(upd1, HIGH);
  Serial.println("up for the actuator");
}
void stpup()
{
  digitalWrite(upd1, LOW);
  digitalWrite(upd2, LOW);
  Serial.println("stop up for the actuator");
}

///*******************///
///ULTRASONIC FUNCTION///
///*******************///
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
}

///*****************************///
///MOTOR PROGRAMS OR FUNCTIONS  ///
///*****************************///

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
void motion_pwm(int val)
{
  if (i != val)
  {
    for (i = 0; i < val; i++)
    {
      if(edf>100) g=map(edf,100,180,0,35);
      else g=0; 
      analogWrite(blp, i+g);
      analogWrite(brp, i);
      analogWrite(flp, i);
      analogWrite(frp, i+g);
      delay(1);
      Serial.print("Speed=");
      Serial.println(i+g);
    }
  }
  Serial.print("Speed=");
  Serial.println(i);
}

void motion_dir(boolean d1, boolean d2, boolean d3, boolean d4)
{
  digitalWrite(fld, d1);
  digitalWrite(frd, d2);
  digitalWrite(bld, d3);
  digitalWrite(brd, d4);
}

///************************************************///
///ALL PS3 COMMANDS BEING EXECUTED IN THIS FUNCTION///
///************************************************///
void condition()
{
    Usb.Task();
    if (PS3.PS3Connected || PS3.PS3NavigationConnected)
    {
      
      Serial.println("\t\t\tCONNECTED!!!");
      //********//
      //LED'S ON//
      //********//
      PS3.setLedOff();
      PS3.setLedOn(LED1);
      PS3.setLedOn(LED2);

      //*********************//
      //STORING ANALOG VALUES//
      //*********************//
      xco = PS3.getAnalogHat(LeftHatX);
      yco = PS3.getAnalogHat(LeftHatY);
      rxco = PS3.getAnalogHat(RightHatX);

      //************//
      //MODE CHANGE //
      //************//
      mode_switch();

      //***************************************//
      //SPEED INCREASING IN UP AND DOWN BUTTONS//
      //***************************************//
      if (PS3.getButtonPress(UP))
      {
          if (vel < 250) vel = vel + 5;
          Serial.print("\tVel=");
          Serial.print(vel);
          delay(100);
      }
      if (PS3.getButtonPress(DOWN)) 
      {
          if (vel > 5) vel = vel - 5;
          Serial.print("\tVel=");
          Serial.print(vel);
          delay(100);
      }  
  }
  else if (!PS3.PS3Connected)
    {
        Serial.println("\t\t\tNOT CONNECTED!!!");
        stp();
        stpup();
        e1.write(0);
        e2.write(0);
        e0.write(0);
        PS3.setLedOff();
    }
  else
    {
        Serial.println("\t\t\tNO CONDITION!!!");
        stp();
        stpup();
        e1.write(0);
        e2.write(0);
        e0.write(0);
    }
}

