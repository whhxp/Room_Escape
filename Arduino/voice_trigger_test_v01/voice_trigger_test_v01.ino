
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




#include "SoftwareSerial1.h"
#define pin_rx 10
#define pin_tx 11
SoftwareSerial mySerial(pin_rx, pin_tx); // RX, TX
#include "cmd.h"
#define DEBUG 0

#define LOOP_PLAY 0
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonPin = 2;     // the number of the pushbutton pin
int connButton;
int num;
int in_signal = 0;
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


void setup()
{
  delay(5000);
  mySerial.begin(9600);
}


void loop()
{
  send_cmd(adjVol30);
  send_cmd(startcycle);
  while (1)
  {
  }

}


int is_change(int now, int pre)
{
  return 	( now == pre) ? 0 : 1;
}




