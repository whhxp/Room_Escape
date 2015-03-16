#include <Arduino.h>
unsigned char lightbox[4][8]=
{
	{
		15,14,37,36,35,34,33,32
	}
	,{
		31,30,29,28,27,26,25,24
	}
	,{
		53,52,51,50,49,48,47,46
	}
	,{
		45,44,43,42,41,40,39,38
	}
};
unsigned char floor_switch[4][8]=
{
	{
		A15,A14,A13,A12,A11,A10,A9,A8
	}
	,{
		A7,A6,A5,A4,A3,A2,A1,A0
	}
	,{
		23,22,21,20,19,18,17,16
	}
	,{
		6,7,8,9,10,11,12,13
	}
};


unsigned char hint_lights[]= {lightbox[1][0],lightbox[0][2],lightbox[1][3],lightbox[1][4],
                              lightbox[0][4],lightbox[0][5],lightbox[1][6],lightbox[1][7],
                              lightbox[3][7],lightbox[3][6],lightbox[2][5],lightbox[2][4],
                              lightbox[3][3],lightbox[2][2],lightbox[3][0]
                             };

#define EFFECT_1         (3)
#define EFFECT_2         (4)
#define EFFECT_3         (5)
