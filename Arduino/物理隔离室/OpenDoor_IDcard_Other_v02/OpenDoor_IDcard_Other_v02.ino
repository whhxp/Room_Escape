
#include "SoftwareSerial1.h"
#include "cmd.h"

#define S(n) Serial.print(n)
#define Sln(nn) Serial.println(nn)
#define enter() S("enter function\t");Sln(__FUNCTION__)

 // 设置输出管脚如下
 const int LightWall = 8;			//  灯箱继电器				relay 1         强电
 const int DoorOpen = 7;			//  打开卷闸门				relay 2			强电
 const int DoorClose = 6;			//  关闭卷帘门				relay 3			强电
 
 const int Boom = 5;				//  启动电磁脉冲炸弹		digital pin		
 const int PasswordPAD = 4;			//	启动密码输入装置		relay 1			弱电
 const int locker = 3;				//  设置抽屉电磁锁输出		relay 2        	弱电

  // 设置输入管脚如下
 
 const int plugs = 12; 				// 航空插头					switch 1
 const int Card_Input = 11;			//刷卡输入					switch 2
 const int PasswordPAD_check = 10;	// 密码输入是否正确			switch 3
 const int Door_bottom = 9;		// 设置开门按钮				
 
 int plugs_flag = 0;				//航空接头状态
 int Card_Input_flag = 0;			//是否刷卡状态
 int PasswordPAD_flag = 0;			// 密码盘是否启动状态
 int locker_flag = 0;			//灯箱启动状态
 int Door_flag = 0;					// 卷闸门状态
 
 
#define pin_rx 1
#define pin_tx 2
SoftwareSerial mySerial(pin_rx, pin_tx); // RX, TX
unsigned char set_track(unsigned char *cmd, unsigned char n)
{
  cmd[4] = n;
  send_cmd(cmd);
  return 0;
}

unsigned char adj_vol(unsigned char n)
{
  adjVol15[4] = n;
  send_cmd(adjVol15);
  return 0;
}

void send_cmd(unsigned char *cmd)
{
  check(cmd);
  mySerial.write(start, 2);
  mySerial.write(cmd, 7);
  mySerial.write(ending, 1);
  //Serial.write(start, 2);
  //Serial.write(cmd, 7);
  //Serial.write(ending, 1);
  delay(50);
}

char check(unsigned char *cmd)
{
  int sum, i;
  sum = 0xff;
  for (i = 0; i < 5; i++)
  {
    sum += cmd[i];
  }
  sum = ~sum + 1;
  cmd[5] = sum >> 8;
  cmd[6] = sum & 0xff;
  return sum;
}

unsigned char play_sound(unsigned char num)
{
  enter();
  mySerial.setTX(pin_tx);
  set_track(setTrack0, num);
  digitalWrite(pin_tx, LOW);
  return 0;
}
 
void setup() {
	pinMode(LightWall, OUTPUT);				//  灯箱继电器
	pinMode(Boom, OUTPUT);					//  启动电磁脉冲炸弹
	pinMode(PasswordPAD, OUTPUT);			//  启动密码输入装置
	pinMode(DoorOpen, OUTPUT);				//  打开卷闸门
	pinMode(DoorClose, OUTPUT);				//  关闭卷闸门
	pinMode(locker, OUTPUT);				//  设置抽屉锁继电器
	
	digitalWrite(LightWall,HIGH);			//初始化灯箱为无效状态
	digitalWrite(Boom,HIGH);				//初始化电磁脉冲炸弹为无效状态
	digitalWrite(PasswordPAD,HIGH);			//初始化密码盘为无效状态
	digitalWrite(DoorOpen,HIGH);			//初始化开门为无效状态
	digitalWrite(DoorClose,HIGH);			//初始化关门为无效状态
	digitalWrite(locker,HIGH);				//初始化抽屉锁为关闭状态

	

	pinMode(plugs, INPUT);          		// 航空插头
	pinMode(Card_Input, INPUT);				// 刷卡输入
	pinMode(PasswordPAD_check, INPUT);		// 密码输入是否正确
	pinMode(Door_bottom, INPUT);			// 设置开门按钮

	

	
}

// the loop function runs over and over again forever
void loop() {
	DoorClose_function();							//上电初始化  关门
	plugs_function();								//等待航空插头接入
	Card_Input_function();							//等待刷卡
	Boom_function();								//启动电磁脉冲炸弹 炸弹启动完成 打开密码盘
	PasswordPAD_check_function();					//如果密码盘打开，检测密码  如果密码正确，打开抽屉
	
}


void plugs_function()
{
	int KeyValue;
	KeyValue = digitalRead(plugs);
	if (KeyValue==LOW)
	{
        delay(50);
        if (KeyValue==LOW)
		{
			plugs_flag = 1;
			digitalWrite(LightWall,LOW);				//如果航空接头接入，打开灯墙。
		}

	}
}


void Card_Input_function()
{
	int KeyValue;
	KeyValue = digitalRead(Card_Input);					//如果灯墙打开，判断是否刷卡
	if (KeyValue==LOW&&plugs_flag==1&&Card_Input_flag == 0)
	{
        delay(50);
        if (KeyValue==LOW)
		{
			Card_Input_flag = 1;
			digitalWrite(Boom,LOW);				//如果刷卡，启动电磁炸弹
                        delay (500);
                        digitalWrite(Boom,HIGH);
		}
	}
}

void Boom_function ()
{
	if (Card_Input_flag == 1)					//如果刷卡，等待电磁炸弹
	{
		delay (15000);
		digitalWrite(PasswordPAD,LOW);			//炸弹启动完成，打开密码盘
		PasswordPAD_flag = 1;
	}
}

void PasswordPAD_check_function()
{
	int KeyValue;
	KeyValue = digitalRead(PasswordPAD_check);
	if (KeyValue==LOW&&PasswordPAD_flag==1)				//如果密码盘打开，检测密码
	{
        delay(50);
        if (KeyValue==LOW)
		{
			digitalWrite(locker,LOW);			//如果密码正确，打开门
			locker_flag = 1;					//改变抽屉状态为打开
		}
	}
}

void Door_function()
{
	int KeyValue;
	KeyValue = digitalRead(PasswordPAD_check);
	if (KeyValue==LOW&&PasswordPAD_flag==1)				//如果密码盘打开，检测密码
	{
        delay(50);
        if (KeyValue==LOW)
		{
			digitalWrite(locker,LOW);			//如果密码正确，打开门
			locker_flag = 1;					//改变抽屉状态为打开
		}
	}
}



void DoorOpen_function()					//  如果抽屉打开，按钮卷闸开门
{
	int KeyValue;
	KeyValue = digitalRead(Door_bottom);
	if (KeyValue==LOW&&locker_flag==1)				//如果抽屉打开，检测按键
	{
        delay(50);
        if (KeyValue==LOW)							//消除抖动后如果按键依然按下，打开门
		{
			digitalWrite(DoorOpen,LOW);				
			delay (500);							
			digitalWrite(DoorOpen,HIGH);
		}
	}
}

void DoorClose_function()					//点动卷闸关门
{
	digitalWrite(DoorClose,LOW);
	delay (500);
	digitalWrite(DoorClose,LOW);
}
