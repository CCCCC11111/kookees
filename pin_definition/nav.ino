long D=0;
long I=0;
//long C=0;

void setup(){
  pinMode(Encoder1, INPUT);
  pinMode(Encoder2, INPUT);

  pinMode(FRM1, OUTPUT);
  pinMode(FRM2, OUTPUT);
  pinMode(PWM_FRM, OUTPUT);
  pinMode(BRM1, OUTPUT);
  pinMode(BRM2, OUTPUT);
  pinMode(PWM_BRM, OUTPUT);

  pinMode(FLM1, OUTPUT);
  pinMode(FLM2, OUTPUT);
  pinMode(PWM_FLM, OUTPUT);
  pinMode(BLM1, OUTPUT);
  pinMode(BLM2, OUTPUT);
  pinMode(PWM_BLM, OUTPUT);

  pinMode(US_RT, OUTPUT); 
  pinMode(US_RE, INPUT); 
  digitalWrite(US_RT, LOW);

  Serial.begin(9600);
}

void loop(){
  //detect(US_RE, US_RT);
  D=detect(US_RE, US_RT);
  I=detect(US_LE, US_LT);
  if (D<10){
    FRMover(130);
  }
  else if (I<10){
    FLMover(130);
  }
  else{
    moverXY(0,1,0);
    Serial.print("N");
  }
  
}