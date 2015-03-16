/*
This program is used to control 12 relays which turn on the lightboxes
 in channel.
 high==on
 low==off

 by whh.
 2015/2/7

 */
#include "pin_define.h"
#include "arduino_debug.h"

#define TEST 1
#define R	1
#define G	0
#define B	2

int i, j;
int in_signal;
// the setup routine runs once when you press reset:


unsigned char led_on(void);
unsigned char led_off(void);
unsigned char led_order(void);
unsigned char led_test(void);



unsigned char start_effect(void);
unsigned char right_effect(void);
unsigned char wrong_effect(void);


unsigned char check_order(void);


void setup()
{
  Serial.begin(9600);
  // initialize the digital pin as an output.
  for ( i = 0; i < 12; i++)
  {
    for ( j = 0; j < 3 ; j++)
      pinMode(lightbox[i][j], OUTPUT);
  }
  pinMode(PIN_OUT_DOOR, OUTPUT);
  digitalWrite(PIN_OUT_DOOR, HIGH);
  
  //sound pin initialization
  pinMode(snd_error, OUTPUT);
  digitalWrite(snd_error, HIGH);
  pinMode(snd_intro, OUTPUT);
  digitalWrite(snd_intro, HIGH);
  pinMode(snd_login, OUTPUT);
  digitalWrite(snd_login, HIGH);
  pinMode(snd_auth, OUTPUT);
  digitalWrite(snd_auth, HIGH);
  
  
  /*INPUT PIN
   	#define	EFFECT_0	14
   	#define	EFFECT_1	15
   	#define	EFFECT_2	16
   	*/
}

// the loop routine runs over and over again forever:
void loop()
{
  //start_effect();
  int val, pre_val;
  while (1)
  {
    val = read_effect();
    if (val != pre_val)
    {
      switch (val)
      {
        case 7:
          Serial.println("right answer");
          break;
        case 1:
          Serial.println("wrong answerXXXXXXXXXXXXXXXXXXXXX");
          break;
        case 2:
          Serial.println("door");
          break;
        case 0:
          Serial.println("init.........................................................");
          break;
        default:
          Serial.println("N");
          break;
      }
      pre_val = val;
    }

  }

}

unsigned char read_effect()
{
  //enter();
  int effect_num[6], tmp;

  effect_num[0] = digitalRead(EFFECT_0);
  effect_num[1] = digitalRead(EFFECT_1);
  effect_num[2] = digitalRead(EFFECT_2);
  delay(5);
  effect_num[3] = digitalRead(EFFECT_0);
  effect_num[4] = digitalRead(EFFECT_1);
  effect_num[5] = digitalRead(EFFECT_2);

  if ((effect_num[3] != effect_num[0]) ||
      (effect_num[4] != effect_num[1]) || (effect_num[5] != effect_num[2]))
    return 4;

  if (effect_num[0] == 1 && effect_num[1] == 1 && effect_num[2] == 1)
  {
    //answer is right
    digitalWrite(snd_login, LOW);
    right_effect();
    digitalWrite(PIN_OUT_DOOR, LOW);
    return 7;
  }
  else if (effect_num[0] == 0 && effect_num[1] == 0 && effect_num[2] == 0)
  {
    //initial mode
    start_effect();
    return 0;
  }
  else if (effect_num[0] == 0 && effect_num[1] == 0 && effect_num[2] == 1)
  {
    // answer is wrong
    digitalWrite(snd_error, LOW);
    wrong_effect();

    return 3;
  }
  else if (effect_num[0] == 0 && effect_num[1] == 1 && effect_num[2] == 0)
  {
    //open door
    digitalWrite(snd_auth, LOW);
    digitalWrite(PIN_OUT_DOOR, LOW);

    //delay(60000);
    //digitalWrite(PIN_OUT_DOOR,HIGH);
    return 2;
  }

  else
  {
    return 4;
  }

}


unsigned char led_on(int num, int color)
{

  digitalWrite(lightbox[num][color], HIGH);
  return 0;
}

unsigned char led_off(int num, int color)
{
  digitalWrite(lightbox[num][color], LOW);
  return 0;
}

unsigned char led_all_off(void)
{
  enter();
  for ( i = 0; i < 12; i++)
  {
    led_off(i, R);
    led_off(i, G);
    led_off(i, B);
  }
}
unsigned char led_all_on(void)
{
  enter();
  for ( i = 0; i < 12; i++)
  {
    led_on(i, R);
    led_on(i, G);
    led_on(i, B);
  }
}

unsigned char start_effect(void)
{
  enter();
  led_all_off();
  delay(1000);
#if 0
  for ( i = 0; i < 6; i++)
  {
    led_on(i, R);
    led_on(i, G);
    led_on(i, B);
    delay(1500);
  }
  for ( i = 11; i >= 6; i--)
  {
    led_on(i, R);
    led_on(i, G);
    led_on(i, B);
    delay(1500);
  }
#endif
  led_all_on();
  digitalWrite(PIN_OUT_DOOR, HIGH);
}


unsigned char right_effect(void)
{
  enter();
  led_all_off();
  for ( j = 0; j < 3; j++)
  {
    for ( i = 0; i < 6; i++)
    {
      //led_on(i,R);
      led_on(i, G);
      //led_on(i,B);
      delay(500);
    }
    for ( i = 11; i >= 6; i--)
    {
      //led_on(i,R);
      led_on(i, G);
      //led_on(i,B);
      delay(500);
    }
    for ( i = 0; i < 6; i++)
    {
      //led_off(i,R);
      led_off(i, G);
      //led_off(i,B);
      delay(500);
    }
    for ( i = 11; i >= 6; i--)
    {
      //led_off(i,R);
      led_off(i, G);
      //led_off(i,B);
      delay(500);
    }
  }
  led_all_on();
}

unsigned char wrong_effect(void)//5.6sec
{
  enter();
  led_all_off();
  for (j = 0; j < 8; j++)
  {
    for ( i = 0; i < 6; i++)
    {
      led_on(i, R);
    }
    for ( i = 11; i >= 6; i--)
    {
      led_on(i, R);
    }
    delay(500);
    for ( i = 0; i < 6; i++)
    {
      led_off(i, R);
    }
    for ( i = 11; i >= 6; i--)
    {
      led_off(i, R);
    }
    delay(200);
  }
  led_all_on();
}


unsigned char test()
{
#if TEST
  for ( i = 0; i < 6; i++)
  {
    led_off(i, R);
    led_off(i, G);
    led_off(i, B);
    delay(500);
  }
  for ( i = 11; i >= 6; i--)
  {
    led_off(i, R);
    led_off(i, G);
    led_off(i, B);
    delay(500);
  }
#endif
}

