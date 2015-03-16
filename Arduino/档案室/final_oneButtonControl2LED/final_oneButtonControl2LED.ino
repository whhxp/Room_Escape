/*
一键控制2-3个灯改变状态，该代码需要两个analogKey板子
 正确后在rightSignal(13号管脚)输出高电平信号
 密码正确是65432164
 */
int button_hold[] ={
  A0,A1,A2,A3,A4,A5};
int light[]={
  2,3,4,5,6,7,8,9,10};//接线位置

int rightSignal=13;
int led[] = {
  0,0,0,0,0,0,0,0,0};//灯的状态
int green_pin=11;//g,r,b respectively

int i;    //按键编号
int w;    //led编号
int y;    //判断编号
int ifChange;
int total=0;
int trytime=0;
//passwd:65432164
void setup()
{
  Serial.begin(9600);


  for(int i=0;i<9;i++)
  {
    pinMode(light[i],OUTPUT);
  }
  pinMode(rightSignal,OUTPUT);
}

void loop()
{
  total=0;
  digitalWrite(rightSignal,LOW);
  int temp=buttonRead();

  if(temp==1){
    trytime++;
    Serial.println(temp);
    lightChange(1);
    lightChange(7);
  }
  else if(temp==2){
    trytime++;
    Serial.println(temp);
    lightChange(4);
    lightChange(6);
    lightChange(8);
  }
  else if(temp==3){
    trytime++;
    Serial.println(temp);
    lightChange(2);
    lightChange(7);
    lightChange(9);
  }
  else if(temp==4){
    trytime++;
    Serial.println(temp);
    lightChange(1);
    lightChange(3);
    lightChange(6);
  }
  else if(temp==5){
    trytime++;
    Serial.println(temp);
    lightChange(3);
    lightChange(5);
    lightChange(7);
  }
  else if(temp==6){
    trytime++;
    Serial.println(temp);
    lightChange(2);
    lightChange(4);
    lightChange(9);
  }
  for(int k=0;k<9;k++){

    total+=led[k];   
  }
  if(total==9){
    digitalWrite(rightSignal, HIGH);
    digitalWrite(green_pin, HIGH);//turn on the green led light
    while(1){
    }
  }
  if(trytime>=30){
    for(int l=0;l<9;l++){
      digitalWrite(light[l],LOW);
      led[l]=0;
    }
    trytime=0;
  }


}


int buttonRead()
{
  while(1)
  {
    /*如果没有感应到按键触发，则返回值99*/
    int i;
    for (i = 0; i< 6; i++)
    {
      if(analogRead(button_hold[i])>800)
      {
        delay(20);
        //if(analogRead(button_hold[i])<100)
        {
          //delay(20);
          while(analogRead(button_hold[i])<500)
          {
            delay(20);
            if(analogRead(button_hold[i])<500)
              return i+1;
          }
        }
      }
    }
  }
}
void lightChange(int lightNum){

  if(led[lightNum-1]==0){
    digitalWrite(light[lightNum-1],HIGH);
    led[lightNum-1]=1;
  }
  else{
    digitalWrite(light[lightNum-1],LOW);
    led[lightNum-1]=0;
  }
}











