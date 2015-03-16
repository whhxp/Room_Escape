#include "led.h"
#include <Arduino.h>


void led_wall::Init(int clk, int le, int oe,int sdi)
{
  _lePin=le; 
    _clkPin=clk; 
    _oePin=oe; 
    _sdiPin=sdi;
  pinMode(_lePin,OUTPUT);
  pinMode(_clkPin,OUTPUT);
  pinMode(_oePin,OUTPUT);
  pinMode(_sdiPin,OUTPUT);
}


void led_wall::DataSend(int LedData) 
{
  int i;
  digitalWrite(_clkPin, LOW); 
  digitalWrite(_lePin, LOW);
  digitalWrite(_oePin, HIGH);
  for ( i = 0; i < 8; i++) 
  {
    if (LedData & 0x8000) 
    {
      digitalWrite(_sdiPin, HIGH);
      digitalWrite(_clkPin, HIGH);
      digitalWrite(_clkPin, LOW);
    } 
    else 
    {
      digitalWrite(_sdiPin, LOW);
      digitalWrite(_clkPin, HIGH);
      digitalWrite(_clkPin, LOW);
    }
    LedData <<= 1;
  }
  //delay (50);
  for (i = 0; i < 8; i++) 
  {
    if (LedData & 0x8000) 
    {
      digitalWrite(_sdiPin, HIGH);
      digitalWrite(_clkPin, HIGH);
      digitalWrite(_clkPin, LOW);
    } 
    else 
    {
      digitalWrite(_sdiPin, LOW);
      digitalWrite(_clkPin, HIGH);
      digitalWrite(_clkPin, LOW);
    }
    LedData <<= 1;
  }
  //delay (50);

}

void led_wall::DataLock(void) 
{
  digitalWrite(_lePin, HIGH);
  digitalWrite(_oePin, LOW);
}

void led_wall::send2wall(short* l, short* m,short* r,int d_time)
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


