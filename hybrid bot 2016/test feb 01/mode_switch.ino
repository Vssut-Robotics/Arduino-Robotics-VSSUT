void edf_mode_switch()
{
  Usb.Task();
  if (mode)
  {
    Serial.print("\t\t\tEDF MODE 1!!!: Default mode");
    if (PS3.getButtonClick(SELECT))
    {
      mode = !mode;
      e1.write(0);
      e2.write(0);
      myservo.write(0);
    }

    if (PS3.getButtonPress(R1))
    {
      edf += 2;

      if (edf > 178) edf = 178;
      delay(30);
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf);
      myservo.write(edf);
    }
    else if (PS3.getButtonPress(L1))
    {
      if (edf > 0)  edf -= 2;
      else if (edf < 0) edf = 0;
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf);
      delay(15);
      myservo.write(edf);
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
      myservo.write(0);
      e1.write(0);
      e2.write(0);
    }
    if (PS3.getAnalogButton(L2))
    {
      oldL2Value = PS3.getAnalogButton(L2);
      if (oldL2Value <= 250)
      {
        edf1 = map(oldL2Value, 0, 250, 0, 175);
      }
      e1.write(edf1);
    }
     if (PS3.getButtonPress(L1))
    {
      if (edf1 > 0)  edf1 -= 10;
      else if (edf1 < 0) edf1 = 0;
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf1);
      delay(15);
      e1.write(edf1);
      if (edf2 > 0)  edf2 -= 10;
      else if (edf2 < 0) edf2 = 0;
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf2);
      delay(15);
      e2.write(edf2);
    }
    if (PS3.getAnalogButton(R2))
    {
      oldR2Value = PS3.getAnalogButton(R2);
      if (oldR2Value <= 250)
      {
        edf2 = map(oldR2Value, 0, 250, 0, 175);
      }
      e2.write(edf2);
    }
    
     /*if (PS3.getButtonPress(R1))
    {
      if (edf2 > 0)  edf2 -= 10;
      else if (edf2 < 0) edf2 = 0;
      Serial.print("\t\tEdf Speed=");
      Serial.println(edf2);
      delay(15);
      e2.write(edf2);
    }*/
    Serial.print("\t\tr2==");
    Serial.println(oldR2Value);
    Serial.print("\t\tEdf Speed=");
    Serial.println(edf2);
  }
}
