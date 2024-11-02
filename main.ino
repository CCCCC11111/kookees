#include "PID.h"
//#include "Ultra.h"
#include "Gripper.h"
#include <QTRSensors.h>

const uint8_t sensorPins[] = {39, 41, 43, 45, 47, 49, 51, 53};
QTRSensors qtr;

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
PID pidlinea = PID(0.01, 2, -2, 0.0006, 0.0001, 0.0001);
int position = 0;    
Gripper gripper = Gripper(2,3);
#define trigPin1 40  // Ultrasonico 1 (Izquierdo)
#define echoPin1 38

#define trigPin2 44  // Ultrasonico 2 (Frente)
#define echoPin2 42

#define trigPin3 48  // Ultrasonico 3 (Derecho)
#define echoPin3 46

// Función para medir la distancia de un sensor ultrasónico
long medirDistancia(int trigPin, int echoPin) {

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

void setup()
{
  
  qtr.setTypeRC();
  qtr.setSensorPins(sensorPins, 8);
  qtr.setEmitterPin(37);
  // Calibrar los sensores
  
  Serial.println("Calibrando... Mueve los sensores sobre la línea durante la calibración.");
  for (int i = 0; i < 400; i++) {
    // Lee los sensores para calibrarlos
    qtr.calibrate();
    
    // Imprimir los valores durante la calibración
    if (i % 100 == 0) {
      Serial.print("Calibrando paso ");
      Serial.println(i);
    }
    delay(20);
  }
  Serial.println("Calibración completa.");



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
  gripper.setup();

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

void FLMover(int v){
  if(-v>0){
    FRForward =true;
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, -v);
  }
  else if(-v <0){
    FRForward =false;
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, v);
  }
    else{
     analogWrite(ENA, 0);
  }
}
void BLMover(int v){
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
void BRMover(int v){
  if(-v>0){
    FLForward =true;
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
    analogWrite(ENC, -v);
  }
  else if(-v < 0){
    FLForward =false;
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, HIGH);
    analogWrite(ENC, v);
  }
    else{
     analogWrite(ENC, 0);
  }
}
void FRMover(int v){
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


bool moverX(float d){
  
  int T = floor(d/(D*3.14)*15);
  double P1 =pid1.calculate(T,BLcounter);
  double P2 =pid2.calculate(T,BRcounter);
  bool run1=true;
  bool run2=true;
  
  if(BLcounter==T){
    run1=false;
    Serial.print("ajdija");
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
    int vxn=floor(vx*(510/(abs(vx)+abs(vy))));
    int vyn=floor(vy*(510/(abs(vx)+abs(vy))));
    FLMover(floor((vxn/2-vyn/2)*P));
    FRMover(floor((vxn/2+vyn/2)*P));
    BLMover(floor((vxn/2+vyn/2)*P));
    BRMover(floor((vxn/2-vyn/2)*P));
}

void moverlinea(int v,double rot, float P) {
    int vxn=floor(v*(510/(abs(v)+abs(rot))));
    int rotn=floor(rot*(510/(abs(v)+abs(rot))));
    FLMover(floor((vxn/2-rotn/2)*P));
    FRMover(floor((vxn/2+rotn/2)*P));
    BLMover(floor((vxn/2-rotn/2)*P));
    BRMover(floor((vxn/2+rotn/2)*P));
}
void resetcounter(){
  BLcounter=0;
  BRcounter=0;
  FRcounter=0;
  FLcounter=0;
}


int state=0;
bool pelota=false;
bool negro=false;

int robotcoord[] = {1,-1};
long init_time=0;
long current_time;
bool first=true;


void moverXYT(int vx, int vy ,long T){

  if(init_time ==0){
      init_time=millis();
    }
    current_time=millis();
    
    if(current_time-init_time<T){
      moverXY(vx,vy,1);
    }
    else{
      moverXY(0,1,0);
      if(vx >0){
        robotcoord[0]+=1;
      }
      else if(vx<0){
        robotcoord[0]-=1;
      }
      else if(vy<0){
        robotcoord[1]+=1;

      }
      else {
        robotcoord[1]-=1;
      }
      init_time=0;
    }      
}
int orientacion=0;
void moverRT(float r,long T, int n){

  if(init_time ==0){
      init_time=millis();
    }
    current_time=millis();
    
    if(current_time-init_time<T){
      moverlinea(0,r,1);
    }
    else{
      moverXY(0,1,0);
      if (r<0){
        orientacion+=n;
      }
      else{
        orientacion-=n;
      }
      
      init_time=0;
    }      
}


bool checarnegra(){

}


void undo(int vx, int vy){
  first= false;
          float D = current_time-init_time;
          init_time =0;
          moverXYT(-vx,-vy,D);
}




double rotacion;

void loop(){


  //moverXY(1,0,1);
   // Leer los valores de los sensores
  
  uint16_t sensorValues[8];
  qtr.readCalibrated(sensorValues);

  // Calcular la posición de la línea de forma manual
  
  int sum = 0;
  int weightedSum = 0;
  for (int i = 0; i < 8; i++) {
    weightedSum += (i * 1000) * sensorValues[i];  // Peso en el índice del sensor
    sum += sensorValues[i];
    Serial.print(sensorValues[i]);
    Serial.print("  ");
  }
  Serial.println();
  


 
  
  if (sum != 0) {
    position = qtr.readLineBlack(sensorValues);
  } 

  rotacion = pidlinea.calculate(3500,position);

  moverlinea(1,rotacion,0.8);
  

  

 

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


  if (robotcoord[0]==1& robotcoord[1]==-1){
    moverXYT(1,0,1000);
  }

  if(robotcoord[0]==1& robotcoord[1]==1){
    gripper.cerrar();
    pelota=true;
    
  }

  else if (robotcoord[0]==1& robotcoord[1]==0){
    if(first){
      if(!pelota){
      if(distancia2<7){
        moverXYT(0,1,1000);  
        if(checarnegra){
          undo(0,1);
        }
      }
      else{
          if(orientacion=0){
            moverlinea(0,1,1);
            delay(2200);
            orientacion+=2;
          }
          moverXY(-1,0,1);
          gripper.abrir();
          delay(1000);
          robotcoord[1]+=1;
      }
      }
      else{
        moverXYT(0,1,1000);
      }
    }
    else{
      moverXYT(0,-1,1000);
    }      
  }
  else if(robotcoord[0]==0& robotcoord[1]==-0){
    if(first){
      moverXYT(1,0,1000);
        if(checarnegra){
          undo(1,0);
        }
    }
    else{
      moverXYT(-1,0,1000);
    }
  }
  else if(robotcoord[0]==0& robotcoord[1]==1){
    if(first){
      if(!pelota){
      if(distancia3<5){
        moverXYT(1,0,1000);
        if(checarnegra){
          undo(1,0);
        }
      }
      else{
        //moverlinea(0,1,1)
      }
      }
      else{
        moverXYT(1,0,1000);
      }
      
        
    }
    else{
        //rotar 90
        moverXYT(-1,0,1000);
      }
    }

  
  else if(robotcoord[0]==0& robotcoord[1]==2){
    if(first){
      moverXYT(0,-1,1000);
        if(checarnegra){
          undo(0,-1); //checar que undo sea en la dirección correcta
        }
    }
    else{
      moverXYT(0,1,1000);

    }
  }
  else if(robotcoord[0]==1& robotcoord[1]==2){
    if(first){
      if(!pelota){
        //rota 90 
        if(distancia1<7){
          // desrota 90
          moverXYT(0,-1,1000);
          
        }
        else{
          // desrota 90
          moverXYT(-1,0,1000);
        }

      }
      else{
        moverXYT(1,0,1000);
      }
     
    }
    else{
      if(!pelota){
        //rota 90 
        if(distancia1<5){
          // desrota 90
          moverXYT(0,1,1000);
          
        }
        else{
          // desrota 90
          moverXYT(-1,0,1000);
        }
      }
      
      else{
        moverXYT(1,0,1000);
      }
    }

  }
   else if(robotcoord[0]==2& robotcoord[1]==2){
    if(first){
      moverXYT(-1,0,1000);
        if(checarnegra){
          undo(-1,0); //checar que undo sea en la dirección correcta
        }
    }
    else{
       moverXYT(1,0,1000);
    }
    

  }
  else if(robotcoord[0]==2& robotcoord[1]==1){
    if(first){
      //rotar 90
        moverXYT(-1,0,1000);
    }
    else
    {
      if(!pelota){
        if(distancia1<5){
          moverXYT(1,0,1000);
        }
        else{
          //rotar 90
          moverXYT(-1,0,1000);
        }
      }
    }
  }
  else if(robotcoord[0]==1& robotcoord[1]==1){


  }
  */
  
  

  

  
  
  
  
moverXY(1,0,1)


  // Imprimir las distancias en el monitor serial
  /*
  Serial.print("Distancia Izquierda: ");
  Serial.print(distancia1);
  Serial.println(" cm");

  Serial.print("Distancia Frente: ");
  Serial.print(distancia2);
  Serial.println(" cm");

  Serial.print("Distancia Derecha: ");
  Serial.print(distancia3);
  Serial.println(" cm");
  */
  
}