/*

 */
#define DEBUG 1
#define PUSHER_DEBUG 0
#define time1   28240   //from middle level up to top,28.24sec
#define time2   18500    //down to middle level,18.5sec
#define time3   24810    //from bottom to middle, 24.81sec

#define S(n) Serial.print(n)
#define Sln(nn) Serial.println(nn)
#define enter() S("enter function\t");Sln(__FUNCTION__)

//input
//const int mapLight=4;
//const int oneButtonControl2LED=5;
//const int colorMixing=6;
//const int timeControl=7;
const int in_signal=4;
const int touchhand[] = {
  A0,A1,A2,A3};
const int reset=5;


//output
const int inner_light_pin=6;
const int pusher_up_pin=7;
const int pusher_down_pin=8;
const int output_pin=13;
const int pass_key_power=12;

int check[]={
  0,0,0,0};
int rightNum=0;



int wait_signal();
int liter_pusher(int time);
int wait_press_palm();
int lights_on();
int output_signal();
int pusher_up();
int pusher_down();
int pusher_stop();

void setup(){
  //start serial connection
  Serial.begin(9600);
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(output_pin,OUTPUT);
  pinMode(inner_light_pin,OUTPUT);
  pinMode(pusher_up_pin,OUTPUT);
  pinMode(pusher_down_pin,OUTPUT);
  pinMode(pass_key_power,OUTPUT);
  digitalWrite(pass_key_power,HIGH);
  digitalWrite(pusher_up_pin,HIGH);
  digitalWrite(pusher_down_pin,LOW);

}







void loop(){

  init_output();
  while(1)
  {
    if (wait_signal())
    {
      liter_pusher(time1);
      light_on();
      if(wait_press_palm()==1)
      {
        light_blink();
        liter_pusher(time2);
        digitalWrite(pass_key_power,LOW);
        output_signal();
        while(1); 
      }
    }
  }
#if PUSHER_DEBUG
  pusher_up();
  pusher_stop();
  pusher_up();
  pusher_stop();
  pusher_down();
  pusher_stop();
#endif
}


/////////////////////////////////////////////////////////////
//pusher function
//
//
//
//
//

int pusher_down()
{
  enter();
  digitalWrite(pusher_up_pin,HIGH);
  digitalWrite(pusher_down_pin,HIGH);
#if PUSHER_DEBUG
  delay(1000);
#endif
}


int pusher_up()
{
  enter();
  digitalWrite(pusher_up_pin,LOW);
  digitalWrite(pusher_down_pin,LOW);
#if PUSHER_DEBUG
  delay(1000);
#endif
}


int pusher_stop()
{
  enter();
  digitalWrite(pusher_up_pin,HIGH);
  digitalWrite(pusher_down_pin,LOW);
#if PUSHER_DEBUG
  delay(1000);
#endif
}

void init_output()
{
  enter();
  for(int k=0;k<4;k++)
  {
    check[k]=0;
  }
  pusher_stop();
  //delay(10000);
  digitalWrite(inner_light_pin,HIGH);
  digitalWrite(output_pin,HIGH);
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
  enter();

  while(1)
  {
    if(digitalRead(in_signal)==LOW)
    {
      delay(20);
      if(digitalRead(in_signal)==LOW)
        return 1;
    }
  }
  return 0;
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
  enter();
  pusher_up();
  delay(time);
  pusher_stop();
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
  enter();
  S("wait press palm\n");
  while(1)
  {
    int add=0;
    for(int i=0;i<4;i++)
    {
      if(analogRead(touchhand[i]) < 400)
      {
        add++;
        S("touchhand:");
        Sln(i+1);
      }
    }
    if(add==4)
    {
      light_blink();
      Serial.println("GOOD LUCK!");
      return 1;
    }
  }
}


int light_on()
{
  enter();
  S("light on\n");
  digitalWrite(inner_light_pin,LOW);
}

int light_blink()
{
  enter();
  digitalWrite(inner_light_pin,LOW);
  delay(1000);
  digitalWrite(inner_light_pin,HIGH);
  delay(1000);
  digitalWrite(inner_light_pin,LOW);
  delay(1000);
  digitalWrite(inner_light_pin,HIGH);
  delay(1000);
}

int output_signal()
{
  enter();
  digitalWrite(output_pin,LOW);
  //while(1);
}





























