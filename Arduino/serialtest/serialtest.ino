
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
}

void loop() // run over and over
{
  delay(1000);
  while(1)
  {
    Serial.write(Serial.read());
  }
}

