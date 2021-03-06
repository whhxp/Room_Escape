/*
对于推杆
继电器low =开通= 出
继电器high=关闭 = 进


 */
#define DEBUG 1
#define BIG 5
//set key numbers    as   input pin
const int key[4] =
{
	A1,A2,A3,A4
};
const int BigButton=A0;
//set DoorOpen
const int DoorOpen = 9;

//set music play pin
const int MusicPlay1 = 10;
const int MusicPlay2 = 11;

// set ID recongnition and push rod pin numbers:
const int CardInPut = 3;        // set CardInPut as InPut Pin
const int PushPin =  2;

//relay pin to control all 220v components such as lights and speaker
const int relay_pin=12;
// set password
const char password[8] =
{
	4,4,1,2,2,4,3,3
};
char PasswordTemp[9];
int passwd_ok_flag = 0;
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

unsigned char reset_all();
unsigned char card_vertify();
unsigned char push_drawer();
unsigned char enter_passwd();
unsigned char check_passwd();
unsigned char play_voice(unsigned char num);
unsigned char alarm();
unsigned char turnoff_lights();
unsigned char open_door();

void setup()
{
	Serial.begin(9600);
	// initialize the LED pin as an output:
	pinMode(PushPin, OUTPUT);
	pinMode(DoorOpen, OUTPUT);
	pinMode(MusicPlay1, OUTPUT);
	pinMode(MusicPlay2, OUTPUT);
	pinMode(relay_pin, OUTPUT);

}

void loop()
{
	reset_all();
	while (card_vertify() != 1)
	{
	}
	push_drawer();

	while ( enter_passwd() == 1)
	{
		if ( check_passwd() == 1)
		{
			break;
		}
		else
		{
			alarm();
		}
	}
	if (is_passwd_ok() == 1)
	{
		play_voice(1);
		turnoff_lights();
		open_door();
	}
}
int is_passwd_ok()
{
	if (passwd_ok_flag ==1)
	{
		passwd_ok_flag=0;
		return 1;
	}
	else
		return 0;
}


int keyscan (void)
{
	int i,j;
	int KeyValue=0,val;
	val = analogRead(BigButton);
	delay(2);
	if (val > 800)
	{
		delay(20);
		val = analogRead(BigButton);
		delay(2);
		if (val > 800)
		{
			delay(20);
			while (val > 800)
			{
				val = analogRead(BigButton);
				delay(2);
			}
			Serial.println("big");
			return BIG;
		}
	}
	for (i=0; i<4; i++)
	{
		j=i+1;
		KeyValue = analogRead(key[i]);
		delay(2);
		if (KeyValue > 800)
		{
			delay(20);
			KeyValue = analogRead(key[i]);
			delay(2);
			if (KeyValue > 800)
			{
				delay(20);
				while (KeyValue > 800)
				{
					KeyValue = analogRead(key[i]);
					delay(2);
				}
				Serial.println(j);
				return j;

			}
		}
	}

	return 0;
}

unsigned char reset_all()
{
	/*
	  pinMode(PushPin, OUTPUT);
	 pinMode(DoorOpen, OUTPUT);
	 pinMode(MusicPlay1, OUTPUT);
	 pinMode(MusicPlay2, OUTPUT);
	 pinMode(relay_pin, OUTPUT);
	 */
	digitalWrite(relay_pin, LOW);
	digitalWrite(MusicPlay1, HIGH);
	digitalWrite(MusicPlay2, HIGH);
	digitalWrite(DoorOpen, HIGH);
	digitalWrite(PushPin, HIGH);
#if DEBUG
	Serial.print("resetall\n");
#endif
	delay(10000);
}

unsigned char card_vertify()
{

	// ID Card check and push drawer
	if (digitalRead(CardInPut) ==0)
	{
#if DEBUG
		Serial.print("card vertifed\n");
#endif
		return 1;
	}
	else return 0;
}


unsigned char push_drawer()
{
#if DEBUG
	Serial.print("push_drawer\n");
#endif
	digitalWrite(PushPin, LOW);
	delay(10000);
	return 1;
}


unsigned char enter_passwd()
{
	int PassWord_NO,i,key_val;
	for (PassWord_NO=0; PassWord_NO<9; PassWord_NO++)
	{
		key_val=keyscan();
		while (key_val== 0)
		{
			key_val=keyscan();
		}
		if (key_val== BIG)
		{
			if(dir_check() == 1);
			{
				return 0;
			}
			return 1;
		}
		else
		{
			PasswordTemp[PassWord_NO]=key_val;
		}
	}
	Serial.println("exit \'enter passwd\'");
	return 1;
}
unsigned char dir_check()
{
	int i;
	{
		if (PasswordTemp[0]==password[0]&&PasswordTemp[1]==password[1]&&PasswordTemp[2]==password[2]
		        &&PasswordTemp[3]==password[3]&&PasswordTemp[4]==password[4]&&PasswordTemp[5]==password[5]
		        &&PasswordTemp[6]==password[6]&&PasswordTemp[7]==password[7])
		{
			Serial.print("check passwd ok\n");
			passwd_ok_flag=1;
			return 1;
		}
		else
		{
			for (i=0; i<8; i++)
				PasswordTemp[i] = 0;
			Serial.print("check failed\n");
			return 0;
		}
	}
}

unsigned char check_passwd()
{
	if (keyscan()==BIG)     // if BigButton push      check data   if data wrong clean all data
	{
		return dir_check();
	}
}




unsigned char play_voice(unsigned char num)
{
	switch(num)
	{
	case 1:
		digitalWrite(MusicPlay1,LOW);
#if DEBUG
		Serial.print("play sound 1\n");
#endif
		return 1;
		break;
	case 2:
		digitalWrite(MusicPlay2,LOW);
#if DEBUG
		Serial.print("play sound 2--alarm!\n");
#endif
		return 2;
		break;
	default:
		return 0;
	}
}
unsigned char alarm()
{
	play_voice(2);
	return 0;
}
unsigned char turnoff_lights()
{
	digitalWrite(relay_pin, HIGH);
#if DEBUG
	Serial.print("turn off lights\n");
#endif
	return 0;
}
unsigned char open_door()
{
	digitalWrite(DoorOpen, LOW);
#if DEBUG
	Serial.print("door opened\n");
#endif
	delay(600000);
	return 0;
}














