#ifndef Lift_h
#define Lift_h

class Lift{

  public:
  Lift(int, int, int, int);
  void GoTo(unsigned char);
  void Move();
  void Stop_MotorMiddle();
  void Stop_MotorUp();
  void MiniCut();
  bool Buzz;
  void GoUp();
  void GoDown();
  void Stop();
  bool InMotion;

  private:
  char sTargetPos, 
       PreviousPos, 
       CurrentPos = 0;
  int  spinUp, 
       spinDown,
       sMiddleSensor, 
       sUpSensor;    
};

Lift::Lift(int pinUp, int pinDown, int UpSensor, int MiddleSensor){
  spinUp = pinUp;
  spinDown = pinDown;
  sUpSensor = UpSensor;
  sMiddleSensor = MiddleSensor; 
  pinMode(spinUp, OUTPUT);
  pinMode(spinDown, OUTPUT);
  pinMode(sMiddleSensor, INPUT);
  pinMode(sUpSensor, INPUT);
  digitalWrite(spinUp, LOW);
  digitalWrite(spinDown, LOW);
  sTargetPos = 0;
}

void Lift::GoTo(unsigned char TargetPos){
  sTargetPos = TargetPos;
  MiniCut();
  Move();
  Serial3.print("CurrentPOS = ");
  Serial3.println(CurrentPos);
}

void Lift::Move(){
  if (sTargetPos == 1){
    digitalWrite(spinDown, HIGH);
    digitalWrite(spinUp, LOW);
    CurrentPos = 1;
    Serial3.println("Descente");
  }
  else if (sTargetPos == 3){
    digitalWrite(spinUp, HIGH);
    digitalWrite(spinDown, LOW);
    Serial3.println("Montee");
  }
  else if (sTargetPos == 2){
    if (digitalRead(sMiddleSensor) == true){
      if (CurrentPos == 1){
        digitalWrite(spinUp, HIGH);
        digitalWrite(spinDown, LOW); 
        Serial3.println("Montee2");
      }
      else if (CurrentPos == 3){
        digitalWrite(spinDown, HIGH);
        digitalWrite(spinUp, LOW);
        Serial3.println("Descente2");
      }
    }
    else {
      digitalWrite(spinDown, LOW);
      digitalWrite(spinUp, LOW);
    }
  }
}

void Lift::Stop_MotorMiddle(){
  digitalWrite(spinDown, LOW);
  digitalWrite(spinUp, LOW);
  CurrentPos = 2;
}

void Lift::Stop_MotorUp(){
  digitalWrite(spinDown, LOW);
  digitalWrite(spinUp, LOW);
  CurrentPos = 3;
}

void Lift::MiniCut(){
  if (sTargetPos != PreviousPos){
    digitalWrite(spinDown, LOW);
    digitalWrite(spinUp, LOW);
    pinMode(spinUp, INPUT);
    pinMode(spinDown, INPUT);
    delay(100);
    pinMode(spinUp, OUTPUT);
    pinMode(spinDown, OUTPUT);
    PreviousPos = sTargetPos;
  }
}

void Lift::GoUp(){
  digitalWrite(spinUp, HIGH);
  digitalWrite(spinDown, LOW);
  InMotion = true;
}

void Lift::GoDown(){
  digitalWrite(spinUp, LOW);
  digitalWrite(spinDown, HIGH);
  InMotion = true;
}

void Lift::Stop(){
  digitalWrite(spinUp, LOW);
  digitalWrite(spinDown, LOW);
  InMotion = false;
}

#endif
