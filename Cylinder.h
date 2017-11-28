#ifndef Cylinder_h
#define Cylinder_h
#include "Arduino.h"
#include "StepperMotor.h"

#define Cylinder_RackSensor     24

class Cylinder: public StepperMotor{
  public:
    Cylinder(int, int, int, int, char, char);
    ~Cylinder(void);
    void Test_CW();
    void Test_CCW();
    void Sens_Rotation();
    void Reach_Target();
    void Update(unsigned char, unsigned char);
    void Origin(int);
    attachInterrupt(digitalPinToInterrupt(Cylinder_RackSensor), IRS_Rack, FALLING);
    attachInterrupt(digitalPinToInterrupt(Cylinder_OriginSensor), IRS_Origin, FALLING);
  private:
    unsigned char stepcw, stepccw;
    char          Buffer;
    unsigned long stepnumber;
    
    
};

Cylinder::Cylinder(int OriginSensor, int stepPin, int dirPin, int EnablePin, char Pos_Min, char Pos_Max):StepperMotor(OriginSensor, stepPin, dirPin, EnablePin, Pos_Min, Pos_Max){ 
}

Cylinder::~Cylinder(void){
}

void Cylinder::IRS_Rack(){
  stepnumber --
}

/*
void Cylinder::Test_CW() {
  stepcw = 0;
  Buffer = sCurrentPos;
  while (sTargetPos != Buffer) {
    stepcw++;
    Buffer++;
    if (Buffer > sPos_Max) {
      Buffer = sPos_Min;
    }
  }
}

void Cylinder::Test_CCW() {
  stepccw = 0;
  Buffer = sCurrentPos;
  while (sTargetPos != Buffer) {
    stepccw++;
    Buffer--;
    if (Buffer == 255)  Buffer = sPos_Max;
  }
}

void Cylinder::Sens_Rotation() {
  Test_CW();
  Test_CCW();
  if (stepccw >= stepcw) {
    digitalWrite(sdirPin, HIGH);
    stepnumber = stepcw;
  }
  else {
    digitalWrite(sdirPin, LOW);
    stepnumber = stepccw;
  }
}
*/

void Cylinder::Reach_Target() {
  Sens_Rotation();
  while (stepnumber != 0) {
    analogWrite(sstepPin, 127);
    while (digitalRead(Cylinder_RackSensor) == true);
    Serial.print("StepNumber = ");
    Serial.println(stepnumber);
    /*if (digitalRead(Cylinder_RackSensor) == true) {
      Serial.println("CAPTEUR");
      stepnumber --;
      Serial.print("StepNumber = ");
      Serial.println(stepnumber);
      if (stepnumber == 255)  stepnumber = 0;*/
    }
  }
  analogWrite(sstepPin, 0);
  sCurrentPos = sTargetPos;
  CurrentPos = sCurrentPos;
}

void Cylinder::Update(unsigned char CurrentPos, unsigned char TargetPos) {
  sTargetPos = TargetPos;
  sCurrentPos = CurrentPos;
  Reach_Target();
}

void Cylinder::Origin(int OriginSensor) {
  digitalWrite(sdirPin, LOW);
  analogWrite(sstepPin, 127);
  while (digitalRead(sOriginSensor) == true);
  analogWrite(sstepPin, 0);
}

#endif
