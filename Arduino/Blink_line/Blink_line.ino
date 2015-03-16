/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led[3]= {9,10,11};
int i;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for ( i =0; i < 3; i++)
  {
  pinMode(led[i], OUTPUT);  
  }

}

// the loop routine runs over and over again forever:
void loop() {
  while(1)
  {

  digitalWrite(led[0], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led[1], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(led[2], HIGH);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
  digitalWrite(led[0], HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led[1], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(led[2], LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second  
  digitalWrite(led[0], HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led[1], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led[2], HIGH);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
  }
}
