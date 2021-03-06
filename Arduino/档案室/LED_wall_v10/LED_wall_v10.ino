/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#include "animation.h" 
#include "pin_def.h"
#include <stdio.h>
#include <stdlib.h>

#define go_process 1
#define DEBUG 0
#define ANIMATION_DBG 1


#define S(n) Serial.print(n)
#define Sln(nn) Serial.println(nn)
#define enter() S("enter function\t");Sln(__FUNCTION__)




void dbg()
{
  dbg1[0]++;
  send2wall(dbg1,dbg1,dbg1,0,1);
}
int i, i2,cnt=0;
int passwd_hint[]={
  0,0,1,1,0,1,0,1,1,0,1,1    };// this is the wall passwd
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  // initialize the digital pin as an output.
  for (i = 4; i < 8; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(push_door, OUTPUT);

  pinMode(out_door, OUTPUT);
  pinMode(out_signal, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() 
{
  wall_init();
  //while(digitalRead(in_rst_signal) == LOW)
  {
#if go_process
    while(door_open() != HIGH);
    door_open_animation();
    if(wait_four_question()==1)
      pusher_on_signal();
    if(wait_check_palm_signal()==1)
    {
      uv_animation();
      delay(3000);
    }
    while(wait_check_passwd_signal() !=1)
    {
      uv_animation();
      delay(3000);
    }
    open_door();
    while(1)
    {
      x_animation();
    }
#endif
#if ANIMATION_DBG
    door_open_animation();
    x_animation();
    uv_animation();
    unlock_animation(0);
    unlock_animation(1);
    unlock_animation(2);
    unlock_animation(3);
    unlock_animation(4);
#endif

  }
}
void pusher_on_signal()
{
  enter();
  digitalWrite(out_signal,LOW);
  return;
}
int wait_four_question()
{
#if DEBUG
  //dbg();
#endif
  int check[4];
  int pre=0,counter=0;
  enter();
  while(1)
  {
    int i;
    for (i = 0; i< 4; i++)
    {
      // S("number:");
      // Sln(i);
      check[i]=(analogRead(four_q_pin[i])>800)?1:0;
      counter+=check[i];
    }


    if (counter != pre || pre ==0)
      unlock_animation(counter);
    pre=counter;
#if DEBUG
    S("total:\t");
    Sln(counter);
#endif


    if(counter==4)
    {
      return 1;
    }
    else
    {
      counter=0;
    }
#if DEBUG
    Serial.print("checkTotal");
    Serial.println(counter);
#endif
  }
  //return counter;

}
int wait_check_palm_signal()
{
#if DEBUG
  dbg();
#endif
  enter();
  //Serial.println("wait_check_palm_signal()");
  if(analogRead(in_palm_correct) < 600)
  {
    delay(2);
    return 0;
  }
  return 1;
}
int wait_check_passwd_signal()
{
#if DEBUG
  dbg();
#endif
  enter();
  while(digitalRead(in_passwd_correct)!=HIGH);
  return 1;
}

void open_door()
{
#if DEBUG
  dbg();
#endif
  enter();
  //Serial.println("open_door_output()");
  digitalWrite(push_door,LOW);
}



void wall_init()
{
  /*
  
   #define push_door 9
   #define out_signal 13
   */

  send2wall(empty,empty,empty,500,1);
  digitalWrite(push_door,LOW);
  digitalWrite(out_signal,HIGH);
  //delay(10000);
#if DEBUG
  dbg();
#endif
}


int length(int *ar)
{
  return sizeof(ar)/sizeof(ar[0]);
}

int door_open()
{
  enter();
  Serial.println("elevator door open()");
  //return digitalRead(elevator_open_signal);

  return 1;
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
  enter();
#if DEBUG
  dbg();
#else
  send2wall(empty,door_open0,empty,500,1);
  send2wall(empty,door_open1,empty,500,1);
  send2wall(empty,door_open2,empty,500,1);
  send2wall(empty,door_open3,empty,500,1);
  send2wall(door_open_l_1,door_open3_1,door_open_r_1,500,1);
  send2wall(door_open_l_2,door_open3_1,door_open_r_2,500,1);
  send2wall(door_open_l_3,door_open3_1,door_open_r_3,500,1);
  send2wall(door_open_l_4,door_open3_1,door_open_r_4,500,1);  
#endif
}


void x_animation()
{
  enter();

  int i;
  send2wall(empty,empty,empty,10,1);
  for ( i=0; i<24;i++)
  {
    send2wall(x,x,x,200,2);
  }
}



void uv_animation()
{
  enter();

  int i;

  for ( i=0; i<12;i++)
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
  enter();
#if DEBUG
  //dbg();
#else

  //send2wall(empty,empty,empty,100,1);
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
    send2wall(empty,empty,empty,500,1);
    send2wall(unlock,unlock,unlock,1500,1);
    send2wall(empty,empty,empty,500,1);
    send2wall(unlock,unlock,unlock,1500,1);
    send2wall(empty,empty,empty,500,1);
    break;
  default:
    send2wall(empty,empty,empty,500,1);

  }
#endif  
}






























