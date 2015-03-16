/*
This program is used to control 32 light boxes on the floor.
 
 state:
 buttonstate:
 0---- not pressed
 1---- pressed
 
 for switch, 0 ----- pressed
 1 ------ not pressed
 
 for lightbox   low -------- on
 high --------off
 by whh.
 2015/2/8
 
 */
#include "pin_def.h"
#define DEBUG 1
int i,j;
int in_signal;
int buttonState[4][8] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0};         // variable for reading the pushbutton status
// the setup routine runs once when you press reset:
void setup() {                
  Serial.begin(9600);
  // initialize the digital pin as an output.
  for ( i =0; i < 4; i++)
  {
    for ( j = 0; j<8 ; j++)
      pinMode(lightbox[i][j], OUTPUT);
  }
}



// the loop routine runs over and over again forever:
void loop() {
  //in_signal =1;
  //light_effect();
#if 1
  while(1)
  {
#if DEBUG
    read_buttons_invert();
#endif
  }
#endif
}





void light_effect()
{
  for ( i =0; i < 4; i++)
  {
    for ( j = 0; j<8 ; j++)
      digitalWrite(lightbox[i][j], HIGH);  
  }
  if (1)
  {
    for (i = 0 ; i < 4; i++)
    {
      for ( j = 0; j<8 ; j++)
      {
        digitalWrite(lightbox[i][j], LOW);
        delay(1000);
      }
    }
  }
}

void read_buttons_invert()
{
  int tmp=0,tmp_prev=0;
  for (i=0 ; i<2; i++)
  {
    for (j=0; j<8; j++)
    {
      tmp=analogRead(floor_switch[i][j]);
      if (tmp<100)
      {
        buttonState[i][j]=1;
        digitalWrite(lightbox[i][j],HIGH);
      }
      else
      {
        digitalWrite(lightbox[i][j],LOW);
      }
    }
  }
  for (i=2 ; i<4; i++)
  {
    for (j=0; j<8; j++)
    {
      if (digitalRead(floor_switch[i][j])==0)
      {
        buttonState[i][j]=1;
        digitalWrite(lightbox[i][j],HIGH);
      }
      else
      {
        buttonState[i][j]=0;
        digitalWrite(lightbox[i][j],LOW);
      }

    }
  }
}

void read_buttons()
{
  int tmp=0,tmp_prev=0;
  for (i=0 ; i<2; i++)
  {
    for (j=0; j<8; j++)
    {
      tmp=analogRead(floor_switch[i][j]);
      if (tmp<100)
      {
        buttonState[i][j]=1;
        digitalWrite(lightbox[i][j],LOW);
      }
      else
      {
        digitalWrite(lightbox[i][j],HIGH);
      }
    }
  }
  for (i=2 ; i<4; i++)
  {
    for (j=0; j<8; j++)
    {
      if (digitalRead(floor_switch[i][j])==0)
      {
        buttonState[i][j]=1;
        digitalWrite(lightbox[i][j],LOW);
      }
      else
      {
        buttonState[i][j]=0;
        digitalWrite(lightbox[i][j],HIGH);
      }

    }
  }
}







