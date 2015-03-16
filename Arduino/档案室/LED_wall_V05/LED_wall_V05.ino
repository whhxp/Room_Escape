/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#define CLK 4
#define LE 5 // LAT
#define OE 6
#define SDI 7 // DATA

#define LED_COL 16
int startSignal=13;
//DEFINE PASSWORD 2,4,6,7,1,5
int i, i2;
short Data[4] = {
  0x8142,0x2418,0x1824,0x4281};
short lightOffCode[4]={
  0x0000,0x0000,0x0000,0x0000};
short lightOn[4]={
  0xFFFF,0xFFFF,0xFFFF,0xFFFF};
  
short locked[4] = {0x007e,0x007e,0x5e7e,0x0000};
//0x007e,0x007e,0x5e7e,0x0000
short unlock[4] = {0x00ce,0x9e92,0x9e92,0x0000};
//0x00ce,0x9e92,0x9e92,0x0000
short zero[4]={
  0x027E,
  0x4040,
  0x4040,
  0x7E02};
short one[4]={
  0x020C,
  0x3040,
  0x4030,
  0x0C02};

void movie_unlock();
// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  lightOff();
  delay(1000);
  for (i = 4; i < LED_COL; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(startSignal, INPUT);
  Serial.begin(9600);
  delay(100);
  lightOff();
}

// the loop routine runs over and over again forever:
void loop() {
  #if 0
  int temp=digitalRead(startSignal);
 
  Serial.println(temp);

  if(temp==0){

    while (1) {
      startLight();
      //Below is for password 2
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(zero[i2]);
        delay(500);
      }
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(zero[i2]);
        delay(500);
      }
      delay(2000);
      lightOff();
      //Below is for password 4
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(zero[i2]);
        delay(500);
      }
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(zero[i2]);
        delay(500);
      }
      delay(2000);
      lightOff();
      //below is for password 6
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(zero[i2]);
        delay(500);
      }
      delay(2000);
      lightOff();

      //below is for password 7 
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      delay(2000);
      lightOff();
//below is for password 1
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(zero[i2]);
        delay(500);
      }
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(zero[i2]);
        delay(500);
      }
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      delay(2000);
      lightOff();
//below is for password 5
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(zero[i2]);
        delay(500);
      }
      delay(2000);
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(one[i2]);
        delay(500);
      }
      delay(2000);
      lightOff();

    }
  }
  #endif
  movie_unlock();
  
}

void DataSend(int LedData) 
{
  digitalWrite(CLK, LOW); 
  digitalWrite(LE, LOW);
  digitalWrite(OE, HIGH);
  for (i = 0; i < 8; i++) 
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
  DataLock();
  delay (50);
  // digitalWrite(LE,HIGH);
  //  digitalWrite(OE,LOW);
  //    digitalWrite(LE,HIGH);
  //    digitalWrite(LE,LOW);
  for (i = 0; i < 8; i++) 
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
  DataLock();
  delay (50);

}

void DataLock(void) 
{
  digitalWrite(LE, HIGH);
  digitalWrite(OE, LOW);
}
void lightOff(void){
  for (i2 = 0; i2 < 4; i2++) {
    DataSend(lightOffCode[i2]);
    //delay(500);
  }
  for (i2 = 0; i2 < 4; i2++) {
    DataSend(lightOffCode[i2]);
    //delay(500);
  }
  for (i2 = 0; i2 < 4; i2++) {
    DataSend(lightOffCode[i2]);
    //delay(500);
  }
  delay(1000);

}
void startLight(void){

  for(int j=0;j<50;j++){

    DataSend(0xAA55);
    DataSend(0xAA55);
    delay(100);

  }
}


void movie_unlock()
{
      for (i2 = 0; i2 < 4; i2++) {
        DataSend(locked[i2]);
        delay(2000);
      }
            for (i2 = 0; i2 < 4; i2++) {
        DataSend(unlock[i2]);
        delay(2000);
      }


}








