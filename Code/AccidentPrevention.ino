#include <Wire.h> // Comes with Arduino IDE
#include<Servo.h>
Servo servo1;
Servo servo2;
#define echopin1 6 // Echo Pin 1
#define trigpin1 7 // Trigger Pin 1

#define echopin2 8 // Echo Pin 2
#define trigpin2 9// Trigger Pin 2

#define echopin3 10 // Echo Pin 3
#define trigpin3 11 // Trigger Pin 3

#define echopin4 12 // Echo Pin 4
#define trigpin4 13 // Trigger Pin 4

int ledR1=5;
int ledG1=4;
int ledR2=3;
int ledG2=2;

unsigned long time_since_last_reset=0;
unsigned int time_since_last_rese2=0;
int timer=5000;
int s1counter=0,sensor1; // for sensor 1
int s2counter=0,sensor2; // for sensor 2
int s3counter=0,sensor3; // for sensor 3
int s4counter=0,sensor4; // for sensor 4
int counter1=0,counter2=0,counter3=0,counter4=0; //for direction

long duration1,duration2,duration3,duration4; // Duration used to calculate distance

int s;
void sensing(int echo,int trig,long duration,long sensor)
{
   digitalWrite(trig,LOW);
    delayMicroseconds(2);
        digitalWrite(trig,HIGH);
        delayMicroseconds(10);
        digitalWrite(trig,LOW); 
        duration=pulseIn(echo,HIGH);
        delayMicroseconds(10);
        sensor=duration*0.034/2;
        s=sensor;        
}

int c;
 void counting(int count,int sen,int trig,int echo,long d)
  {    
  label:
       if(sen>10)
    {  
      count++;
      if(trig==trigpin1)
      {
      Serial.print("s1counter=");
      }
      if(trig==trigpin2)
      {
      Serial.print("s2counter=");
      }
     if(trig==trigpin3)
      {
      Serial.print("s3counter=");
      }
     if(trig==trigpin4)
      {
      Serial.print("s4counter=");
      }
      Serial.println(count);
      c=count;
       delay(1000);
    }
      else
      {
         digitalWrite(trig,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
        d=pulseIn(echo,HIGH);
       delayMicroseconds(10);
       sen=d*0.034/2;
    
       goto label;
      }
  }
void setup() {
 Serial.begin (9600);

 pinMode(trigpin1, OUTPUT);
 pinMode(echopin1, INPUT);
 pinMode(trigpin2, OUTPUT);
 pinMode(echopin2, INPUT);
 pinMode(trigpin3, OUTPUT);
 pinMode(echopin3, INPUT);
 pinMode(trigpin4, OUTPUT);
 pinMode(echopin4, INPUT);
 pinMode(ledR1, OUTPUT);
 pinMode(ledG1, OUTPUT); 
 pinMode(ledR2, OUTPUT);
 pinMode(ledR2, OUTPUT);
 servo1.attach(14);
 servo2.attach(15);
}

void loop() 
{ 
 sensing(echopin1,trigpin1,duration1,sensor1);
 sensor1=s;
 sensing(echopin2,trigpin2,duration2,sensor2);
     sensor2=s;
    sensing(echopin3,trigpin3,duration3,sensor3);
     sensor3=s;
 sensing(echopin4,trigpin4,duration4,sensor4);
 sensor4=s;
 //Calculate the distance (in cm) based on the speed of sound. 
 if(sensor1>10 && sensor2>10)
 {
   digitalWrite(ledR1,LOW);
   digitalWrite(ledG1,HIGH);
   digitalWrite(ledR2,HIGH);
   digitalWrite(ledG2,LOW);
   servo1.write(0);
   servo2.write(0);
 }
 labelB:
 if(sensor1<=10)
 {
  servo2.write(90);
  servo1.write(0); 
   digitalWrite(ledR1,LOW);
   digitalWrite(ledG1,HIGH);
   digitalWrite(ledR2,HIGH);
   digitalWrite(ledG2,LOW);
   counting(s1counter,sensor1,trigpin1,echopin1,duration1);
   s1counter=c;
   sensing(echopin1,trigpin1,duration1,sensor1);
   sensor1=s;
  time_since_last_reset=millis();
  while((millis()-time_since_last_reset)<timer)
     {
      if(sensor1<=10)
      {
        counting(s1counter,sensor1,trigpin1,echopin1,duration1);
        s1counter=c;
     }
     sensing(echopin1,trigpin1,duration1,sensor1);
     sensor1=s;
     sensing(echopin2,trigpin2,duration2,sensor2);
     sensor2=s;
      if(sensor2<=10)
      {
        counting(s2counter,sensor2,trigpin2,echopin2,duration2);
        s2counter=c;
      }
      sensing(echopin3,trigpin3,duration3,sensor3);
      sensor3=s;
      if(sensor3<=10)
      {
       counting(s3counter,sensor3,trigpin3,echopin3,duration3);
       s3counter=c;
     }
      
      
    }
   servo1.write(90);
   digitalWrite(ledR1,HIGH);
   digitalWrite(ledG1,LOW);
   labelA:
   if(s2counter!=0 && s3counter!=0)
   {
   if(s1counter==s2counter && s2counter==s3counter)
   {
    digitalWrite(ledG1,HIGH);
    digitalWrite(ledG2,HIGH);
    digitalWrite(ledR1,LOW);
    digitalWrite(ledR2,LOW);
    s1counter=0;
    s2counter=0;
    s3counter=0;
   }
   }
   if(s1counter!=s2counter || s2counter!=s3counter)
   {
    time_since_last_reset=millis();
    while((millis()-time_since_last_reset)<5000)
    { 
       sensing(echopin2,trigpin2,duration2,sensor2);
       sensor2=s;
      if(sensor2<=10)
      {
        counting(s2counter,sensor2,trigpin2,echopin2,duration2);
       s2counter=c;
      }
      sensing(echopin3,trigpin3,duration3,sensor3);
      sensor3=s;
      if (sensor3<=10)
      {
        counting(s3counter,sensor3,trigpin3,echopin3,duration3);
       s3counter=c;
      }      
    }
    goto labelA;
  }
  if(sensor4>10)
  {
    goto labelB; 
  }
 }

labelD:
  if(sensor4<=10)
 {
  servo2.write(0);
  servo1.write(90);
  digitalWrite(ledR1,HIGH);
  digitalWrite(ledG1,LOW);
  digitalWrite(ledR2,LOW);
  digitalWrite(ledG2,HIGH);
  counting(s4counter,sensor4,trigpin4,echopin4,duration4);
        s4counter=c;
   sensing(echopin4,trigpin4,duration4,sensor4);
   sensor4=s;
  time_since_last_reset=millis();
  while((millis()-time_since_last_reset)<timer)
     {
      if(sensor4<=10)
      {
        counting(s4counter,sensor4,trigpin4,echopin4,duration4);
        s4counter=c;
     }
     sensing(echopin4,trigpin4,duration4,sensor4);
     sensor4=s;
     sensing(echopin3,trigpin3,duration3,sensor3);
     sensor3=s;
      if(sensor3<=10)
      {
        counting(s3counter,sensor3,trigpin3,echopin3,duration3);
        s3counter=c;
      }
      sensing(echopin2,trigpin2,duration2,sensor2);
      sensor2=s;
      if(sensor2<=10)
      {
       counting(s2counter,sensor2,trigpin2,echopin2,duration2);
       s2counter=c;
     }
      
      
    }
   servo2.write(90);
   digitalWrite(ledR1,LOW);
   digitalWrite(ledG1,HIGH);
   labelC:
   if(s2counter!=0 && s3counter!=0)
   {
   if(s4counter==s3counter && s3counter==s2counter)
   {
    digitalWrite(ledG1,LOW);
    digitalWrite(ledG2,LOW);
    digitalWrite(ledR1,HIGH);
    digitalWrite(ledR2,HIGH);
    s4counter=0;
    s3counter=0;
    s2counter=0;
   }
   }
   if(s4counter!=s3counter || s3counter!=s2counter)
   {
    time_since_last_reset=millis();
    while((millis()-time_since_last_reset)<5000)
    { 
       sensing(echopin3,trigpin3,duration3,sensor3);
       sensor3=s;
      if(sensor3<=10)
      {
        counting(s3counter,sensor3,trigpin3,echopin3,duration3);
       s3counter=c;
      }
      sensing(echopin2,trigpin2,duration2,sensor2);
      sensor2=s;
      if(sensor2<=10)
      {
        counting(s2counter,sensor2,trigpin2,echopin2,duration2);
       s2counter=c;
      }      
    }
    goto labelC;
  }
  if(sensor1>10)
  {
    goto labelD; 
  }
 }
}
