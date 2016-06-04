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
  if ((dis > 25) && (dis > 0))
    down();
  else if ((dis < 20) && (dis > 0))
    up();
  else if (dis < 0)
    stpup();
  else stpup();
}

void ultrasonic1()
{
  digitalWrite(trig1, LOW);
  delayMicroseconds(10);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH, 32760);
  dis1 = duration1 / 58;
  Serial.print("Dis1=");
  Serial.print(dis1);
}

void ultrasonic2()
{
  digitalWrite(trig2, LOW);
  delayMicroseconds(10);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH, 32760);
  dis2 = duration2 / 58;
  Serial.print("\tDis=");
  Serial.print(dis2);
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
      //if(edf>100) g=map(edf,100,180,0,35);
      //else g=0; 
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

void motion_dir(boolean d1, boolean d2, boolean d3, boolean d4)
{
  digitalWrite(fld, d1);
  digitalWrite(frd, d2);
  digitalWrite(bld, d3);
  digitalWrite(brd, d4);
}

///************************************************///
///ALL PS4 COMMANDS BEING EXECUTED IN THIS FUNCTION///
///************************************************///
void condition()
{
    Usb.Task();
    if (PS4.connected())
    {
      
      Serial.println("\t\t\tCONNECTED!!!");
      
      //*********************//
      //STORING ANALOG VALUES//
      //*********************//
      xco = PS4.getAnalogHat(LeftHatX);
      yco = PS4.getAnalogHat(LeftHatY);
      rxco = PS4.getAnalogHat(RightHatX);

      //************//
      //MODE CHANGE //
      //************//
      mode_switch();

      //***************************************//
      //SPEED INCREASING IN UP AND DOWN BUTTONS//
      //***************************************//
      if (PS4.getButtonPress(UP))
      {
          if (vel < 250) vel = vel + 5;
          Serial.print("\tVel=");
          Serial.print(vel);
          delay(100);
      }
      if (PS4.getButtonPress(DOWN)) 
      {
          if (vel > 5) vel = vel - 5;
          Serial.print("\tVel=");
          Serial.print(vel);
          delay(100);
      }  
  }
  else if (!PS4.connected())
    {
        Serial.println("\t\t\tNOT CONNECTED!!!");
        stp();
        stpup();
        e1.write(0);
        e2.write(0);
        e0.write(0);
        PS4.setLedOff();
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

