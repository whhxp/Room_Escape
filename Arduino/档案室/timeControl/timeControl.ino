/*
控制时间达到要求的秒数，按键按下时显示蓝光，正确显示绿光，并常亮，错误显示红光
 
 正确后在rightSignal(13号管脚)输出高电平信号
 */
#define COUNTER 1
#define DEBUG 0
const int buttonPin = 2;     // the number of the pushbutton pin
const int greenLEDPin = 9;    // LED connected to digital pin 9
const int redLEDPin = 10;     // LED connected to digital pin 10
const int blueLEDPin = 11;    // LED connected to digital pin 11
const int rightSignal=13;

int buttonState = 0;         // variable for reading the pushbutton status
int setTime=9000;//设定时间
int misRange=500;//误差范围;
int timeRecorder=0;
void setup() {
#if DEBUG
  Serial.begin(9600);  //串口波特率
#endif
  // initialize the LED pin as an output:
  pinMode(greenLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);
  pinMode(blueLEDPin,OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  pinMode(rightSignal, OUTPUT);

}

void loop()
{
#if 0
  // read the state of the pushbutton value:


  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:

  digitalWrite(rightSignal,LOW);
  analogWrite(redLEDPin, 255);
  analogWrite(greenLEDPin, 255);
  analogWrite(blueLEDPin, 255);

  timeRecorder=0;
  if(!digitalRead(buttonPin)==HIGH){  
    while(!digitalRead(buttonPin)==HIGH){ 
      analogWrite(redLEDPin, 0);
      analogWrite(greenLEDPin, 0);
      analogWrite(blueLEDPin, 255);
      delay(10);
      timeRecorder+=10;
    }
    if((timeRecorder>=(setTime-misRange))&&(timeRecorder<=(setTime+misRange))){
      digitalWrite(rightSignal, HIGH);
      rightLight();
    }
    else{
      wrongLight();

    }
  }
#endif


#if COUNTER
  float time1,time2;  //定义变量为浮点数
  digitalWrite(rightSignal,LOW);
  analogWrite(redLEDPin, 255);
  analogWrite(greenLEDPin, 255);
  analogWrite(blueLEDPin, 255);
  timeRecorder=0;
  if(digitalRead(buttonPin)==LOW)
  {  
    delay(20);
    if(digitalRead(buttonPin)==LOW)
    {
      time1= pulseIn(2, LOW,60000000)/1000;
    }
  }
  if (abs(time1-setTime)<misRange)
  {
    digitalWrite(rightSignal, HIGH);
    rightLight();
  }
  else
  {
    wrongLight();
  }
#if DEBUG
  if (time1 > 200)
  {
    Serial.print(time1); //通过串口输出time1变量
    Serial.println("ms  ");
#endif
  }
#endif
}

void blue_blink()
{
  for(int i=0;i<3;i++)
  {
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 255);
    delay(500);
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 0);
    delay(500);
  }
}
void wrongLight(){
  for(int i=0;i<3;i++){
    analogWrite(redLEDPin, 255);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 0);
    delay(500);
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 0);
    delay(500);
  }
}
void rightLight(){
  for(int i=0;i<3;i++){
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 255);
    analogWrite(blueLEDPin, 0);
    delay(500);
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 0);
    delay(500);
  }
  while(1){
    analogWrite(greenLEDPin, 255);
  }
}













