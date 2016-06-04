void mode_switch()
{
  Usb.Task();

  
    if (but)
    {
      Serial.print("change");
      if (PS3.getButtonClick(SQUARE))
        but = !but;
      if (PS3.getButtonPress(TRIANGLE))
        up();
      else if (PS3.getButtonPress(CROSS))
        down();
      else stpup();
    }
    else
    {
      Serial.print("same");
      if (PS3.getButtonClick(SQUARE))
        but = !but;
      if (PS3.getButtonPress(TRIANGLE))
        up();
      else if (PS3.getButtonPress(CROSS))
        down();

      else ultrasonic();
    }
  
  if (mode)
  {
      Serial.print("\t\t\tEDF MODE 1!!!: Default mode");
      if (PS3.getButtonClick(SELECT))
      {
        mode = !mode;
        e1.write(0);
        e2.write(0);
        e0.write(0);
      }
      ///*********************///
      ///MOTOR CONDITION CHECK///
      ///*********************///
      if (rxco > 165)
      {
          dir1 = LOW;
          dir2 = LOW;
          dir3 = LOW;
          dir4 = LOW;
          motion_dir(dir1, dir2, dir3, dir4);
          motion_pwm(vel);
          Serial.print("YAWRIGHT");
      }
      else if (rxco < 92)
      {
          dir1 = HIGH;
          dir2 = HIGH;
          dir3 = HIGH;
          dir4 = HIGH;
          motion_dir(dir1, dir2, dir3, dir4);
          motion_pwm(vel);
          Serial.print("YAWLEFT");
      }
      else if (yco > 155 && xco > 32 && xco < 200)
      {
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
      else  stp();
    
    if (PS3.getButtonPress(R1))
    {
      edf += 2;
      if (edf > 178) edf = 178;
      delay(30);
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf);
      e0.write(edf);
    }
    else if (PS3.getButtonPress(L1))
    {
      if (edf > 0)  edf -= 2;
      else if (edf < 0) edf = 0;
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf);
      delay(15);
      e0.write(edf);
    }

    Serial.print("\t\tEdf Speed=");
    Serial.println(edf);
  }
  else
  {
    Serial.print("\t\t\tEDF MODE 2!!!: Changed mode");
    if (PS3.getButtonClick(SELECT))
    {
      mode = !mode;
      e0.write(0);
      e1.write(0);
      e2.write(0); 
    } 
    if (PS3.getAnalogButton(L2))
    {
      oldL2Value = PS3.getAnalogButton(L2);
      if (oldL2Value <= 250)    edf1 = map(oldL2Value, 0, 250, 0, 175);
      e1.write(edf1);
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf1);
    }
    if (PS3.getAnalogButton(R2))
    {
      oldR2Value = PS3.getAnalogButton(R2);
      if (oldR2Value <= 250)  edf2 = map(oldR2Value, 0, 250, 0, 175);
      e2.write(edf2);
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf2);
    }
      ///*********************///
      ///MOTOR CONDITION CHECK///
      ///*********************///
      if (rxco > 165)
      {
          dir1 = LOW;
          dir2 = LOW;
          dir3 = LOW;
          dir4 = LOW;
          motion_dir(dir1, dir2, dir3, dir4);
          motion_pwm(vel);
          Serial.print("YAWRIGHT");
      }
      else if (rxco < 92)
      {
          dir1 = HIGH;
          dir2 = HIGH;
          dir3 = HIGH;
          dir4 = HIGH;
          motion_dir(dir1, dir2, dir3, dir4);
          motion_pwm(vel);
          Serial.print("YAWLEFT");
      }
      else if (yco > 155 && xco > 32 && xco < 200)
      {
          dir1 = HIGH;
          dir2 = HIGH;
          dir3 = LOW;
          dir4 = LOW;
          motion_dir(dir1, dir2, dir3, dir4);
          motion_pwm(vel);
          Serial.print("BACKWARD");
      }
      else if (xco < 117 && yco > 32 && yco < 200)
      {
          dir1 = LOW;
          dir2 = HIGH;
          dir3 = LOW;
          dir4 = HIGH;
          motion_dir(dir1, dir2, dir3, dir4);
          motion_pwm(vel);
          Serial.print("LEFT");
      }
      else if (xco > 157 && yco > 32 && yco < 200)
      { 
          dir1 = HIGH;
          dir2 = LOW;
          dir3 = HIGH;
          dir4 = LOW;
          motion_dir(dir1, dir2, dir3, dir4);
          motion_pwm(vel);
          Serial.print("RIGHT");
      }
     else if (yco < 97 && xco > 52 && xco < 200)
      {
          dir1 = LOW;
          dir2 = LOW;
          dir3 = HIGH;
          dir4 = HIGH; 
          motion_dir(dir1, dir2, dir3, dir4);
          motion_pwm(vel);
          Serial.print("FORWARD");
    }
    else   stp();
  }
}
