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
long init_time=0;
long current_time; 

/*void encoderea(){
  E1= analogRead(Encoder1);
  E2= analogRead(Encoder2);
  //Serial.print(BRcounter);  Serial.print("\t"); Serial.println(BLcounter);
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
*/
void FRMover(int v){
  if(v>0){
    FRForward =true;
    digitalWrite(FRM1, HIGH);
    digitalWrite(FRM2, LOW);
    analogWrite(PWM_FRM, v);
  }
  else if(v <0){
    FRForward =false;
    digitalWrite(FRM1, LOW);
    digitalWrite(FRM2, HIGH);
    analogWrite(PWM_FRM, -v);
  }
    else{
     analogWrite(PWM_FRM, 0);
  }
}

void BRMover(int v){
  if(v>0){
    BRForward = true;
    digitalWrite(BRM1, HIGH);
    digitalWrite(BRM2, LOW);
    analogWrite(PWM_BRM, v);
  }
  else if(v < 0){
    BRForward = false;
    digitalWrite(BRM1, LOW);
    digitalWrite(BRM2, HIGH);
    analogWrite(PWM_BRM, -v);
  }
    else{
     analogWrite(PWM_BRM, 0);
  }
}

void FLMover(int v){
  if(v>0){
    FLForward =true;
    digitalWrite(FLM1, HIGH);
    digitalWrite(FLM2, LOW);
    analogWrite(PWM_FLM, v);
  }
  else if(v < 0){
    FLForward =false;
    digitalWrite(FLM1, LOW);
    digitalWrite(FLM2, HIGH);
    analogWrite(PWM_FLM, -v);
  }
    else{
     analogWrite(PWM_FLM, 0);
  }
}

void BLMover(int v){
  if(v>0){
    BLForward = true;
    digitalWrite(BLM1, HIGH);
    digitalWrite(BLM2, LOW);
    analogWrite(PWM_BLM, v);
   
  }
  else if(v < 0){
    BLForward =false;
    digitalWrite(BLM1, LOW);
    digitalWrite(BLM2, HIGH);
    analogWrite(PWM_BLM, -v);
  }
  else{
     analogWrite(PWM_BLM, 0);
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
    //encoderea();
}

void moverXYT(int vx, int vy, long T) {
   if(init_time==0){
      init_time=millis();
    }
    current_time=millis();
    
    if(current_time-init_time<T){
      moverXY(vx,vy,1);
    }
    else{
      init_time=0;
    }
}
