#ifndef Carriage_h
#define Carriage_h
#include "Arduino.h"
#include "StepperMotor.h"

#define Carriage_ExtSensor      99 // NON DEFINI
#define Carriage_IntSensor      99 // NON DEFINI

#define Degagement              50
#define Ext_Barillet            1900
#define Retrait                 100
#define Barillet_Ascenseur      2100
#define Ascenseur_Barillet      2100
#define Barillet_Ext            1800
#define Ext_Ascenseur           3800
#define Ascenseur_Ext           3800

class Carriage: public StepperMotor{
  public:
    Carriage(int, int, int, int, char, char);
    ~Carriage(void);
    void Update_Loader(unsigned char, unsigned char);
    void Reach_Target_Loader();
    void Origin_Loader(int);

  private:

};

Carriage::Carriage(int OriginSensor, int stepPin, int dirPin, int EnablePin, char Pos_Min, char Pos_Max):StepperMotor(OriginSensor, stepPin, dirPin, EnablePin, Pos_Min, Pos_Max){ 
}

Carriage::~Carriage(void){
}

void Carriage::Reach_Target_Loader() {
  if (sTargetPos == 1){
    if (sCurrentPos == 2){
      digitalWrite(sdirPin, LOW);
      for(int x = 0; x < Barillet_Ext; x++){
        digitalWrite(sstepPin,HIGH);
        delay(1);
        digitalWrite(sstepPin,LOW);
        delay(1);
      }
    }
    else if (sCurrentPos == 3){
      digitalWrite(sdirPin, LOW);
      for(int x = 0; x < Ascenseur_Ext; x++){
        digitalWrite(sstepPin,HIGH);
        delay(1);
        digitalWrite(sstepPin,LOW);
        delay(1);
      }
    }
    sCurrentPos = 1;
  }
  else if (sTargetPos == 3){
    if (sCurrentPos == 1){
      digitalWrite(sdirPin, HIGH);
      for(int x = 0; x < Ext_Ascenseur; x++){
        digitalWrite(sstepPin,HIGH);
        delay(1);
        digitalWrite(sstepPin,LOW);
        delay(1);
      }
    }
    else if (sCurrentPos == 2) {
      digitalWrite(sdirPin, HIGH);
      for(int x = 0; x < Barillet_Ascenseur; x++) {
        digitalWrite(sstepPin,HIGH);
        delay(1);
        digitalWrite(sstepPin,LOW);
        delay(1);
      }
    }
    sCurrentPos = 3;
  }
  else if (sTargetPos == 2){
    if (sCurrentPos == 1){
      digitalWrite(sdirPin, HIGH);
      for(int x = 0; x < Ext_Barillet; x++) {
        digitalWrite(sstepPin,HIGH);
        delay(1);
        digitalWrite(sstepPin,LOW);
        delay(1);
      }
      digitalWrite(sdirPin, LOW);
      for(int x = 0; x < Retrait; x++) {
        digitalWrite(sstepPin,HIGH);
        delay(1);
        digitalWrite(sstepPin,LOW);
        delay(1);
      }
    }
    else if (sCurrentPos == 3) {
      digitalWrite(sdirPin, LOW);
      for(int x = 0; x < Ascenseur_Barillet; x++) {
        digitalWrite(sstepPin,HIGH);
        delay(1);
        digitalWrite(sstepPin,LOW);
        delay(1);
      }
    }
    sCurrentPos = 2;
  }
}

void Carriage::Update_Loader(unsigned char CurrentPos, unsigned char TargetPos) {
  sTargetPos = TargetPos;
  sCurrentPos = CurrentPos;
  Reach_Target_Loader();
  CurrentPos = sCurrentPos;
}

void Carriage::Origin_Loader(int OriginSensor) {
  digitalWrite(sdirPin, LOW);
  Serial.print("OriginSensor = ");
  Serial.println(sOriginSensor);
  while (digitalRead(sOriginSensor) == true){
    digitalWrite(sstepPin,HIGH);
    delay(1);
    digitalWrite(sstepPin,LOW);
    delay(1);
  }
  digitalWrite(sdirPin, HIGH);
  for(int x = 0; x < Degagement; x++) {
    digitalWrite(sstepPin,HIGH);
    delay(1);
    digitalWrite(sstepPin,LOW);
    delay(1);
  }
  sCurrentPos = 1;
}

#endif
