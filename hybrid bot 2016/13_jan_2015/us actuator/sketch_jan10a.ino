

int trig=5;
int echo=17;
int duration;
int dis;
int pwr=14;
//linear actuator
int exd1=25;
int exd2=33;
int upd1=37;
int upd2=45;

void up()
 {
  pinMode(pwr,OUTPUT);
  digitalWrite(pwr,HIGH); 
  digitalWrite(upd2,LOW);
  digitalWrite(upd1,HIGH);
  Serial.println("up for the actuator");
 }
void down()
{
  digitalWrite(upd1,LOW);
  digitalWrite(upd2,HIGH);
  Serial.println("down");
}
void stopact()
{
  digitalWrite(upd1,LOW);
  digitalWrite(upd2,LOW);
  Serial.println("stp");
} 
void setup() 
{
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(pwr,OUTPUT);
 digitalWrite(pwr,HIGH);
 Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() 
{
 void ultrasonic()
 {
  digitalWrite(trig,LOW);
  delay(3);
  digitalWrite(trig,HIGH);
  delay(5);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  dis=duration/29/2;
  Serial.println(dis);
  //dis=microseconds_to_cms(duration);
   if(dis>15)
    down();
   else if(dis<12)
      up();
   else
     stopact();
 }    
   delay(50);  
    // put your main code here, to run repeatedly:

}
