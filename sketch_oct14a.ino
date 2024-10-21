int sensor = A0;
bool FRForward =true;
bool FLForward = true;
bool BRForward =true;
bool BLForward = true;
bool state;
bool pstate;
int FRcounter;
int FLcounter;
int BRcounter;
int BLcounter;
int v;
int vxn;
int vyn;
float power;
float Ctrampa =0.0005;
// Pines del primer puente H (Motor 1 y Motor 2)
const int IN1 = 22;
const int IN2 = 24;
const int IN3 = 26;
const int IN4 = 28;
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
pinMode(sensor, INPUT);
}


void encoderea(){
  v= analogRead(sensor);
      if(v<127){
        state=false;
      }
      else{
        state=true;
      }
      if(pstate!=state){

      if(FRForward){
        FRcounter++;
      }
      else{
        FRcounter--;
      }
      if(FLForward){
        FLcounter++;
      }
      else{
        FLcounter--;
      }
      if(BRForward){
        BRcounter++;
      }
      else{
        BRcounter--;
      }
      if(BLForward){
        BLcounter++;
      }
      else{
        BLcounter--;
      }

      }

}
void FRMover(int v){
  if(v>0){
    FRForward =true;
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, v);
  }
  else{
    FRForward =false;
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, -v);
  }
}
void FLMover(int v){
  if(v>0){
    FLForward = true;
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, v);
  }
  else{
    FLForward = false;
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, -v);
  }
}
void BLMover(int v){
  if(v>0){
    BLForward =true;
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
    analogWrite(ENC, v);
  }
  else{
    BLForward =false;
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
    analogWrite(ENC, -v);
  }
}
void BRMover(int v){
  if(v>0){
    BRForward = true;
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);
    analogWrite(END, v);
  }
  else{
    BRForward =false;
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);
    analogWrite(END, -v);
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
    vxn=floor(vx*(510/abs(vx+vy)));
    vyn=floor(vy*(510/abs(vx+vy)));
    FLMover(floor((vxn/2-vyn/2)*P));
    FRMover(floor((vxn/2+vyn/2)*P));
    BLMover(floor((vxn/2+vyn/2)*P));
    BRMover(floor((vxn/2-vyn/2)*P));
    encoderea();
}

void loop(){  
      moverXY(1,1,trampa(1));
}