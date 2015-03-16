/*
中转板代码，正确后输出draw1,draw2,lightwall信号
 backupRelay(8号管脚)接遥控应急方案
 lightwall接灯墙信号，正确时输出低电平
 draw1,draw2接抽屉，正确时输出高电平
 */
#define time1   30
#define time2   20


//input
const int mapLight=4;
const int oneButtonControl2LED=5;
const int colorMixing=6;
const int timeControl=7;
const int touchhand[] = {
  A0,A1,A2,A3};



//output
const int inner_light_pin=6;
const int pusher_pin=7;
const int output_pin=13;


int check[]={
  0,0,0,0};
int rightNum=0;



int wait_signal();
int liter_pusher(int time);
int wait_press_palm();
int lights_on();
int output_signal();

void setup(){
  //start serial connection
  Serial.begin(9600);
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(output_pin,OUTPUT);
  pinMode(inner_light_pin,OUTPUT);
  pinMode(pusher_pin,OUTPUT);

}







void loop(){
#if 0
  digitalWrite(drawer1,LOW);
  digitalWrite(drawer2,LOW);
  digitalWrite(lightWall,HIGH);
  //  delay(5000);
  for(int k=0;k<4;k++){
    check[k]=0;
  }
  Serial.println(digitalRead(2));
  Serial.println(digitalRead(3));
  Serial.println(digitalRead(4));
  Serial.println(digitalRead(5));
  Serial.println("End");
  check[0]=digitalRead(2);
  check[1]=digitalRead(3);
  check[2]=digitalRead(4);
  check[3]=digitalRead(5);


  if(check[0]==1 && check[1]==1  && check[2]==1 && check[3]==1){
    checkTotal=1;
  }
  else if(backupStatus==1){
    checkTotal=1;
  }
  else{
    checkTotal=0;
  }
  Serial.println(backupStatus);
  Serial.print("checkTotal");
  Serial.println(checkTotal);
  if(checkTotal==1){
    Serial.println("IM HEREHERE");

    while(1){
      Serial.println("IM LOOPING");
      digitalWrite(drawer1,HIGH);
      digitalWrite(drawer2,HIGH);
      digitalWrite(lightWall,LOW);
    }
  }

#endif
  for(int k=0;k<4;k++)
  {
    check[k]=0;
  }
  if (wait_signal())
  {
    liter_pusher(time1);
    lights_on();
    if(wait_press_palm())
    {
      liter_pusher(time2);
      output_signal();
    }

  }
}

/*
function:waits for signals and returns the result of the judgement
 name:wait_signal
 para:none
 return value:
 1:there are signals
 0:no signal
 */

int wait_signal()
{
  int checkTotal=0;
  Serial.println(digitalRead(2));
  Serial.println(digitalRead(3));
  Serial.println(digitalRead(4));
  Serial.println(digitalRead(5));
  Serial.println("End");
  check[0]=digitalRead(2);
  check[1]=digitalRead(3);
  check[2]=digitalRead(4);
  check[3]=digitalRead(5);
  if(check[0]==1 && check[1]==1  && check[2]==1 && check[3]==1){
    checkTotal=1;
  }
  else{
    checkTotal=0;
  }
  Serial.print("checkTotal");
  Serial.println(checkTotal);
  return checkTotal;
}

/*
function:push the box up according to the time given
 name:liter pusher
 para:time in millisec
 return value:
 1:error 
 0:done
 */
int liter_pusher(int time)
{
  //int pusher_pin=7;
  digitalWrite(pusher_pin,LOW);//open the relay
  delay(time);
  digitalWrite(pusher_pin,HIGH);//open the relay
}

/*
function:read the signal from palm PCB
 name:wait_press_palm
 para:none
 return value:
 1:there are signals
 0:no signal
 */
int wait_press_palm()
{
  while(1)
  {
    int add=0;
    for(int i=0;i<4;i++)
    {
      if(digitalRead(touchhand[i]) == HIGH)
      {
        add++;
        Serial.print("touchhand:");
        Serial.println(i+1);
      }
    }
    if(add==4)
    {
      Serial.println("GOOD LUCK!");
      return 1;
    }
  }
}


int lights_on()
{
  digitalWrite(inner_light_pin,HIGH);
}
int output_signal()
{
  digitalWrite(output_pin,HIGH);
}














