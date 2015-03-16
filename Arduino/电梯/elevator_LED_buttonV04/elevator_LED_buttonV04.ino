/*
该代码需要analogKey板子3块，LED Control长板1块
 
 
 button_hold[0]的analogRead的值从大到小分别对应按键1-5
 button_hold[1]的analogRead的值从大到小分别对应按键67890,此处0为antixcape键
 button_hold[2]的analogRead的值从大到小分别对应按键11-15
 正确密码是01278,此处0为antixcape键
 
 arduino mega 2560
 
 2015/03/11
 加入了声音引脚
 
 
 
 */

// 首先定义 管脚 22--39作为按键输入管脚
// 对应电梯按钮为    buttom 的 1--9 分别对应输入的1到9键 ，0键对应  antixcape  11--15键 分别是其他区间的按键   其中0--9 必须按照正确次序连接

int buttom [17] = {
  22,23,24,25,                    //antixcape 1 2 3 
  26,27,28,29,					//4 5 6 7  
  30,31,32,33,					//8 9 * * 
  34,35,36,37,					//* * * *
  38};							//*

int light_door_open = 13;			//定义开门按钮为13脚
int light_door_close = 12;			//定义关门按钮为12脚
int light_door_open_to_lightwall = 11;                   //

int voice_out [4] = {
  8,9,10,11};	//定义声音输出为 8,9,10,11 管脚 分别输出4中音效

int led_out [9]={
  39,40,41,42,43,44,19,20,21};



// 定义LED 控制板的信号线
#define CLK 4
#define LE 5 						// LAT
#define OE 6
#define SDI 7 						// DATA

//output sound effect

#define elevator_working_pin   8
#define button_press_sound       9

int Password_open[5];    //按键对应的密码位


void setup()
{
  int i;
  Serial.begin(9600);
  for (i = 0; i < 17; i++)                  //对 按键管脚进行初始化   初始化为输入端口
  {
    pinMode(buttom[i], INPUT);
  }
  for (i = 0; i < 9; i++)                  //对 LED 管脚进行初始化    初始化成为输出端口
  {
    pinMode(led_out[i], OUTPUT);
  }   


  pinMode(CLK,OUTPUT); 			//对LED控制电路板输出部分进行初始化    初始化成为输出端口
  pinMode(LE,OUTPUT);
  pinMode(OE,OUTPUT);
  pinMode(SDI,OUTPUT);

  pinMode(elevator_working_pin,OUTPUT);
  pinMode(button_press_sound,OUTPUT);
  digitalWrite(button_press_sound,HIGH);
  digitalWrite(elevator_working_pin,HIGH);

  pinMode(light_door_open,OUTPUT);				//对开门控制进行初始化，使得一开始时按键处于非按下状态
  pinMode(light_door_close,OUTPUT);
  pinMode(light_door_open_to_lightwall,OUTPUT);

  pinMode(light_door_open_to_lightwall,LOW);
  digitalWrite(light_door_open,HIGH);
  digitalWrite(light_door_close,HIGH);

}

void loop(void)
{
  //  int key=0;
  //  key=buttonRead(buttom);
  //  Serial.println(key);
  //
  //  
  password_input();
  password_check_and_opendoor();

  //light debug
  //        water_lights();


}

void elevator_working_sound()
{
  digitalWrite(elevator_working_pin,LOW);
  delay(20);
  digitalWrite(elevator_working_pin,HIGH);
}

void button_sound()
{
  digitalWrite(button_press_sound,LOW);
    delay(20);
  digitalWrite(button_press_sound,HIGH);
}

void password_input (void)
{
  int  k,key_now;             						// 定义循环变量

  for(k=0;k<5;k++)
  {
    while(1){
      key_now=buttonRead(buttom);
      Serial.println("key_now=");
      Serial.println(key_now);
      if(key_now!=99){
        Password_open[k]=key_now;
        Serial.println(key_now);
        Serial.print("i=");
        Serial.println(k);
        break;
      }
    }
  }
}


int password_check_and_opendoor (void)
{
  if(Password_open[0]==0 && Password_open[1]==1 && Password_open[2]==2 && Password_open[3]==7 && Password_open[4]==8) 
  {
    Serial.println("good luck:doorOpen!");
    elevator_working_sound();
    water_lights ();
    digitalWrite(light_door_open,LOW);
    digitalWrite(light_door_open_to_lightwall,HIGH);
    delay(2000);
    digitalWrite(light_door_open,HIGH);
    digitalWrite(light_door_open_to_lightwall,LOW);
  }
  else if (Password_open[0]==2 && Password_open[1]==7 && 									//password_check
  Password_open[2]==2 && Password_open[3]==4 && Password_open[4]==0)
  {
    Serial.println("good luck:doorclose!");
    digitalWrite(light_door_close,LOW);
    delay(500);
    digitalWrite(light_door_close,HIGH);
  }
  else
  {
    password_Wrong();
    Serial.println("i'm sorry,please again");
    delay (500);
  }


}


int buttonRead(int *key)
{
  int i;
  int pre_key,now_key,length;
  /*如果没有感应到按键触发，则返回值99*/
  for (i=0;i<17;i++)
  {
    if (digitalRead(key[i]) == LOW) 
    {
      Serial.print("key=");
      Serial.println(i);
      delay(50);
      now_key = digitalRead(key[i]);
      if (digitalRead(key[i]) == LOW)
      {
        delay(50);
        while (digitalRead(key[i]) != HIGH)
        {
          //Serial.println ("test");
          
            LedLighten(i);

        }
      }
      return i;
    }
  }
  return 99;
}

void LedLighten (int Number)
{
  Number = 15-Number; 
  Number -= 1; 
  DataSend(0x4000>>Number);
  DataLock();
}

void DataSend(int LedData) 
{
  int i;
  digitalWrite(CLK, LOW); 
  digitalWrite(LE, LOW);
  digitalWrite(OE, HIGH);
  for (i = 0; i < 16; i++) 
  {
    if (LedData & 0x8000) 
    {
      digitalWrite(SDI, HIGH);
      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
    } 
    else 
    {
      digitalWrite(SDI, LOW);
      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
    }
    LedData <<= 1;
  }
  // digitalWrite(LE,HIGH);
  //  digitalWrite(OE,LOW);
  //    digitalWrite(LE,HIGH);
  //    digitalWrite(LE,LOW);
  delay(1);
}

void DataLock (void) 
{
  digitalWrite(LE, HIGH);
  digitalWrite(OE, LOW);
}

void password_Wrong(void)
{
  int l;
  for(int l=15;l>=0;l--){
    LedLighten(l);
    delay(100);
  }
  LedLighten(16);
}

void water_lights (void)
{
  int i;
/*
  for (i=1000;i>100;i-=70)
  {
    water_lights1 (i);
  }
  for (i=0;i<30;i++)
  {
    water_lights1 (100);
  }
  for (i=100;i<1000;i+=70)
  {
    water_lights1 (i);
  }*/
  for(int i=1;i<10;i++){//Accelerated motion 7sec
    writequeue1();
    delay(1000*(sqrt(6*i-2)-sqrt(6*i-6)));               // wait for a second
    writequeue2();
    delay(1000*(sqrt(6*i)-sqrt(6*i-2)));     
    writequeue3();
    delay(1000*(sqrt(6*i+4)-sqrt(6*i)));     
  }
  for(int i=0;i<43;i++){//Uniform motion 26sec
    writequeue1();
    delay(212);               // wait for a second
    writequeue2();
    delay(212);     
    writequeue3();
    delay(212);     
  }
  for(int i=7;i>=1;i--){//Deceleration  5sec
    writequeue1();
    delay(1000*(sqrt(6*i+4)-sqrt(6*i)));
    writequeue2();
    delay(1000*(sqrt(6*i)-sqrt(6*i-2)));     
    writequeue3();
    delay(1000*(sqrt(6*i-2)-sqrt(6*i-6)));               // wait for a second     
  }

}

void writequeue1()
{
  digitalWrite(led_out[0], HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_out[1], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[2], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[3], HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_out[4], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[5], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[6], HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_out[7], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[8], LOW);    // turn the LED off by making the voltage LOW
}
void writequeue2()
{
  digitalWrite(led_out[0], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_out[1], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[2], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[3], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_out[4], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[5], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[6], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_out[7], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[8], LOW);    // turn the LED off by making the voltage LOW
}
void writequeue3()
{
  digitalWrite(led_out[0], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_out[1], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[2], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[3], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_out[4], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[5], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[6], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_out[7], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_out[8], HIGH);    // turn the LED off by making the voltage LOW
}

void water_lights1 (int led_time)
{
  digitalWrite(led_out[2],HIGH);
  digitalWrite(led_out[5],HIGH);
  digitalWrite(led_out[8],HIGH);
  delay (led_time);
  digitalWrite(led_out[2],LOW);
  digitalWrite(led_out[5],LOW);
  digitalWrite(led_out[8],LOW);

  digitalWrite(led_out[1],HIGH);
  digitalWrite(led_out[4],HIGH);
  digitalWrite(led_out[7],HIGH);
  delay (led_time);
  digitalWrite(led_out[1],LOW);
  digitalWrite(led_out[4],LOW);
  digitalWrite(led_out[7],LOW);

  digitalWrite(led_out[0],HIGH);
  digitalWrite(led_out[3],HIGH);
  digitalWrite(led_out[6],HIGH);
  delay (led_time);
  digitalWrite(led_out[0],LOW);
  digitalWrite(led_out[3],LOW);
  digitalWrite(led_out[6],LOW);
}

