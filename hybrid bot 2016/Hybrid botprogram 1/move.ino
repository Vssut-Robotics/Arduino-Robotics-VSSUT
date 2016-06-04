//move

void stp()
{
  analogWrite(frp,0);
  digitalWrite(frd,LOW);
  analogWrite(flp,0);
  digitalWrite(fld,HIGH);
  analogWrite(brp,0);
  digitalWrite(brd,HIGH);
  analogWrite(blp,0);
  digitalWrite(bld,LOW);
  Serial.print("STOP");
}

void forward()
 {
  
  analogWrite(frp,sp);
  digitalWrite(frd,HIGH);
  analogWrite(flp,sp);
  digitalWrite(fld,HIGH);
  analogWrite(brp,sp);
  digitalWrite(brd,HIGH);
  analogWrite(blp,sp);
  digitalWrite(bld,HIGH);
  Serial.print("FORWARD");
 }

void backward()
{
  
  analogWrite(frp,sp);
  digitalWrite(frd,LOW);
  analogWrite(flp,sp);
  digitalWrite(fld,LOW);
  analogWrite(brp,sp);
  digitalWrite(brd,LOW);
  analogWrite(blp,sp);
  digitalWrite(bld,LOW);
  Serial.print("backward");
}

void right()
{
  
  analogWrite(frp,sp);
  digitalWrite(frd,LOW);
  analogWrite(flp,sp);
  digitalWrite(fld,HIGH);
  analogWrite(brp,sp);
  digitalWrite(brd,HIGH);
  analogWrite(blp,sp);
  digitalWrite(bld,LOW);
  Serial.print("RIGHT");
}

void left()
 {
  analogWrite(frp,sp);
  digitalWrite(frd,HIGH);
  analogWrite(flp,sp);
  digitalWrite(fld,LOW);
  analogWrite(brp,sp);
  digitalWrite(brd,LOW);
  analogWrite(blp,sp);
  digitalWrite(bld,HIGH);
  Serial.print("LEFT");
 }

void yawright()
 {
  analogWrite(frp,sp);
  digitalWrite(frd,LOW);
  analogWrite(flp,sp);
  digitalWrite(fld,HIGH);
  analogWrite(brp,sp);
  digitalWrite(brd,LOW);
  analogWrite(blp,sp);
  digitalWrite(bld,HIGH);
  Serial.print("YAWRIGHT");
 }

void yawleft()
 {
  analogWrite(frp,sp);
  digitalWrite(frd,HIGH);
  analogWrite(flp,sp);
  digitalWrite(fld,LOW);
  analogWrite(brp,sp);
  digitalWrite(brd,HIGH);
  analogWrite(blp,sp);
  digitalWrite(bld,LOW);
  Serial.print("YAWLEFT");
 }

void expand()
 {
  digitalWrite(exd1,HIGH);
  digitalWrite(exd2,LOW);
 }

void contract()
 {
  digitalWrite(exd1,LOW);
  digitalWrite(exd2,HIGH);
 }
void stpexp()
{
  digitalWrite(exd1,LOW);
  digitalWrite(exd2,LOW);
}

void stpup()
 {
  digitalWrite(exd1,LOW);
  digitalWrite(exd2,LOW);
 }
void up()
 {
   digitalWrite(upd2,LOW);
  digitalWrite(upd1,HIGH);
 }
void down()
{
  digitalWrite(upd1,LOW);
  digitalWrite(upd2,HIGH);
}

