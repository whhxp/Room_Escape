/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#include "animation.h" 
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
#define ANIMATION_DBG 1
//output signal
#define CLK 4
#define LE 5 // LAT
#define OE 6
#define SDI 7 // DATA
#define out_door 2
#define out_signal 13



//input pin
#define door_open_signal 12
const int four_q_pin[]={
  A0,A1,A2,A3};//four questioon pin
#define in_passwd_correct 3
const int in_palm_correct=A4;

int i, i2,cnt=0;
int passwd_hint[]={
  0,0,1,1,0,1,0,1    };// this is the wall passwd
// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  for (i = 4; i < 8; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(out_door, OUTPUT);
  pinMode(out_signal, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
#if !DEBUG
  if(door_open())
    door_open_animation();
  if(wait_four_question()==1)
    pusher_on_signal();
  if(wait_check_palm_signal()==1)
    uv_animation();
  if(wait_check_passwd_signal() ==1)
    open_door();
  x_animation();
  while(1);
#if ANIMATION_DBG
  door_open_animation();
  x_animation();
  uv_animation();
  unlock_animation();
#endif
#endif
}

int wait_four_question()
{
  Serial.println("wait_four_question()");
  int check[4];
  int checkTotal=0;
  int i;
  for (i = 0; i< 4; i++)
  {
    check[i]=(analogRead(four_q_pin[i])>800)?1:0;
    checkTotal+=check[i];
    unlock_animation(checkTotal);
#if DEBUG
    Serial.println(check[i]);
#endif

  }
  if(check[0]==1 && check[1]==1  && check[2]==1 && check[3]==1)
  {
    checkTotal=1;
  }
  else
  {
    checkTotal=0;
  }
#if DEBUG
  Serial.print("checkTotal");
  Serial.println(checkTotal);
#endif
  return checkTotal;

}
int wait_check_palm_signal()
{
  Serial.println("wait_check_palm_signal()");
  while(analogRead(in_palm_correct) < 1000);
  return 1;
}
int wait_check_passwd_signal()
{
  Serial.println("wait_check_passwd_signal()");
  while(digitalRead(in_passwd_correct)!=HIGH);
  return 1;
}

void open_door()
{
  Serial.println("open_door_output()");
  digitalWrite(out_signal,LOW);
}

int length(int *ar)
{
  return sizeof(ar)/sizeof(ar[0]);
}

int door_open()
{
  Serial.println("elevator door open()");
#if !DEBUG
  //return digitalRead(door_open_signal);
#else
  return 1;
#endif
}


void DataSend(int LedData) 
{
  digitalWrite(CLK, LOW); 
  digitalWrite(LE, LOW);
  digitalWrite(OE, HIGH);
  for (i = 0; i < 8; i++) 
  {
    if (LedData & 0x8000) 
    {
      digitalWrite(SDI, HIGH);
      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
    } 
    else 
    {
      digitalWrite(SDI, LOW);
      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
    }
    LedData <<= 1;
  }
  //delay (50);
  for (i = 0; i < 8; i++) 
  {
    if (LedData & 0x8000) 
    {
      digitalWrite(SDI, HIGH);
      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
    } 
    else 
    {
      digitalWrite(SDI, LOW);
      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
    }
    LedData <<= 1;
  }
  //delay (50);

}

void DataLock(void) 
{
  digitalWrite(LE, HIGH);
  digitalWrite(OE, LOW);
}
/*

 send2wall
 para:
 l       -----left screen
 m       -----middle screen
 r       -----right screen
 d_time  ------delay time
 mode    ------1,normal mode
 2,shift mode
 
 */
void send2wall(short* l, short* m,short* r,int d_time,int mode)
{
  //mode 1,normal
  //mode 2,x mode
  int i2;
  for (i2 =0; i2 < 4; i2++) {
    DataSend(r[i2]);
    if (mode == 2)
    {
      DataLock();
      if (d_time != 0)
        delay(d_time);
    }
  }
  if (mode == 2)
  {
    return;
  }
  for (i2 =0; i2 < 4; i2++) {
    DataSend(m[i2]);
  }
  for (i2 =0; i2 < 4; i2++) {
    DataSend(l[i2]);
  }
  DataLock();
  if (d_time != 0)
    delay(d_time);
}




void door_open_animation()
{
  send2wall(empty,door_open0,empty,500,1);
  send2wall(empty,door_open1,empty,500,1);
  send2wall(empty,door_open2,empty,500,1);
  send2wall(empty,door_open3,empty,500,1);
  send2wall(door_open_l_1,door_open3_1,door_open_r_1,500,1);
  send2wall(door_open_l_2,door_open3_1,door_open_r_2,500,1);
  send2wall(door_open_l_3,door_open3_1,door_open_r_3,500,1);
  send2wall(door_open_l_4,door_open3_1,door_open_r_4,500,1);  
}


void x_animation()
{
  int i;
  send2wall(empty,empty,empty,500,1);
  for ( i=0; i<24;i++)
  {
    send2wall(x,x,x,200,2);
  }
}



void uv_animation()
{
  int i;

  for ( i=0; i<length(passwd_hint);i++)
  {
    if (passwd_hint[i]==0)
    {
      send2wall(u,u,u,1200,1);
      send2wall(empty,empty,empty,500,1);
    }
    else
    {
      send2wall(v,v,v,1200,1);
      send2wall(empty,empty,empty,500,1);
    }
  }
}

void unlock_animation(int n)
{
  send2wall(empty,empty,empty,100,1);
  switch(n)
  {
  case 0:
    send2wall(locked,locked,locked,0,1);
    break;
  case 1:
    send2wall(unlock,locked,locked,0,1);
    break;
  case 2:
    send2wall(unlock,unlock,locked,0,1);
    break;
  case 3:
    send2wall(unlock,unlock,unlock,0,1);
    break;
  case 4:
    send2wall(unlock,unlock,unlock,1500,1);
    send2wall(empty,empty,empty,100,1);
    send2wall(unlock,unlock,unlock,1500,1);
    send2wall(empty,empty,empty,100,1);
    send2wall(unlock,unlock,unlock,1500,1);
    send2wall(empty,empty,empty,100,1);
    break;
  default:
    send2wall(empty,empty,empty,100,1);

  }  
}











