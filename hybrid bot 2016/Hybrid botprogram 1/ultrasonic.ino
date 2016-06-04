//utlrasonic

void ultrasonic()
 {
  digitalWrite(trig,LOW);
  delay(3);
  digitalWrite(trig,HIGH);
  delay(5);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  dis=duration/29/2;
  //dis=microseconds_to_cms(duration);
   if(dis>15)
    down();
   else if(dis<12)
      up();
   else
      stpup();
 }

