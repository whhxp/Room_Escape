/*
触手板代码
 drawerPw读到高电平时启动，并输出servo高电平，给到舵机控制板
 当touchhand都读到高电平的时候，输出stepper低电平信号
 */
int touchhand[] = {
  8,9,2,3,4,4,6,6};
int drawerPw=10;
int servo=12;
int stepper = 13;

int i;
void setup()
{

  for(i=0; i<8; i++)
  {
    pinMode(touchhand[i],INPUT);
  }
  pinMode(drawerPw,INPUT);
  pinMode(servo,OUTPUT);
  pinMode(stepper,OUTPUT);
  digitalWrite(servo,LOW);
  Serial.begin(9600);

}

void loop()
{
  Serial.println("START:");
  int add=0;
  digitalWrite(servo,LOW);
  digitalWrite(stepper,HIGH);

  int temp=checkPW();

  Serial.println(digitalRead(drawerPw));
  if(temp==1){
    while(1){
      add=0;
      digitalWrite(servo,HIGH);
      for(i=0;i<8;i++)
      {
        if(digitalRead(touchhand[i]) == HIGH)
        {
          add++;
          Serial.print("touchhand:");
          Serial.println(i+1);
        }
      }

      if(add>=4)
      {
        Serial.println("GOOD LUCK!");
        digitalWrite(stepper,LOW);
        while(1){
          Serial.println("IM WHILING");
        }
      }
    }
  }
}



int checkPW(){

  int buttonState = digitalRead(drawerPw);
  int total=0;
  // print out the state of the button:
  for(int s=0;s<100;s++){
    Serial.println(buttonState);
    buttonState = digitalRead(drawerPw);
    total+=buttonState;
    Serial.print("total=");
    Serial.println(total);
    delay(10);        // delay in between reads for stability
  }
  if(total>10){
    return 0;
  }
  else{
    return 1;
  }
}

