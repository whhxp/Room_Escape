/*
需要13个按钮
 
 */
#include <Arduino.h>
#define r 0
#define g 1
#define b 2

int button_hold[]={
  A0,A1,A2,A3,A4,A5,2,3,4,5,6,7,8};

int rightSignal=13;
int temp;
int rightAnswer[]={
  1,2,3,4,5,6,7,8,9,10,11,12,13};
int inputAnswer[]={
  0,0,0,0,0,0,0,0,0,0,0,0,0};
int numRecoder=0;

int rgb_ctl[]={
  9,10,11};//r,g,b order repectively

void setup()
{
  Serial.begin(9600);
  pinMode(rightSignal,OUTPUT);
  pinMode(rgb_ctl[r],OUTPUT);
  pinMode(rgb_ctl[g],OUTPUT);
  pinMode(rgb_ctl[b],OUTPUT);
}

void loop()
{
  init_led_effect();
  digitalWrite(rightSignal,LOW);
  numRecoder=0;

  while(1)
  {
    temp=buttonRead();
#if 1
    Serial.println(temp);
    inputAnswer[numRecoder]=temp;
    if(inputAnswer[numRecoder]!=rightAnswer[numRecoder])
    {
      //wrongEffect();
      //reset inputAnswer;
      Serial.println("WrongWrong");
      numRecoder=0;
      //delay(1000);
      for(int l=0;l<13;l++){
        inputAnswer[l]=0;
      }
    }
    else if(numRecoder==13){
      Serial.println("rightright");
      right_effect();
      digitalWrite(rightSignal, HIGH);
    }
    numRecoder++;
  }
#endif
}

void init_led_effect()
{
  digitalWrite(rgb_ctl[b],LOW);
}

void wrongEffect(){
  digitalWrite(rgb_ctl[r],LOW);
  delay(1000);
  digitalWrite(rgb_ctl[r],HIGH);
  delay(1000);
  digitalWrite(rgb_ctl[r],LOW);
  delay(1000);
  digitalWrite(rgb_ctl[r],HIGH);
}

void right_effect(){
  digitalWrite(rgb_ctl[g],LOW);
  delay(200);
  digitalWrite(rgb_ctl[g],HIGH);
  delay(200);
  digitalWrite(rgb_ctl[g],LOW);
}

int buttonRead()
{
  while(1)
  {
    /*如果没有感应到按键触发，则返回值99*/
    int i;
    for (i = 0; i< 6; i++)
    {
      if(analogRead(button_hold[i])<100)
      {
        delay(20);
        //if(analogRead(button_hold[i])<100)
        {
          //delay(20);
          while(analogRead(button_hold[i])>800)
          {
            //delay(20);
            //if(analogRead(button_hold[i])>800)
              return i+1;
          }
        }
      }
    }
    for (i =6; i< 13; i++)
    {
      if(digitalRead(button_hold[i])== LOW )
      {
        delay(20);
        //if(digitalRead(button_hold[i])== LOW )
        {
          //delay(20);
          while(digitalRead(button_hold[i])== HIGH)
          {
            //delay(20);
            //if(digitalRead(button_hold[i])== HIGH)
              return i+1;
          }
        }
      }
    }
  }
}


















