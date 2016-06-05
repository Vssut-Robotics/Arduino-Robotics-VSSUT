//#include <Servo.h>
#include <MeetAndroid.h>

int lp=5;
int ln=3;
int rp=9;
int rn=6;
float data[3] = {0};

int t=0;

int pro ;//[1]= {0};


// MeetAndroid meetAndroid();
// you can define your own error function to catch messages
// where not fuction has been attached for
MeetAndroid meetAndroid;

void error(uint8_t flag, uint8_t values){
  Serial.print("ERROR: ");
  Serial.print(flag);
}

 
  void setup() {
  Serial.begin(9600); //begin serial link @ 9600bps
  // register callback functions, which will be called when an associated event occurs.
  // - the first parameter is the name of your function (see below)
  // - match the second parameter ('A', 'B', 'a', etc...) with the flag on your Android application
   meetAndroid.registerFunction(intValues, 'B');
  meetAndroid.registerFunction(floatValues, 'A');  
    
  //myservo.attach(11); //Attach the servo to pin eleven
  pinMode(rp,OUTPUT);
  pinMode(rn,OUTPUT);
  pinMode(lp,OUTPUT);
  pinMode(ln,OUTPUT);
  /*analogWrite(3,0);
  analogWrite(5,0);
  analogWrite(6,0);
  analogWrite(9,0);*/
  analogWrite(rp,0);
  analogWrite(rn,0);
  analogWrite(lp,0);
  analogWrite(ln,0);
  

}

void loop()
{
 // Serial.println("entered LOOP()");delay(1000);
  meetAndroid.receive(); // you need to keep this in your loop() to receive events 
 // Serial.println("Exiting  loop()"); delay(1000);
}
void intValues(byte flag, byte numOfValues)
{//Serial.println("entering prox"); delay(1000);
 
  pro=meetAndroid.getInt();
  Serial.println(pro);
  if(pro==0) t=1; else t=0 ;
  //Serial.println("exiting prox");
  //delay(1000);
}
void floatValues(byte flag, byte numOfValues)
{
//  Serial.println("Entering acc:"); delay(1000);
  // create an array where all event values should be stored
  // the number of values attached to this event is given by
  // a parameter(numOfValues)
  
  // call the library function to fill the array with values (floats)
  
  meetAndroid.getFloatValues(data);
  
  Serial.print(data[0]);
    Serial.print('\t');
      Serial.print(data[1]);
        Serial.print('\t');
          Serial.println(data[2]);
          
        stop();//  digitalWrite(5,LOW); digitalWrite(9,LOW);
          //analogWrite(5,0); analogWrite(9,0);
          if(t==1){
          if(data[0]<-3) {digitalWrite(lp,100); digitalWrite(rn,100);}//turns right
          //analogWrite(5,200);
         // else digitalWrite(13,0);
         
          if(data[0]>3) {digitalWrite(rp,100); digitalWrite(ln,100);}//turns left
          //analogWrite(9,200);
         // else digitalWrite(12,LOW);
          
          if(data[1]>3){digitalWrite(rn,HIGH); digitalWrite(ln,HIGH);}// backward  // {analogWrite(5,200); analogWrite(9,200);}
           if(data[1]<-3){digitalWrite(rp,HIGH); digitalWrite(lp,HIGH);} // forward
        
          }          
        //  Serial.println("Exiting acc");
          //delay(1000);
          //else {digitalWrite(13,LOW); digitalWrite(12,LOW);}
   
            
}
void stop()
{
    digitalWrite(rp,0); digitalWrite(rn,0);
      digitalWrite(lp,0); digitalWrite(ln,0);
}

