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
#define DEBUG 1
//set key numbers    as   input pin
const int key[4] = {
  4,5,6,7}; 
int BigButton = 5;

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
const char password[8] = {
  4,4,1,2,2,4,3,3};
char PasswordTemp[8];

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

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(PushPin, OUTPUT); 
  pinMode(DoorOpen, OUTPUT); 
  pinMode(MusicPlay1, OUTPUT); 
  pinMode(MusicPlay2, OUTPUT); 
  pinMode(relay_pin, OUTPUT); 

}

void loop(){
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
  play_voice(1);
  turnoff_lights();
  open_door(); 
}

int keyscan (void){
  int i,j;
  int KeyValue,pushed;
#if 0
  Serial.print("enter key scan \n");
#endif
  for (i=4;i<9;i++)
  {
    j=i-3;
    KeyValue = digitalRead(i);
#if 0
    Serial.print(i);
    Serial.print("<---i\t");
    Serial.print(KeyValue);
    Serial.print("<---key\t");
    Serial.print(j);
    Serial.print("<----j\n");
#endif
    if (KeyValue == HIGH) 
    {
      delay(20);
      KeyValue = digitalRead(i);
      if (KeyValue == HIGH)
      {
        delay(20);
      //  delay(50);
        while (KeyValue != LOW)
        {
          KeyValue = digitalRead(i);
        }
#if DEBUG
        Serial.print("keyscan:  ");
        Serial.println(j);
#endif
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
  //digitalWrite(PushPin, LOW); 
  //delay(10000);
  return 1;
}


unsigned char enter_passwd()
{
  int PassWord_NO,i;
  for (PassWord_NO=0; PassWord_NO<8; PassWord_NO++)
  {
    while (keyscan() == 0)     //if no key push wait
    {
      delay (10);
    }
    if (keyscan() != BigButton)
    {
      PasswordTemp[PassWord_NO]=keyscan();
    }
    else if(keyscan() == BigButton)
    {
      dir_check();
    }
  }
#if DEBUG
  Serial.print("enter passwd\n");
#endif
  return 1;
}
unsigned char dir_check()
{
  int i;
    {
      if (!(strcmp(PasswordTemp,password)))
      {
#if DEBUG
        Serial.print("check passwd ok\n");
#endif
        return 1;
      }
      else
      {
        for (i=0;i<8;i++)
          PasswordTemp[i] = 0;
#if DEBUG
        Serial.print("check failed\n");
#endif
        return 0;
      }
    }
}

unsigned char check_passwd()
{
  if (keyscan()==BigButton)     // if BigButton push      check data   if data wrong clean all data
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
  digitalWrite(relay_pin, LOW);
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
  return 0;
}














