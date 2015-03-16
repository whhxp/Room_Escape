/*
控制时间达到要求的秒数，按键按下时显示蓝光，正确显示绿光，并常亮，错误显示红光

 正确后在rightSignal(13号管脚)输出高电平信号
 */
#define COUNTER 1
#define DEBUG 0
const int buttonPin = A0;     // the number of the pushbutton pin
const int greenLEDPin = 9;    // LED connected to digital pin 9
const int redLEDPin = 10;     // LED connected to digital pin 10
const int blueLEDPin = 11;    // LED connected to digital pin 11
const int rightSignal=13;

int buttonState = 0;         // variable for reading the pushbutton status
int setTime=9000;//设定时间
int misRange=800;//误差范围;
int timeRecorder=0;
int key_value=0;
void setup()
{
	Serial.begin(9600);  //串口波特率
	// initialize the LED pin as an output:
	pinMode(greenLEDPin,OUTPUT);
	pinMode(redLEDPin,OUTPUT);
	pinMode(blueLEDPin,OUTPUT);
	// initialize the pushbutton pin as an input:
	//pinMode(buttonPin, INPUT);
	pinMode(rightSignal, OUTPUT);

}

void loop()
{
	// read the state of the pushbutton value:


	// check if the pushbutton is pressed.
	// if it is, the buttonState is HIGH:

	digitalWrite(rightSignal,LOW);
	analogWrite(redLEDPin, 255);
	analogWrite(greenLEDPin, 255);
	analogWrite(blueLEDPin, 255);

	timeRecorder=0;
	key_value=analogRead(buttonPin);

	Serial.println(key_value);
	
	if( key_value < 300)
	{
		delay(10);
		key_value=analogRead(buttonPin);
		Serial.println(key_value);
		while(key_value < 300)
		{
			key_value=analogRead(buttonPin);
			Serial.println(key_value);
			analogWrite(redLEDPin, 0);
			analogWrite(greenLEDPin, 0);
			analogWrite(blueLEDPin, 255);
			delay(10);
			timeRecorder+=10;
		}
		if((timeRecorder>=(setTime-misRange))&&(timeRecorder<=(setTime+misRange)))
		{
			digitalWrite(rightSignal, HIGH);
			rightLight();
			while(1);
		}
		else
		{
			wrongLight();

		}
	}


}

void blue_blink()
{
	for(int i=0; i<3; i++)
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
void wrongLight()
{
	for(int i=0; i<3; i++)
	{
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
void rightLight()
{
	for(int i=0; i<3; i++)
	{
		analogWrite(redLEDPin, 0);
		analogWrite(greenLEDPin, 255);
		analogWrite(blueLEDPin, 0);
		delay(500);
		analogWrite(redLEDPin, 0);
		analogWrite(greenLEDPin, 0);
		analogWrite(blueLEDPin, 0);
		delay(500);
	}
	while(1)
	{
		analogWrite(greenLEDPin, 255);
	}
}














