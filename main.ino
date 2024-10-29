#include "PID.h"
//#include "Ultra.h"
//#include "Gripper.h"
int Encoder1 = A0;
int Encoder2= A1;
bool FRForward =true;
bool FLForward = true;
bool BRForward =true;
bool BLForward = true;
bool stateE1;
bool pstateE1;
bool stateE2;
bool pstateE2;
int FRcounter;
int FLcounter;
int BRcounter;
int BLcounter;
float D=5;
int E1;
int E2;
int vxn;
int vyn;

float power;
float Ctrampa =0.005;
// Pines del primer puente H (Motor 1 y Motor 2)
const int IN1 = 24;
const int IN2 = 22;
const int IN3 = 28;
const int IN4 = 26;
const int ENA = 10;  // PWM para Motor 1
const int ENB = 11;  // PWM para Motor 2

// Pines del segundo puente H (Motor 3 y Motor 4)
const int IN5 = 30;
const int IN6 = 32;
const int IN7 = 34;
const int IN8 = 36;
const int ENC = 12;  // PWM para Motor 3
const int END = 13;  // PWM para Motor 4

PID pid1 = PID(0.01, 1, -1, 0.25, 0.0, 0.02);
PID pid2 = PID(0.01, 1, -1, 0.25, 0.0, 0.02);
#define trigPin1 40  // Ultrasonico 1 (Izquierdo)
#define echoPin1 38

#define trigPin2 44  // Ultrasonico 2 (Frente)
#define echoPin2 42

#define trigPin3 48  // Ultrasonico 3 (Derecho)
#define echoPin3 46

// Función para medir la distancia de un sensor ultrasónico
long medirDistancia(int trigPin, int echoPin) {
  // Limpiar el pin Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Enviar un pulso de 10 microsegundos al pin Trig
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer el tiempo que tarda en recibir el pulso de vuelta (Echo)
  long duracion = pulseIn(echoPin, HIGH);

  // Calcular la distancia en cm
  long distancia = duracion * 0.034 / 2;

  return distancia;
}

//Ultra *ultra1,*ultra2,*ultra3=nullptr;
//Gripper *gripper;
void setup()
{
  // Configurar pines como salida para el primer puente H
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);  // PWM para Motor 1
  pinMode(ENB, OUTPUT);  // PWM para Motor 2
  //ultra1= new Ultra(40,38);
//ultra2= new Ultra(44,42);
//ultra3= new Ultra(48,46);
//gripper = new Gripper(20,21);

  // Configurar pines como salida para el segundo puente H
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(ENC, OUTPUT);  // PWM para Motor 3
  pinMode(END, OUTPUT);  // PWM para Motor 4
Serial.begin (9600);
pinMode(Encoder1, INPUT);
pinMode(Encoder2, INPUT);
}


void encoderea(){
  E1= analogRead(Encoder1);
  E2= analogRead(Encoder2);
Serial.print("  ");
Serial.print(BRForward);
Serial.print("  ");
Serial.print(BRcounter);
Serial.print("  ");
Serial.println(BLcounter);
//Serial.print(E1); Serial.print("\t"); Serial.println(E2);
      stateE1 = E1 < 500 ;
      if(pstateE1!=stateE1){
        pstateE1=stateE1;
        FRcounter = FRForward? FRcounter+1: FRcounter-1;
        BLcounter = BLForward? BLcounter+1: BLcounter-1;
    
      }
      stateE2 = E2 < 500 ;
      if(pstateE2!=stateE2){
        pstateE2=stateE2;
        FLcounter = FLForward? FLcounter+1: FLcounter-1;
        BRcounter = BRForward? BRcounter+1: BRcounter-1;
      //Serial.print(stateE1); 
     }
    
}
void FRMover(int v){
  if(v>0){
    FRForward =true;
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, v);
  }
  else if(v <0){
    FRForward =false;
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, -v);
  }
    else{
     analogWrite(ENA, 0);
  }
}
void BRMover(int v){
  if(v>0){
    BRForward = true;
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, v);
  }
  else if(v < 0){
    BRForward = false;
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, -v);
  }
    else{
     analogWrite(ENB, 0);
  }
}
void FLMover(int v){
  if(v>0){
    FLForward =true;
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
    analogWrite(ENC, v);
  }
  else if(v < 0){
    FLForward =false;
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, HIGH);
    analogWrite(ENC, -v);
  }
    else{
     analogWrite(ENC, 0);
  }
}
void BLMover(int v){
  if(v>0){
    BLForward = true;
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);
    analogWrite(END, v);
   
  }
  else if(v < 0){
    BLForward =false;
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, HIGH);
    analogWrite(END, -v);
  }
  else{
     analogWrite(END, 0);
  }
}
float trampa(float P){
  if(P>power){
    power+=Ctrampa;
  }
  else if(P==power){
  }
  else{
    power-=Ctrampa;
  }
  return power;
}
void moverX(float d){
    int T = floor(d/(D*3.14)*15);
  double P1 =pid1.calculate(T,BLcounter);
  double P2 =pid2.calculate(T,BRcounter);
  bool run1=true;
  bool run2=true;
  
  if(BLcounter==T){
    run1=false;
  }
   if(BLcounter==T){
    run2=false;
  }
  if(run1){
  FRMover(floor(255*P1));
  BLMover(floor(255*P1));
  }
  else{
    FRMover(0);
  BLMover(0);

  }
  if (run2){
  FLMover(floor(255*P2));
  BRMover(floor(255*P2));
  }
   else{
    FLMover(0);
  BRMover(0);

  }
  if(!run1&!run2){
    return false;
  }
  encoderea();

  Serial.print("  ");
  Serial.print(P1);
  Serial.print("  ");
  Serial.print(P2);
  return true;

}
void moverY(float d){
  encoderea();
  int T = floor(d/(D*3.14)*20);
  double P1 =pid1.calculate(T,BLcounter);
  double P2 = pid2.calculate(-T,BRcounter);
  Serial.print("  ");
  Serial.print(P1);
  Serial.print("  ");
  Serial.print(P2);
  FLMover(floor(255*P2));
  FRMover(floor(255*P1));
  BLMover(floor(255*P1));
  BRMover(floor(255*P2));
}

void moverXY(int vx,int vy, float P) {
    vxn=floor(vx*(510/(abs(vx)+abs(vy))));
    vyn=floor(vy*(510/(abs(vx)+abs(vy))));
    FLMover(floor((vxn/2-vyn/2)*P));
    FRMover(floor((vxn/2+vyn/2)*P));
    BLMover(floor((vxn/2+vyn/2)*P));
    BRMover(floor((vxn/2-vyn/2)*P));
    encoderea();
}


int state=0;
bool pelota=false;

void loop(){
  moverX(30);
  // Medir la distancia de cada sensor
  /*
  long distancia1 = ultra1->medirDistancia();
  long distancia2 = ultra2->medirDistancia();
  long distancia3 = ultra3->medirDistancia();
  */

  /*
  long distancia1 = medirDistancia(trigPin1, echoPin1);
  long distancia2 = medirDistancia(trigPin2, echoPin2);
  long distancia3 = medirDistancia(trigPin3, echoPin3);

  switch (state)
  {
  case 0:
    if (distancia1<10 & distancia2 < 10 & distancia3 <10){
      state=1;
    }
    if (distancia1<10 & distancia2 > 10 & distancia3 <10){
      state=2;
    }
    if (distancia1<10 & distancia2 < 10 & distancia3 >10){
      state=3;
    }
     if (distancia1>10 & distancia2 < 10 & distancia3 <10){
      state=4;
    }
  break;

  case 1:
    gripper->abrir();
    if(!pelota){
    moverXY(-1,0,1);
    }
    else{
      moverXY(-1,0,1);
      gripper->cerrar();
    }



    break;
  
  default:
    break;
  }



  // Imprimir las distancias en el monitor serial
  Serial.print("Distancia Izquierda: ");
  Serial.print(distancia1);
  Serial.println(" cm");

  Serial.print("Distancia Frente: ");
  Serial.print(distancia2);
  Serial.println(" cm
  */
}