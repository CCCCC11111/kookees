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


void setup()
{
  // Configurar pines como salida para el primer puente H
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);  // PWM para Motor 1
  pinMode(ENB, OUTPUT);  // PWM para Motor 2

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
Serial.print(BRcounter);  Serial.print("\t"); Serial.println(BLcounter);
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
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
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
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
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
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
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
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);
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

void moverXY(int vx,int vy, float P) {
    vxn=floor(vx*(510/(abs(vx)+abs(vy))));
    vyn=floor(vy*(510/(abs(vx)+abs(vy))));
    FLMover(floor((vxn/2-vyn/2)*P));
    FRMover(floor((vxn/2+vyn/2)*P));
    BLMover(floor((vxn/2+vyn/2)*P));
    BRMover(floor((vxn/2-vyn/2)*P));
    encoderea();
}
void loop(){
   
      encoderea();
      if(BRcounter<500){  
        BRMover(255); 
      }
      else{
        BRMover(0);
      }

      if(BLcounter<500){  
        BLMover(255) ;
      
      }
      else{
        BLMover(0);
      }

      
}