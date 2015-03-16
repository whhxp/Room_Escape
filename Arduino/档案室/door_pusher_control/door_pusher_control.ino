/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int in_uv_start = 2;     // the number of the pushbutton pin
const int pusher_pin =  4;      // the number of the LED pin
const int out_x_start= 5;
const int in_passwd_ok= A0;
// variables will change:
int buttonState = 1000;         // variable for reading the pushbutton status
#define S(n) Serial.print(n)
#define Sln(nn) Serial.println(nn)
int uv_start_flag = 0;
int pusher_flag = 0;
int in_passwd_flag = 0;
int x_start_flag = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(pusher_pin, OUTPUT);
  pinMode(out_x_start, OUTPUT);
  digitalWrite(pusher_pin,HIGH);
  digitalWrite(out_x_start,HIGH);
  //pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(in_uv_start, INPUT);     
}

void loop(){
  if(digitalRead(in_uv_start) == LOW)
  {
    uv_start_flag = 1;
  }
  if (uv_start_flag==1)
  {
    buttonState = analogRead(in_passwd_ok);
    Serial.println(buttonState);
  }
  if (buttonState < 10) 
  {     
    in_passwd_flag = 1;
    x_start_flag = 1;
  }
  if (in_passwd_flag==1)
  {
    pusher_flag=1;
  }  
  if(pusher_flag == 1)
  {
    digitalWrite(pusher_pin, LOW);
  }
  else
  {
    digitalWrite(pusher_pin, HIGH);  
  }

  if(x_start_flag ==1)
  { 

    digitalWrite(out_x_start, LOW); 
  }
  else
  {
    digitalWrite(out_x_start, HIGH);
  }
  S("uv_start_flag  ");
  Sln(uv_start_flag);
  S("pusher_flag ");
  Sln(pusher_flag);
  S("in_passwd_flag ");
  Sln(in_passwd_flag);
  S("x_start_flag ");
  Sln(x_start_flag );

}












