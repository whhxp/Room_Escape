/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#include "animation.h" 

//output signal
#define CLK 4
#define LE 5 // LAT
#define OE 6
#define SDI 7 // DATA


//input pin
#define door_open_signal 8

int i, i2,cnt=0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  for (i = 4; i < 8; i++) {
    pinMode(i, OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
#if !DEBUG
  if(door_open())
    door_open_animation();

  while (cnt < 4) {

    cnt ++;

  }
#endif
#if DEBUG
  door_open_animation();
  x_animation();
#endif
}

int door_open()
{
  return digitalRead(door_open_signal);
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

void send2wall(short* l, short* m,short* r,int d_time,int mode)
{
  //mode 1,normal
  //mode 2,x mode
  int i2;
  for (i2 =0; i2 < 4; i2++) {
    DataSend(r[i2]);
    if (mode == 2)
      DataLock();
  }
  if (mode == 2)
  {
    if (d_time != 0)
      delay(d_time);
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
  for ( i=0; i<24;i++)
    send2wall(x,empty,empty,200,2);
}



void uv_animation()
{
  int i;
  int string1[]={
    0,0,1,1,0,1,0,1  };
  for ( i=0; i<8;i++)
  {
    if (string1[i]==0)
      send2wall(u,empty,empty,200,2);
    else
      send2wall(v,empty,empty,200,2);
  }
}




