/*
This program is used to control 32 light boxes on the floor.

 state:
 buttonstate:
 0---- not pressed
 1---- pressed

 for switch, 0 ----- pressed
 1 ------ not pressed

 for lightbox
 low -------- on
 high --------off

 by whh.
 2015/2/8

 */
#include "pin_def.h"
#include "arduino_debug.h"

#define hint_time 300


#define DEBUG 1
int i,j,t;
int in_signal;
int buttonState[4][8] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};         // variable for reading the pushbutton status
int right_State[4][8] =
{
	0,0,1,0,1,1,0,0,
	1,0,0,1,1,0,1,1,
	0,0,1,0,1,1,0,0,
	1,0,0,1,0,0,1,1
};         // variable for reading the pushbutton status

int key[15]= {9,3,12,13,5,6,15,16,32,31,22,21,28,19,25};
int right_order[15];
void floor_light_init(void)
{
	for ( i =0; i < 4; i++)
		{
			for ( j = 0; j<8 ; j++)
				LIGHTOFF(lightbox[i][j]);
		}
	DH(EFFECT_1);
	DH(EFFECT_2);
	DH(EFFECT_3);
}


static void light_right_effect(void)
{
	DL(EFFECT_1);
	DL(EFFECT_2);
	DL(EFFECT_3);
}
static void light_wrong_effect(void)
{
	DL(EFFECT_1);
	DH(EFFECT_2);
	DL(EFFECT_3);
}

static void open_next_door(void)
{
	DL(EFFECT_1);
	DH(EFFECT_2);
	DH(EFFECT_3);
}

// the setup routine runs once when you press reset:
void setup()
{
	Serial.begin(9600);
	// initialize the digital pin as an output.
	for ( i =0; i < 4; i++)
		{
			for ( j = 0; j<8 ; j++)
				pinMode(lightbox[i][j], OUTPUT);
		}

	pinMode(EFFECT_1, OUTPUT);
	pinMode(EFFECT_2, OUTPUT);
	pinMode(EFFECT_3, OUTPUT);
	floor_light_init();

}

static void read_buttons(void)
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
							if (buttonState[i][j]==right_State[i][j]&&(i*8+j+1)==key[t])
								{
									right_order[t]=1;
									t++;
								}
							else
								{
									light_wrong_effect();
									t=0;
								}
						}
					else
						{
							buttonState[i][j]=0;
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
							if (buttonState[i][j]==right_State[i][j]&&(i*8+j+1)==key[t])
								{
									right_order[t]=1;
									t++;
								}
							else
								{
									light_wrong_effect();
									hint();
									t=0;
								}
						}
					else
						{
							buttonState[i][j]=0;
							digitalWrite(lightbox[i][j],HIGH);
						}

				}
		}

}

// the loop routine runs over and over again forever:
void loop()
{
	floor_light_init();
	t=0;
re_hint:
	hint();
	while(1)
		{
			read_buttons();
			if (t==15)
				{
					light_right_effect();
					open_next_door();
					while(1);
				}
		}
	goto re_hint;
}

static void hint()
{
	int i,j,tmp1;
	for (i=0 ,tmp1=0; i<4; i++)
		for (j=0 ; j<8; i++)
			{
				if((i*8+j+1) == key[tmp1])
					{
						LIGHTON(lightbox[i][j]);
						delay(hint_time);
						LIGHTOFF(lightbox[i][j]);
						tmp1++;
					}
			}
}
















