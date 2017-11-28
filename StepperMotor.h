#ifndef StepperMotor_h
#define StepperMotor_h

#include "Arduino.h"

class StepperMotor {

  public:
    StepperMotor(int, int, int, int, char, char);
    ~StepperMotor(void);
    unsigned char GetCurrentPos(),
                  CurrentPos;
  protected:
    char          sCurrentPos,
                  TargetPos,
                  sTargetPos,
                  sPos_Min,
                  sPos_Max;
    int           sdirPin,
                  sEnablePin,
                  sOriginSensor,
                  sstepPin;
};

StepperMotor::StepperMotor(int OriginSensor, int stepPin, int dirPin, int EnablePin, char Pos_Min, char Pos_Max){
  sOriginSensor = OriginSensor;
  sstepPin = stepPin;
  sdirPin = dirPin;
  sEnablePin = EnablePin;
  sPos_Min = Pos_Min;
  sPos_Max = Pos_Max;
  pinMode(sstepPin, OUTPUT);
  pinMode(sdirPin, OUTPUT);
  pinMode(sOriginSensor, INPUT);
} 

StepperMotor::~StepperMotor(void){
  
}

unsigned char StepperMotor::GetCurrentPos() {
  return CurrentPos;
}

#endif
