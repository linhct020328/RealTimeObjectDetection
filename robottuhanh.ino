#include<Servo.h>

#define IN1_L298_PIN 4
#define IN2_L298_PIN 5
#define IN3_L298_PIN 8
#define IN4_L298_PIN 9
#define ENA_PIN 11
#define ENB_PIN 6                                                           
#define echo_PIN 19
#define trig_PIN 18
#define servo_PIN 7

Servo servosg;

void motor_stop()
{
  digitalWrite(IN1_L298_PIN,LOW);
  digitalWrite(IN2_L298_PIN,LOW);
  digitalWrite(IN3_L298_PIN,LOW);
  digitalWrite(IN4_L298_PIN,LOW);
  
}
void motor_up(int x,int y)
{
  analogWrite(ENA_PIN,x);
  analogWrite(ENB_PIN,y);
  digitalWrite(IN1_L298_PIN,HIGH);
  digitalWrite(IN2_L298_PIN,LOW);
  digitalWrite(IN3_L298_PIN,HIGH);
  digitalWrite(IN4_L298_PIN,LOW);
  
}
void motor_back(int x,int y)
{
  analogWrite(ENA_PIN,x);
  analogWrite(ENB_PIN,y);
   digitalWrite(IN1_L298_PIN,LOW);
  digitalWrite(IN2_L298_PIN,HIGH);
  digitalWrite(IN3_L298_PIN,LOW);
  digitalWrite(IN4_L298_PIN,HIGH);
  
}
void motor_left(int x,int y)
{
  analogWrite(ENA_PIN,x);
  analogWrite(ENB_PIN,y);
   digitalWrite(IN1_L298_PIN,HIGH);
  digitalWrite(IN2_L298_PIN,LOW);
  digitalWrite(IN3_L298_PIN,LOW);
  digitalWrite(IN4_L298_PIN,LOW);
  
}
void motor_right(int x,int y)
{
   analogWrite(ENA_PIN,x);
  analogWrite(ENB_PIN,y);
   digitalWrite(IN1_L298_PIN,LOW);
  digitalWrite(IN2_L298_PIN,LOW);
  digitalWrite(IN3_L298_PIN,HIGH);
  digitalWrite(IN4_L298_PIN,LOW);
 
}
int getDistance()
{
  int duration, distanceCm;
  digitalWrite(trig_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_PIN, LOW);
  duration = pulseIn(echo_PIN, HIGH);
  distanceCm = (int)duration / 29.1 / 2;
  return distanceCm;
}


void setup()
{
  Serial.begin(9600);
  servosg.attach(servo_PIN);
  servosg.write(90);
  pinMode(trig_PIN,OUTPUT);
  pinMode(echo_PIN,INPUT);
  pinMode(IN1_L298_PIN,OUTPUT);
  pinMode(IN2_L298_PIN,OUTPUT);
  pinMode(IN3_L298_PIN,OUTPUT);
  pinMode(IN4_L298_PIN,OUTPUT);
  pinMode(ENA_PIN,OUTPUT);
  pinMode(ENB_PIN,OUTPUT);
  
  
}
void tuchay()
{

	int distance;
  int distance0,distance180;
  distance=getDistance();
  
  if(distance <=20)
  {
    motor_stop();
    delay(100);
    motor_back(120,120);
    delay(300);
    motor_stop();
    delay(200);
    servosg.write(0);
    distance0=getDistance();
    delay(100);
    servosg.write(35);
    delay(100);
    servosg.write(70);
    delay(100);
    servosg.write(105);
    delay(100);
    servosg.write(145);
    delay(100);
    servosg.write(180);
    distance180=getDistance();
    delay(100);
    servosg.write(90);
   
    if((distance0 < 20)&& (distance180 < 20))
    {
      motor_back(100,100);
      delay(300);
      motor_stop();
      delay(300);
    }
    else
    if( distance0 >distance180)
    {
      motor_right(100,100);
      delay(750);
    }
    else
    if( distance0 <=distance180)
    {
      motor_left(100,100);
      delay(750);
    }
    
    
    
  }
  else
  {
   
    motor_up(100,100);
  }
}
char bluetooth;
void loop()
{
     if(Serial.available() > 0)
      {
        bluetooth=  Serial.read();
        Serial.println(bluetooth);
      }
      switch(bluetooth)
      {
        case  '2':motor_up(150,150); break;
        case  '4':motor_left(150,150);break;
        case  '5':motor_right(150,150);break;
        case  '3':motor_back(150,150);break;
        case  '1':motor_stop();break;
        case  '6':
        while(1)
        {
          if(Serial.available() > 0)
          {
           bluetooth=  Serial.read();  
          }
          if(bluetooth=='2') break;
          tuchay();
         
          
        } break;
      }
      
      
  
  
  
}
