
int fld=12;
int flp=13;
int bld=8;
int blp=9;

int frd=10;
int frp=11;
int brd=6;
int brp=7;

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
  Serial.println("STOP MOTORS");
}

void forward(int f)
 {
  
  analogWrite(frp,f);
  digitalWrite(frd,LOW);
  analogWrite(flp,f);
  digitalWrite(fld,LOW);
  analogWrite(brp,f);
  digitalWrite(brd,HIGH);
  analogWrite(blp,f);
  digitalWrite(bld,LOW);
  Serial.println("FORWARD");
 }

void backward(int b)
{
  
  analogWrite(frp,b);
  digitalWrite(frd,HIGH);
  analogWrite(flp,b);
  digitalWrite(fld,HIGH);
  analogWrite(brp,b);
  digitalWrite(brd,LOW);
  analogWrite(blp,b);
  digitalWrite(bld,HIGH);
  Serial.println("backward");
}

void right(int r)
{
  
  analogWrite(frp,r);
  digitalWrite(frd,HIGH);
  analogWrite(flp,r);
  digitalWrite(fld,LOW);
  analogWrite(brp,r);
  digitalWrite(brd,HIGH);
  analogWrite(blp,r);
  digitalWrite(bld,HIGH);
  Serial.println("RIGHT");
}

void left(int l)
 {
  analogWrite(frp,l);
  digitalWrite(frd,LOW);
  analogWrite(flp,l);
  digitalWrite(fld,HIGH);
  analogWrite(brp,l);
  digitalWrite(brd,LOW);
  analogWrite(blp,l);
  digitalWrite(bld,LOW);
  Serial.println("LEFT");
 }

void yawleft(int yr)
 {
  analogWrite(frp,yr);
  digitalWrite(frd,LOW);
  analogWrite(flp,yr);
  digitalWrite(fld,HIGH);
  analogWrite(brp,yr);
  digitalWrite(brd,HIGH);
  analogWrite(blp,yr);
  digitalWrite(bld,HIGH);
  Serial.println("YAWLEFT");
 }

void yawright(int yl)
 {
  analogWrite(frp,yl);
  digitalWrite(frd,HIGH);
  analogWrite(flp,yl);
  digitalWrite(fld,LOW);
  analogWrite(brp,yl);
  digitalWrite(brd,LOW);
  analogWrite(blp,yl);
  digitalWrite(bld,LOW);
  Serial.println("YAWRIGHT");
 }
void setup()
{
      //pinmode for motors
    pinMode(fld,OUTPUT);
    pinMode(flp,OUTPUT);
    pinMode(bld,OUTPUT);
    pinMode(blp,OUTPUT);
    pinMode(frd,OUTPUT);
    pinMode(frp,OUTPUT);
    pinMode(brd,OUTPUT);
    pinMode(brp,OUTPUT);
Serial.begin(57600);
}
void loop()
{
  //forward(100);
  //delay(3000);
  //backward(100);
  //left(100);
  //right(100);
  //yawright(100);
  //yawleft(100);
  stp();
}
