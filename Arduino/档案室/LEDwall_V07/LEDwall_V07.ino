/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#include "animation.h" 
#include "led.h"


//output signal

#define CLK 4
#define LE 5 // LAT
#define OE 6
#define SDI 7 // DATA
#define palm_trigger 13
#define archive_door 3

//input pin
#define door_open_in_signal 12
#define map_light 8
#define _6key_9light 9
#define color_mix 10
#define timecnt 11
#define palm_done 2

int i, i2,cnt=0;
int check[]={
  0,0,0,0};
// the setup routine runs once when you press reset:
void door_open_animation();

void setup() {
  // initialize the digital pin as an output.
  for (i = 8; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(palm_trigger, OUTPUT);
  pinMode(archive_door, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() 
{
  if(door_open())
    door_open_animation();
  lock_on_wall();
  if (wait_signal())
    enable_palm();
  if (palm_finished())
    enable_input_passwd();
  if(passwd_finished())
  {
    open_archive_door();
    x_animation();
  }
}

int door_open()
{
  return digitalRead(door_open_in_signal);
}


int wait_signal()
{
#if 1
  int checkTotal=0;
  Serial.println(digitalRead(8));
  Serial.println(digitalRead(9));
  Serial.println(digitalRead(10));
  Serial.println(digitalRead(11));
  Serial.println("End");
  check[0]=digitalRead(2);
  check[1]=digitalRead(3);
  check[2]=digitalRead(4);
  check[3]=digitalRead(5);
  if(check[0]==1 && check[1]==1  && check[2]==1 && check[3]==1){
    checkTotal=1;
  }
  else{
    checkTotal=0;
  }
  Serial.print("checkTotal");
  Serial.println(checkTotal);
#endif
  return checkTotal;
  //return digitalRead(in_signal);
}


void lock_on_wall()
{
  send2wall(empty,empty,empty,0);
  send2wall(locked,locked,locked,0);
}

void door_open_animation()
{
  send2wall(empty,door_open0,empty,500);
  send2wall(empty,door_open1,empty,500);
  send2wall(empty,door_open2,empty,500);
  send2wall(empty,door_open3,empty,500);
  send2wall(door_open_l_1,door_open3_1,door_open_r_1,500);
  send2wall(door_open_l_2,door_open3_1,door_open_r_2,500);
  send2wall(door_open_l_3,door_open3_1,door_open_r_3,500);
  send2wall(door_open_l_4,door_open3_1,door_open_r_4,500);  
}



int enable_palm()
{
  return 0;
}

int palm_finished()
{
}


int enable_input_passwd()
{
  
}

int passwd_finished()
{
  return digitalRead(palm_done);
}

int open_archive_door()
{
  digitalWrite(archive_door,LOW);
  return 0;
}

int x_animation()
{
}

void DataSend(int LedData) 
{
  int i;
  digitalWrite(CLK, LOW); 
  digitalWrite(LE, LOW);
  digitalWrite(OE, HIGH);
  for ( i = 0; i < 8; i++) 
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

void send2wall(short* l, short* m,short* r,int d_time)
{
  int i2;
  for (i2 =0; i2 < 4; i2++) {
    DataSend(r[i2]);
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


