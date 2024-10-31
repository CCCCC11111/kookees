#define s0 2
#define s1 3
#define s2 4
#define s3 5
#define out 6

int data = 0;  
float R = 0;
float G = 0;
float B = 0;
int C=0;

const int rows = 3;
const int cols = 5;

int currentRow = 0;
int currentCol = 0;
int lastSensorValue = 0;

int matriz[rows][cols];
void setup() { // put your setup code here, to run once:
  // set pin modes
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(out,INPUT);

  digitalWrite(s0,HIGH);
  digitalWrite(s1,LOW);

  Serial.begin(9600);
}

void loop(){
  int Color=color();

  if(Color != lastSensorValue){
  matriz[currentRow][currentCol]=Color;
  Serial.print("Stored color ");
  Serial.print(Color);
  Serial.print(" at position [");
  Serial.print(currentRow);
  Serial.print("][");
  Serial.print(currentCol);
  Serial.println("]");
  currentCol++;

  if (currentCol >= cols) {
    currentCol = 0; 
    currentRow++; 
  }

  if (currentRow >= rows) {
    Serial.println("Array is full. No more values can be stored.");
    currentRow = 0;
    currentCol = 0;
  }
  
  lastSensorValue=Color;
  }

}

int color(){
  int R=getRedPW();
  Serial.print("Red");
  Serial.println(R);
  int G=getGreenPW();
  Serial.print("Green");
  Serial.println(G);
  int B=getBluePW();
  Serial.print("Blue");
  Serial.println(B);
  Serial.println();

  if(R>100){
    if(G>250 && B<130){
      Serial.println("Blue");
    }
    else if(G<250 && B>145){
      Serial.println("Purple");
    }
  }
  else if(R>60){
    if(G>215 && B>170){
      Serial.println("Red");
    }
    else if(G<40 && B<70){
      Serial.println("Pink");
    }
  }
  else if(R<50){
    if(G>110 && B<70){
      Serial.println("Orange");
    }
    else if(G<70 && B>110){
      Serial.println("Yellow");
    }
    else{
      Serial.println("Unknown");
    }
  }

  /*/*if (R<100 && G>60 && B>100){
    Serial.println("Red");
    C=1;
  }
  else if (R<60 && G<40 && B>60){
    if (R<45){
      //Serial.println("Light orange");
      C=2;
    }
    else {
      //Serial.println("Orange");
      C=2;
    }
  }
  else if (R>50 && G<32 && B<70){
    Serial.println("Light yellow");
    C=3;
    if (R>60){
      Serial.println("Yellow");
      C=3;
    }
  }
  else if(R>55 && G<25 && B<65){
    Serial.println("Pink");
    C=4;
  }
  else if(R>77 && G<25 && B>80){
    Serial.println("Lavender");
    C=5;
  }*/


  /*else if(R>390 && G>70 && B>390){
    Serial.println("Dark blue");
    C=6;
  }
  else if(R>250 && G<45 && B>260){
    Serial.println("Blue");
    C=6;
  }*/


  return C;
  //delay(2000);
}

int getRedPW(){
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  int PW;
  PW = pulseIn(out, HIGH);
  return PW; 
}

int getGreenPW(){
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int PW;
  PW = pulseIn(out, HIGH);
  return PW; 
}

int getBluePW(){
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  int PW;
  PW = pulseIn(out, HIGH);
  return PW; 