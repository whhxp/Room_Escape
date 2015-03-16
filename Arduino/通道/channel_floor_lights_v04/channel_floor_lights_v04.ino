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
 effect_1	0		1		1		1		0
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
#if 0
	floor_light_off_all();
	delay(500);
	floor_light_on_all();
	delay(100);
	floor_light_off_all();
	delay(400);
	floor_light_on_all();
	delay(200);
	floor_light_off_all();
	delay(500);
	floor_light_on_all();
	delay(50);
	floor_light_off_all();
	delay(500);
	floor_light_on_all();
	delay(3000);
#endif
	floor_light_off_all();
	for (i=0; i< 15; i++)
		right_order[i]=0;
	DL(EFFECT_1);
	DL(EFFECT_2);
	DL(EFFECT_3);
	delay(10);//10ms后回复无信号状态，100为无信号状态
	DH(EFFECT_1);
	DL(EFFECT_2);
	DL(EFFECT_3);
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
	DH(EFFECT_2);
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


}

static int read_buttons(void)
{
	enter();
try_again:
	//
	int tmp=0,pre_tmp=0;
	for (i=0 ; i<2; i++)
	{
		for (j=0; j<8; j++)
		{
			if (analogRead(floor_switch[i][j])<100)
			{

				buttonState[i][j]=1;
				digitalWrite(lightbox[i][j],LOW);

				return (i*8+j+1);
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
				return (i*8+j+1);
			}
			else
			{
				buttonState[i][j]=0;
				digitalWrite(lightbox[i][j],HIGH);
			}

		}
	}
	goto try_again;
}


// the loop routine runs over and over again forever:
void loop()
{
	enter();
	floor_light_init();
	//delay(15000);
start1:
	//hint();
	for (i=0; i< 15; i++)
		right_order[i]=0;
	for (i=0; i< 15; i++)
	{
		for (j = 0; j< i; j++)
		{
			if (right_order[i] ==1)
				goto jump1;
		}
		while(read_buttons()!=key[i])
		{

			light_wrong_effect();
			//delay(1000);
			goto start1;
		}

		right_order[i]=1;
jump1:
		enter();
		S("key");
		Sln(i);
	}

	light_right_effect();
	open_next_door();
	while(1);
}

static inline void hint()
{
	enter();
	int i;
	delay(2000);
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















