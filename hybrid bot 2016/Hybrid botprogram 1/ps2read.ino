///ps2_read
void ps2_read()
 {
    if(error == 1) //skip loop if no controller found
    return; 
  
   
  else
    { //DualShock Controller
    

    if(ps2x.Button(PSB_PAD_UP)) 
    {      //will be TRUE as long as button is pressed
      //Serial.print("Up held this hard: ");
      //Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      forward();
    }
    if(ps2x.Button(PSB_PAD_RIGHT))
    {
      //Serial.print("Right held this hard: ");
      //Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      right();
    }
    if(ps2x.Button(PSB_PAD_LEFT))
    {
      //Serial.print("LEFT held this hard: ");
      //Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      left();
    }
    if(ps2x.Button(PSB_PAD_DOWN))
    {
      //Serial.print("DOWN held this hard: ");
      //Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      down();
    }   

    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
      /*if(ps2x.Button(PSB_L2))
        {
          //Serial.println("L2 pressed");
          
        }
        if(ps2x.Button(PSB_TRIANGLE))
        {
          //Serial.println("Triangle pressed");
           
        }
        if(ps2x.ButtonReleased(PSB_SQUARE))              //will be TRUE if button was JUST released
      Serial.println("Square just released");     

           
    */
    if(ps2x.Button(PSB_R2))
        {
          //Serial.println("R2 pressed");
          val=val-1;
        }
    if(ps2x.Button(PSB_R1))
        {
          //Serial.println("R2 pressed");
          val=val+1;
        }
    if(ps2x.Button(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
        {
          //Serial.println("Circle just pressed");
          expand();
        }
    else if(ps2x.Button(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
      {
        //Serial.println("X just changed");
        contract();
      }
      else 
        stpexp();
      //Serial.print("Stick Values:");
      ly=ps2x.Analog(PSS_LY);
      Serial.print(ly, DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      lx=ps2x.Analog(PSS_LX);
      Serial.print(lx, DEC); 
      Serial.print(",");
      ry=ps2x.Analog(PSS_RY);
      Serial.print(ry, DEC); 
      Serial.print(",");
      rx=ps2x.Analog(PSS_RX);
      Serial.println(rx, DEC);      
  }
    
 }

