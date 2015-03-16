/*
light1[],light2[]用于接跑马灯，doorControl(13号管脚)接输出给门的信号，
 signalIn(12号管脚)接输入信号，music(11号管脚)接音乐开启信号
 */
int doorControl = 13;
int music=11;
int light1[]={
  2,3,4};
int light2[]={
  5,6,7};
int light3[]={
  8,9,10};
int signalIn=12;
int digitalInData;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(doorControl, OUTPUT);     
  for(int k=0;k<3;k++){
    pinMode(light1[k],OUTPUT);
    pinMode(light2[k],OUTPUT);
    pinMode(light3[k],OUTPUT);
  }
  pinMode(signalIn,INPUT);
  pinMode(music,OUTPUT);
  Serial.begin(9600);
}
void writequeue1()
{
  digitalWrite(light1[0], HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(light1[1], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light1[2], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light2[0], HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(light2[1], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light2[2], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light3[0], HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(light3[1], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light3[2], LOW);    // turn the LED off by making the voltage LOW
}
void writequeue2()
{
  digitalWrite(light1[0], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(light1[1], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(light1[2], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light2[0], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(light2[1], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(light2[2], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light3[0], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(light3[1], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(light3[2], LOW);    // turn the LED off by making the voltage LOW
}
void writequeue3()
{
  digitalWrite(light1[0], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(light1[1], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light1[2], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(light2[0], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(light2[1], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light2[2], HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(light3[0], LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(light3[1], LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(light3[2], HIGH);    // turn the LED off by making the voltage LOW
}
// the loop routine runs over and over again forever:
void loop() {

  digitalWrite(doorControl,LOW);
  digitalWrite(music, LOW);

  while(digitalRead(signalIn)==HIGH){
    for(int i=0;i<16;i++){//Accelerated motion
      writequeue1();
      delay(1000*(sqrt(6*i-2)-sqrt(6*i-6)));               // wait for a second
      writequeue2();
      delay(1000*(sqrt(6*i)-sqrt(6*i-2)));     
      writequeue3();
      delay(1000*(sqrt(6*i+4)-sqrt(6*i)));     
    }
    for(int i=0;i<30;i++){//Uniform motion
      writequeue1();
      delay(212);               // wait for a second
      writequeue2();
      delay(212);     
      writequeue3();
      delay(212);     
    }
    for(int i=16;i>=0;i--){//Deceleration
      writequeue1();
      delay(1000*(sqrt(6*i+4)-sqrt(6*i)));
      writequeue2();
      delay(1000*(sqrt(6*i)-sqrt(6*i-2)));     
      writequeue3();
      delay(1000*(sqrt(6*i-2)-sqrt(6*i-6)));               // wait for a second     
    }
    Serial.println("IM AAAAAAAAAAAAAAAAA");
    digitalWrite(music, HIGH);
    delay(2000);

    digitalWrite(doorControl, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(4000);
    digitalWrite(music, LOW);

    delay(15000);               // wait for a second
  }
  Serial.println("IM BBBBBBB");
}








