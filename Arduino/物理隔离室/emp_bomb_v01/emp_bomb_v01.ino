// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  int i;
  for (i=2;i<12;i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);  
}

// the loop routine runs over and over again forever:
void loop() {
  int i,j,k;
  while (digitalRead (12)==LOW)
  {

    for (i=10;i>0;i--)
    {
      for (j=2;j<12;j++)
      {
        digitalWrite(j, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(i*15);               // wait for a second
        k=i;
        if ((j+1)>11) 
        {
          k=j+1;
          k=j-10;
          digitalWrite(k, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(i*15);
        }
          digitalWrite(j+1, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(i*15);
        digitalWrite(j, LOW);    // turn the LED off by making the voltage LOW
        delay(i*15);
      }
    }
    for (i=0;i<12;i++)
    {
      for (j=11;j>i;j--)
      {
        delay(100);
        digitalWrite(j, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(100);               // wait for a second
        digitalWrite(j, LOW);    // turn the LED off by making the voltage LOW

      }
      digitalWrite(i, HIGH);    // turn the LED off by making the voltage LOW
      delay(100);
    }
  }
}

//void music (void)
//{
//  digitalWrite (13,LOW);
//}

