
/*
this document is written in English.
 
 Voice trigger board is a green PCB which is connected with a small extensive
 board. The voice process modual is on the back of the small board and TF card
 is used to store voices of which extension name is mp3.
 
 This version has some features:No return value processing;
 
 
 button state
 HIGH = not connected
 LOW  = connected
 
 
 by whh
 2015/2/6
 */




#include "SoftwareSerial.h"
SoftwareSerial mySerial(10, 11); // RX, TX
#include "cmd.h"
#define DEBUG 0
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonPin = 2;     // the number of the pushbutton pin
int connButton;
int num;

unsigned char set_track(unsigned char *cmd, unsigned char n)
{
  cmd[4] = n;
  send_cmd(cmd);
  return 0;
}

unsigned char adj_vol(unsigned char *cmd, unsigned char n)
{
  cmd[3] = 0x01;
  cmd[4] = n;
  send_cmd(cmd);
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
  int sum,i;
  sum= 0xff;
  for (i = 0; i < 5; i++)
  {
    sum+= cmd[i];
  }
  sum=~sum+1;
  cmd[5]=sum>>8;
  cmd[6]=sum&0xff;
  return sum;
}
void setup() {
  delay(2000); //wait for initialzation after power on
  // initialize serial communications at 9600 bps:
  //Serial.begin(9600);


  //Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  pinMode(buttonPin, INPUT); 

}


void loop() {
  /*for ( buttonPin = 2; buttonPin <= 11; buttonPin++ )
   {
   buttonState=digitalRead(buttonPin);
   if (  buttonState == LOW ) //the button connected
   {
   connButton = buttonPin;
   }
   }*/
  delay(5000);
  /*
  send_cmd(adjVol15);
   delay(1000);
   //Serial.println("Initialization is done" );
   send_cmd(setTrack1);
   delay(5000);  
   send_cmd(setTrack2);
   delay(5000);
   send_cmd(adjVol15);
   delay(1000);
   send_cmd(setTrack3);
   delay(5000);
   send_cmd(stopTrack);*/



  send_cmd(adjVol15);
  delay(1000);
  send_cmd(startcycle);
  //delay(5000);
  digitalWrite(11,LOW);
  delay(5000);
  mySerial.setTX( 11);
  send_cmd(setTrack3);
  digitalWrite(11,LOW);
  delay(5000);
  mySerial.setTX(11);
  send_cmd(startcycle);
  digitalWrite(11,LOW);
  //send_cmd(startcycle);  
  while(1);
}






