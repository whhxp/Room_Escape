#include "Max6675.h"
#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
double consKp=1, consKi=0.001, consKd=9.79;
//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;


Max6675 ts(8, 9, 10);

void print_max6675()
{
  //Serial.print("MAX6675:");
  Serial.println(ts.getCelsius());
  //Serial.println(" C");
}
void setup()
{
  ts.setOffset(0);
  Serial.begin(19200);
  //Serial.println("Ready");
  windowStartTime = millis();

  //initialize the variables we're linked to
  Setpoint = 100;

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  //print_max6675();
  Input =ts.getCelsius() ;
  Serial.println(Input);
  myPID.Compute();
  analogWrite(3,Output);

}



