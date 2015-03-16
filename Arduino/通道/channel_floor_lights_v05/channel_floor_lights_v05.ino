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
int t,wrong_time=0;
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
	enter();
	int tmp,len= sizeof(src)/sizeof(int);
	for (tmp = 0; tmp < 15; tmp++)
	{
		if (src[tmp] == n)
			return tmp;
		else
			return -1;
	}
}


void floor_light_init(void)
{
	int i,j;
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
	//delay(15000);
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
	int i,j;
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
	int i,j,t1,tmp=0,pre_tmp=0,wrong_flag=0;
	for (i=0 ; i<4; i++)
	{
		for (j=0; j<8; j++)
		{
			if (i<2)
			{
				tmp=analogRead(floor_switch[i][j])<100?1:0;
			}
			else
			{
				tmp=digitalRead(floor_switch[i][j])==0?1:0;
			}
			if (1==tmp)
			{
				buttonState[i][j]=1;
				digitalWrite(lightbox[i][j],LOW);
				if (buttonState[i][j]==right_State[i][j])
				{
					for (t1 =0; t1 < 15; t1 ++)
					{
						if ( key[t1]==(i*8+j+1))
							right_order[t1]=1;
					}
				}
				else//踩错按键
				{
					light_wrong_effect();
					wrong_flag=1;
					clear_right_flag();
				}
			}
			else//没踩按键
			{
				buttonState[i][j]=0;
				digitalWrite(lightbox[i][j],HIGH);
			}
		}
	}


///全部按键扫描完成后输出错误和提示
	if (wrong_flag == 1)
	{
		//light_wrong_effect();
		hint();
		wrong_flag=0;
	}
}

void clear_right_flag()
{
	int nn;
	for (nn = 0; nn<15; nn++)
	{
		right_order[nn]=0;
	}
}
// the loop routine runs over and over again forever:
void loop()
{
	enter();
	floor_light_init();
	int i,j;
	t=0;
re_hint:
	hint();
	while(1)
	{
		read_buttons();
		if(1==right_order[0]&&1==right_order[1]&&1==right_order[2]&&1==right_order[3]&&1==right_order[4]
		        &&1==right_order[5]&&1==right_order[6]&&1==right_order[7]&&1==right_order[8]&&1==right_order[9]
		        &&1==right_order[10]&&1==right_order[11]&&1==right_order[12]&&1==right_order[13]&&1==right_order[14])
		{
			key_on();
			light_right_effect();
			open_next_door();
			delay(300000);
			break;
		}
		for (i = 0; i<15; i++)
		{
			if (right_order[i]!=0)
			{
				S(key[i]);
				S("\t\t");
				S(right_order[i]);
				S("\n");
			}
		}

	}
	goto re_hint;

}

static void hint()
{
	enter();
	delay(5000);
	int i;
	for (i = 0; i<15; i++)
	{
		LIGHTON(hint_lights[i]);
		delay(hint_time);
		LIGHTOFF(hint_lights[i]);
	}

}

static void key_on()
{
	enter();
	int i;
	for (i = 0; i<15; i++)
	{
		LIGHTON(hint_lights[i]);

	}

}
static void floor_light_on_all()
{
	int i,j;
	for ( i =0; i < 4; i++)
	{
		for ( j = 0; j<8 ; j++)
			LIGHTON(lightbox[i][j]);
	}
}

static void floor_light_off_all()
{
	int i,j;
	for ( i =0; i < 4; i++)
	{
		for ( j = 0; j<8 ; j++)
			LIGHTOFF(lightbox[i][j]);
	}
}














