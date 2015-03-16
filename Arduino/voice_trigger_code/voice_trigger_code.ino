/*
this document is written in English.
 
 Voice trigger board is a green PCB which is connected with a small extensive
 board. The voice process modual is on the back of the small board and TF card
 is used to store voices of which extension name is mp3.
 
 button state
 HIGH = not connected
 LOW  = connected
 
 
 */
#include "cmd.h"
#include <string.h>
#define DEBUG 0
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonPin = 2;     // the number of the pushbutton pin
int connButton=0;
int num;
unsigned char dh,dl;

unsigned char set_track(unsigned char *cmd, short n)
{
  cmd[4] = n;
  check(cmd);
  return 0;
}
void send_cmd(unsigned char *cmd)
{
  check(cmd);
  Serial.write(start, 2);
  Serial.write(cmd, 7);
  Serial.write(ending, 1);
  delay(50);
}
char check(unsigned char *cmd)
{
  char sum,i;
  sum= 0xff;
  for (i = 0; i < 5; i++)
  {
    sum+= cmd[i];
  }
  sum=~sum;
  sum++;
  cmd[5]=sum>>8;
  cmd[6]=sum&0xff;
  return sum;
}
void setup() {
  delay(2000); //wait for initialzation after power on
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT); 

}


void loop() {
  for ( buttonPin = 2; buttonPin <= 11; buttonPin++ )
  {
    buttonState=digitalRead(buttonPin);
    if (  buttonState == LOW ) //the button connected
    {
      connButton = buttonPin;
    }
  }
  delay(5000);
#if 0
  //Serial.println("Initialization is done" );
  send_cmd(adjVol);
  if (~set_track(setTrack,1))
  {
  }
#endif
#if 1
  send_cmd(setTrack);
    delay(500000);
    send_cmd(stopTrack);
    #endif
#if DEBUG
  Serial.print(" Pin = " );                       
  Serial.print(connButton);
  Serial.print("\tstate = " );
  Serial.println(buttonState);
#endif  
  // wait 500 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(500);
}

