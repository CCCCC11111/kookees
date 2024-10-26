 #include "Chasis.h"
 Chasis::Chasis(){
  int Encoder1 = A0;
int Encoder2= A1;
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
  else if(P<power){
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
void setup(){

}