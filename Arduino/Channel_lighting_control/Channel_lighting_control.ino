/*
This program is used to control 12 relays which turn on the lightboxes 
 in channel.
 
 
 by whh.
 2015/2/7
 
 */
#include "pin_define.h"

#define DEBUG 0

int i,j;
int in_signal;
// the setup routine runs once when you press reset:


unsigned char led_on();
unsigned char led_off();
unsigned char led_order();
unsigned char led_test();



unsigned char start_effect(unsigned char para);

unsigned char check_order();


void setup() {                
  // initialize the digital pin as an output.
  for ( i =0; i < 12; i++)
  {
    for ( j = 0; j<3 ; j++)
      pinMode(lightbox[i][j], OUTPUT);
  }

}

// the loop routine runs over and over again forever:
void loop() {
#if DEBUG
  in_signal =1;
  for ( i =0; i < 12; i++)
  {
    for ( j = 0; j<3 ; j++)
      digitalWrite(lightbox[i][j], HIGH);  
  }
  if (in_signal == 1)
  {
    for (i = 0 ; i < 12; i++)
    {
      for ( j = 0; j<3 ; j++)
      {
        digitalWrite(lightbox[i][j], LOW);
        delay(200);
      }
    }
  }
  for ( i =0; i < 12; i++)
  {
    for ( j = 0; j<3 ; j++)
      digitalWrite(lightbox[i][j], LOW);  
  }
  if (in_signal == 1)
  {
    for (i = 0 ; i < 12; i++)
    {
      for ( j = 0; j<3 ; j++)
      {
        digitalWrite(lightbox[i][j], HIGH);
        delay(200);
      }
    }
  }
#endif
  
}

unsigned char led_on()
{
  
}
unsigned char led_off()
{
  
}
unsigned char led_order()
{
  
}
unsigned char led_test()
{
  
}



unsigned char start_effect(unsigned char para)
{
  
}

unsigned char check_order()
{
  
}
