/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */
int i;
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  for ( i = 1; i<= 16; i ++)
  { 
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000*(sqrt(6*i-2)-sqrt(6*i-6)));               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(1000*(sqrt(6*i)-sqrt(6*i-2)));               // wait for a second
  }
    for ( i = 0 ; i< 50; i ++)
  { 
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(242);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(121);               // wait for a second
  }
  for ( i = 20 ; i>0; i --)
  { 
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000*(sqrt(6*i-2)-sqrt(6*i-6)));             // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(1000*(sqrt(6*i)-sqrt(6*i-2)));               // wait for a second
  }
}

