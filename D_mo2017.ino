  // Modification dans variant.h de la variable PWM_FREQUENCY afin de changer la fréquence par défaut du PWM

//#include "StepperMotor.h"           // Classe Moteur pas à pas
#include "Cylinder.h"
#include "Carriage.h"
#include "Lift.h"                   // Classe Ascenseur
#include "Config.h"                 // Bibliothéque Configuration

unsigned char Carriage_CurrentPos = 1, 
              Lift_CurrentPos = 1,
              RxdBuffer[2],         // Déclaration Buffer de réception
              ActualAdress = 0,
              Address = 0,
              Command = 0,
              Check_serial_is_OK,
              State = 0;
int           Sequence = 0,
              i = 0,
              j = 0;
unsigned long CurrentMillis;        // Variable millis
bool          test = true;

Lift Lift(Lift_pinUp, Lift_pinDown, Lift_UpSensor, Lift_MiddleSensor);                                                               //Appel de l'objet ascenseur
Cylinder Cylinder(Cylinder_OriginSensor, Cylinder_StepPin, Cylinder_DirPin, Cylinder_EnablePin, Cylinder_PosMin, Cylinder_PosMax);   //Appel de l'objet barillet
Carriage Carriage(Carriage_OriginSensor, Carriage_StepPin, Carriage_DirPin, Carriage_EnablePin, Carriage_PosMin, Carriage_PosMax);   //Appel de l'objet chariot

void setup() {

  Serial.begin(115200);                         // Port série pour communication avec Raspberry
  
  pinMode(Carriage_OriginSensor, INPUT_PULLUP);
  pinMode(Buzzer_Output, OUTPUT);
  pinMode(Cylinder_EnablePin, INPUT);
  digitalWrite(Cylinder_DirPin, LOW);
  Cylinder.Origin(Cylinder_OriginSensor);
  
}


void FlushIncomingSerial(){
/////////////////////////////////   Vider le buffer de réception  ////////////////////////
  while(Serial.available())
  Serial.read();
}

void ReadSerial(){
/////////////////////////////////   Attente et lecture de trame   //////////////////////////////
  CurrentMillis = millis();
  while (!Serial.available())
    {
      if((millis() - CurrentMillis) >= 500){
        break; 
      }
    }

  ActualAdress = 0;
  if (Serial.read() == Start_Command)
  {
    for(;;)
    {
      RxdBuffer[ActualAdress] = Serial.read();
      if (RxdBuffer[ActualAdress] == 255)
        ActualAdress--;
      if (RxdBuffer[ActualAdress] == Start_Command)
        break;
      else
      {
        ActualAdress++;
      }
    }
  }
}


void SendSerial(){
/////////////////////////////////   Envoi de trame dans les 2 ports série   //////////////////////////////
  Serial.print(Start_Command);
  Serial.print(Address);
  Serial.print(Command);
  Serial.println(State);
}

void loop() {

    // Remise à zéro des variables de communications à chaque boucle
  Address = 0;    
  Command = 0;
  State = 0;
  
  ReadSerial();   // Lecture série

  Address = RxdBuffer[0];
  Command = RxdBuffer[1];
  
  Check_serial_is_OK = 0;
  // Tester la trame recu
  if ((Address != Start_Command) && (Command != Start_Command)){      // si la trame est correct (pas de 9 dans la commande ou l'adresse)   
      Check_serial_is_OK = 1;
  }
  else{                                                               // si la trame est mauvaise, ou identique, ne rien faire dans le switch/case
    Address = 0;
  }
  
  State = 1;
  SendSerial();

  if (((Address == 1) && (Command == 0)) || (digitalRead(Carriage_OriginSensor) == false)){
   // Début de la démo
  }
  FlushIncomingSerial();
  
}
