long RD=0;
long LD=0;
long CD=0;

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
  pinMode(US_LT, OUTPUT);
  pinMode(US_LE, INPUT);
  pinMode(US_CT, OUTPUT);
  pinMode(US_CE, INPUT);
  //digitalWrite(US_RT, LOW);

  Serial.begin(9600);
}

//El robot cambia de frente para la primera pista
void loop(){
  RD=detect(US_RE, US_RT);
  LD=detect(US_LE, US_LT);
  CD=detect(US_CE, US_CT);

  moverXY(1,0,1);

  if(RD<7 && LD<7){ //Si detecta pared en ambos lados
    if(CD<7){ //pared en ambos lados y adelante
      moverXY(1,0,1); //hacia atras
    }
    moverXY(-1,0,1); //Avanza hacia adelante (invertido)
  }
  //Pared detras
  else if(CD<7){
    if(RD<7){ //Pared atras y derecha
      moverXY(0,-1,1); //Avanza a la izquierda
    }
    else if(LD<7){ //Pared frente e izquierda
      moverXY(0,1,1); //Avanza a la derecha
    }
    moverXY(0,1,1); //Avanza a la derecha
  }
  //Pared a la derecha
  else if(RD<7){ //Detecta a la derecha
    moverXY(1,0,1); //Avanza adelante
  }
  else if(LD<7){ //Detecta a la izquierda
    moverXY(1,0,1); //Avanza adelante
  }
  

  /*if (RD<10){
    Serial.print("Derecha=");
    Serial.println(RD);
    moverXY(0,1,1);
  }
  else if (LD<10){
    Serial.print("Izquierda=");
    Serial.println(LD);
    moverXY(0,-1,1);
  }
  else if(CD<10){
    Serial.print("Centro=");
    Serial.println(CD);
    moverXY(-1,0,1);
  } */
}