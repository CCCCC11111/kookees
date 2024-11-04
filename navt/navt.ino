long RD=0;
long LD=0;
long CD=0;
int d=8;

void setup(){
  #define Blue 7
  #define Green 6
  #define Red 5

  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);

  #define FRM1 24
  #define FRM2 22 
  #define PWM_FRM 10  
  #define BRM1 28
  #define BRM2 26
  #define PWM_BRM 11
  pinMode(FRM1, OUTPUT);
  pinMode(FRM2, OUTPUT);
  pinMode(PWM_FRM, OUTPUT);
  pinMode(BRM1, OUTPUT);
  pinMode(BRM2, OUTPUT);
  pinMode(PWM_BRM, OUTPUT);

  #define FLM1 30
  #define FLM2 32
  #define PWM_FLM 12
  #define BLM1 34
  #define BLM2 36
  #define PWM_BLM 13

  pinMode(FLM1, OUTPUT);
  pinMode(FLM2, OUTPUT);
  pinMode(PWM_FLM, OUTPUT);
  pinMode(BLM1, OUTPUT);
  pinMode(BLM2, OUTPUT);
  pinMode(PWM_BLM, OUTPUT);

  #define US_RT 48
  #define US_RE 46
  #define US_LT 40
  #define US_LE 38
  #define US_CT 44
  #define US_CE 42

  pinMode(US_RT, OUTPUT); 
  pinMode(US_RE, INPUT); 
  pinMode(US_LT, OUTPUT);
  pinMode(US_LE, INPUT);
  pinMode(US_CT, OUTPUT);
  pinMode(US_CE, INPUT);
  //digitalWrite(US_RT, LOW);
  #define s0 35
#define s1 33
#define s2 29
#define s3 27
#define out 31

  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(out,INPUT);

  digitalWrite(s0,HIGH);
  digitalWrite(s1,LOW);
  
  Serial.begin(9600);
  //pixels.begin();
}

bool cambiar =false;
bool x=false; //false==izquierda
bool y=false; //false==atras

//El robot cambia de frente para la primera pista
void loop(){
  color();

  RD=detect(US_RE, US_RT);
  LD=detect(US_LE, US_LT);
  CD=detect(US_CE, US_CT);

  if(cambiar){
    moverXY(-1,0,1);
    delay(1300);
    cambiar=false;
  }

  if (CD>d){ //si no detecta adelante
    moverXY(0,1,1); //avanza adelante
    y=true;
  }
  else { //si detecta adelante
    if(LD>d && RD<d){ // si esta a la derecha 
      if (y==true){
        moverXY(0,-1,1);
      }
      moverXY(1,0,1); // izquierda
      x=false;
    }
    else if(RD>d && LD<d){ // si esta a la izquierda
      moverXY(-1,0,1); // derecha
      x=true;
    }
    else { // si ambos
      if (LD>d && RD>d){
        if(x==true){
          moverXY(-1,0,1);
        }
        else if(x==false){
          moverXY(1,0,1);
        }
      }
      else {
        moverXY(0,-1,1);
        delay(1100);
        cambiar=true;
    }
  }
} 

}