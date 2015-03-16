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

 			初始	正确	错误	开门	无信号
 effect_0	0		1		0		0		1
 effect_1	0		1		0		1		0
 effect_2	0		1		1		0		0

 by whh.
 2015/2/22

 */
#include "pin_def.h"
#include "arduino_debug.h"

#define hint_time 100


#define DEBUG 1
int i,j,t,wrong_time=0;
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

int key[15]=
{
	9,3,12,13,5,6,15,16,32,31,22,21,28,19,25
};
//上面是键值
//
//
//
int right_order[15];


int search_dst(int* src, int n)
{
	int tmp,len= sizeof(src)/sizeof(int);
	for (tmp = 0; tmp < len; tmp++)
	{
		if (src[tmp] == n)
			return n;
		else
			return -1;
	}
}


void floor_light_init(void)
{
	enter();
	for ( i =0; i < 4; i++)
	{
		for ( j = 0; j<8 ; j++)
		{
			LIGHTON(lightbox[i][j]);
		}
	}
	for (i = 0; i<15; i++)
	{
		right_order[i]=0;
	}
	DL(EFFECT_1);
	DL(EFFECT_2);
	DL(EFFECT_3);
	delay(10);//10ms后回复无信号状态，100为无信号状态
	DH(EFFECT_1);
	DL(EFFECT_2);
	DL(EFFECT_3);
	delay(15000);
	for ( i =0; i < 4; i++)
	{
		for ( j = 0; j<8 ; j++)
		{
			LIGHTOFF(lightbox[i][j]);
		}
	}
}


static void light_right_effect(void)
{
	enter();
	DH(EFFECT_1);
	DH(EFFECT_2);
	DH(EFFECT_3);
	delay(10);//10ms后回复无信号状态，100为无信号状态
	DH(EFFECT_1);
	DL(EFFECT_2);
	DL(EFFECT_3);
}
static void light_wrong_effect(void)
{
	enter();
	DL(EFFECT_1);
	DL(EFFECT_2);
	DH(EFFECT_3);
	delay(10);//10ms后回复无信号状态，100为无信号状态
	DH(EFFECT_1);
	DL(EFFECT_2);
	DL(EFFECT_3);
}

static void open_next_door(void)
{
	enter();
	DL(EFFECT_1);
	DH(EFFECT_2);
	DL(EFFECT_3);
	delay(10);//10ms后回复无信号状态，100为无信号状态
	DH(EFFECT_1);
	DL(EFFECT_2);
	DL(EFFECT_3);
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
	//floor_light_init();

}

static int read_buttons(void)
{
	//enter();
	int tmp=0,pre_tmp=0;
	for (i=0 ; i<2; i++)
	{
		for (j=0; j<8; j++)
		{
			if (analogRead(floor_switch[i][j])<100)
			{

				buttonState[i][j]=1;
				digitalWrite(lightbox[i][j],LOW);
				
				if (buttonState[i][j]==right_State[i][j])
				{
					right_order[search_dst(key,i*8+j+1)]=1;
					//Sln(i*8+j+1);
					//break;
					//break;
				}
				else
				{
					//tmp=i*8+j;
					light_wrong_effect();
					hint();
				}
			}
			else
			{
				buttonState[i][j]=0;
				digitalWrite(lightbox[i][j],HIGH);
				return -1;
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
				if (buttonState[i][j]==right_State[i][j])
				{
					right_order[search_dst(key,i*8+j+1)]=1;
				}
				else
				{
					light_wrong_effect();
					hint();
				}
			}
			else
			{
				buttonState[i][j]=0;
				digitalWrite(lightbox[i][j],HIGH);
				return -1;
			}

		}
	}
}


// the loop routine runs over and over again forever:
void loop()
{
	enter();
	floor_light_init();

	t=0;
re_hint:
	hint();
	while(1)
	{
		read_buttons();
		for (i = 0; i<15; i++)
		{
			if(right_order[i]==1)
				t++;
		}
		if (t == 15)
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
	enter();
	int i;
	for (i = 0; i<15; i++)
	{
		LIGHTON(hint_lights[i]);
		delay(hint_time);
		LIGHTOFF(hint_lights[i]);
	}

}

static void floor_light_on_all()
{
	for ( i =0; i < 4; i++)
	{
		for ( j = 0; j<8 ; j++)
			LIGHTON(lightbox[i][j]);
	}
}

static void floor_light_off_all()
{
	for ( i =0; i < 4; i++)
	{
		for ( j = 0; j<8 ; j++)
			LIGHTOFF(lightbox[i][j]);
	}
}














