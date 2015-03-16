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
#define DEBUG 1
#define ANIMATION_DBG 0


#define S(n) Serial.print(n)
#define Sln(nn) Serial.println(nn)
#define enter() S("enter function\t");Sln(__FUNCTION__)
int i, i2,cnt=0;
int passwd_hint[]=
{
  0,0,1,1,0,1,0,1,1,0,1,1
};// this is the wall passwd
// the setup routine runs once when you press reset:
void setup()
{
  Serial.begin(9600);
  // initialize the digital pin as an output.
  for (i = 4; i < 8; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  pinMode(push_door, OUTPUT);
  pinMode(out_signal, OUTPUT);
  digitalWrite(push_door,HIGH);
  digitalWrite(out_signal,HIGH);
}

// the loop routine runs over and over again forever:
void loop()
{

  digitalWrite(push_door,HIGH);
  digitalWrite(out_signal,HIGH);
  delay(5000);
  wall_init();
  //while(digitalRead(in_rst_signal) == LOW)
  {
#if go_process
    if (door_open() ==1)
    {
      //door_open_animation();
      if(wait_four_question()==1)
        pusher_on_signal();
      if(wait_check_palm_signal()==1)
      {
        digitalWrite(2,LOW);
        uv_animation();
        delay(3000);
      }
      while(1)
      {
        if(wait_check_passwd_signal()==1)
          break;
        uv_animation();
        delay(5000);
      }
      open_door();
      while(1)
      {
        x_animation();
      }
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
  int check[4];
  int pre=10,counter=0;
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


    if (counter != pre || pre == 0)
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
  enter();
  //Serial.println("wait_check_palm_signal()");
  while(analogRead(in_palm_correct) > 800)
  {
    delay(2);
    //Sln(analogRead(in_palm_correct));
    //return 0;
  }
  Sln(analogRead(in_palm_correct));
  return 1;
}
int wait_check_passwd_signal()
{
  enter();
  if (analogRead(in_passwd_correct) > 10)
  {
    return 0;
  }
  //Sln(digitalRead(in_passwd_correct));
  return 1;
}

void open_door()
{
#if DEBUG

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

  send2wall(empty,empty,empty,0,1);

  digitalWrite(push_door,HIGH);
  digitalWrite(out_signal,HIGH);
  //delay(10000);
#if DEBUG

#endif
}


int length(int *ar)
{
  return sizeof(ar)/sizeof(ar[0]);
}

int door_open()
{
  enter();
  //Serial.print("elevator door open()");
  int tmp=digitalRead(elevator_open_signal);
  if (tmp == HIGH)
  {
    Sln(tmp);
    return 1;
  }
  else
    return 0;
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
  for (i2 =0; i2 < 4; i2++)
  {
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
  for (i2 =0; i2 < 4; i2++)
  {
    DataSend(m[i2]);
  }
  for (i2 =0; i2 < 4; i2++)
  {
    DataSend(l[i2]);
  }
  DataLock();
  if (d_time != 0)
    delay(d_time);
}




void door_open_animation()
{
  enter();
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
  enter();

  int i;
  send2wall(empty,empty,empty,10,1);
  for ( i=0; i<24; i++)
  {
    send2wall(x,x,x,200,2);
  }
}



void uv_animation()
{
  enter();

  int i;

  for ( i=0; i<12; i++)
  {
    if(i % 3 == 0)
    {
      delay(5000);
      send2wall(empty,empty,empty,1500,1);
    }
    if (passwd_hint[i]==0)
    {
      send2wall(u,u,u,1200,2);
      //send2wall(empty,empty,empty,500,1);
    }
    else
    {
      send2wall(v,v,v,1200,2);
      //send2wall(empty,empty,empty,500,1);
    }
  }
}

void unlock_animation(int n)
{
  enter();

  //send2wall(empty,empty,empty,100,1);
  switch(n)
  {
  case 0:

    door_open_animation();
    break;
  case 1:

    send2wall(locked,locked,locked,0,1);
    break;
  case 2:
    send2wall(unlock,locked,locked,0,1);
    break;
  case 3:
    send2wall(unlock,unlock,locked,0,1);
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

}
































