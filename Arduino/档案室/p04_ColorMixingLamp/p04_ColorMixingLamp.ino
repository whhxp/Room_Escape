
/*
调色在误差范围内正确后，高电平信号输出给13号口
 */

#define DEBUG 1
const int greenLEDPin = 9;    
const int redLEDPin = 10;     
const int blueLEDPin = 11;    
const int greenLEDPin0 = 3;   
const int redLEDPin0 = 6;     
const int blueLEDPin0 = 5;    
const int signalOut=13;

const int redSensorPin = A0;   
const int greenSensorPin = A1;   
const int blueSensorPin = A2;    
/*各个颜色正确值*/
const int redRightValue = 50;   
const int greenRightValue = 180;  
const int blueRightValue = 80; 
const int misRange = 40;//误差范围



int redActualValue = 0; // value to write to the red LED
int greenActualValue = 0; // value to write to the green LED
int blueActualValue = 0; // value to write to the blue LED

int redSensorValue = 0; // variable to hold the value from the red sensor 
int greenSensorValue = 0; // variable to hold the value from the green sensor 
int blueSensorValue = 0; // variable to hold the value from the blue sensor 

void setup() {
  // initialize serial communications at 9600 bps:
#if DEBUG
  Serial.begin(9600); 
#endif
  // set the digital pins as outputs
  pinMode(greenLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);
  pinMode(blueLEDPin,OUTPUT);
  pinMode(greenLEDPin0,OUTPUT);
  pinMode(redLEDPin0,OUTPUT);
  pinMode(blueLEDPin0,OUTPUT);
  pinMode(signalOut,OUTPUT);
}

void loop() {

  digitalWrite(signalOut, LOW);
  redSensorValue = analogRead(redSensorPin);
  delay(5);
  greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  blueSensorValue = analogRead(blueSensorPin);  
#if DEBUG
  Serial.print("raw sensor Values \t red: ");
  Serial.print(redSensorValue);
  Serial.print("\t green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.println(blueSensorValue);
#endif
  redActualValue = redSensorValue/4;
  greenActualValue = greenSensorValue/4;
  blueActualValue = blueSensorValue/4;  
#if DEBUG
  Serial.print("Mapped sensor Values \t red: ");
  Serial.print(redActualValue);
  Serial.print("\t green: ");
  Serial.print(greenActualValue);
  Serial.print("\t Blue: ");
  Serial.println(blueActualValue);

  //  delay(2000);
  Serial.print(redRightValue);
  Serial.print("\t green: ");
  Serial.print(greenRightValue);
  Serial.print("\t Blue: ");
  Serial.println(blueRightValue);
  //delay(2000);
#endif
  analogWrite(redLEDPin0, redRightValue);
  analogWrite(greenLEDPin0, greenRightValue);
  analogWrite(blueLEDPin0, blueRightValue);

  analogWrite(redLEDPin, redActualValue);
  analogWrite(greenLEDPin, greenActualValue);
  analogWrite(blueLEDPin, blueActualValue);
  if((redActualValue<(redRightValue+misRange))&&
    (redActualValue>(redRightValue-misRange))&&
    (greenActualValue<(greenRightValue+misRange))&&
    (greenActualValue>(greenRightValue-misRange))&&
    (blueActualValue<(blueRightValue+misRange))&&(blueActualValue>(blueRightValue-misRange))){

    digitalWrite(signalOut, HIGH);  
    rightEffect();
  }



}

void rightEffect(){

  for(int i=0;i<3;i++){
    analogWrite(redLEDPin, redRightValue);
    analogWrite(greenLEDPin, greenRightValue);
    analogWrite(blueLEDPin, blueRightValue);
    delay(500);
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 0);
    delay(500);

  }
  while(1){

    analogWrite(redLEDPin, redRightValue);
    analogWrite(greenLEDPin, greenRightValue);
    analogWrite(blueLEDPin, blueRightValue);

#if DEBUG
    Serial.print("Mapped sensor Values \t red: ");
    Serial.print(redRightValue);
    Serial.print("\t green: ");
    Serial.print(greenRightValue);
    Serial.print("\t Blue: ");
    Serial.println(blueRightValue); 
#endif
  }

}





