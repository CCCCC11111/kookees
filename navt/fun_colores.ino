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
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, 23, NEO_GRB + NEO_KHZ800);

void setColor(int redValue, int greenValue,  int blueValue) {
analogWrite(Red, redValue);
analogWrite(Green,  greenValue);
analogWrite(Blue, blueValue);
}

void matriz_col(){
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
  //Serial.print("Red");
  //Serial.println(R);
  int G=getGreenPW();
  //Serial.print("Green");
  //Serial.println(G);
  int B=getBluePW();
  //Serial.print("Blue");
  //Serial.println(B);
  //Serial.println();
/*
  if(R>580){
    Serial.println("Blue");
    C=1;
    setColor(0,0,255);
  }
  else if(R>250){
    Serial.println("Purple");
    C=2;
    setColor(170,0,255);
  }
  else if(R>110){
    Serial.println("Red");
    C=3;
    setColor(255,0,0);
  }
  else if(R<110){
    if(G>300){
      Serial.println("Pink");
      C=4;
      setColor(255,20,147);
    }
    else if (R>75){
      Serial.println("Yellow");
      C=5;
      setColor(255,255,0);
    }
    else if(R<70){
      Serial.println("White");
      setColor(255,255,255);
    }
  }
*/

  if(R>90){
    if(G>110){
      Serial.println("Blue");
      C=1;
      setColor(0,0,255);
    }
    else if(G>70){
      Serial.println("Purple");
      C=2;
      setColor(170,0,255);
    }
  }
  else if(R<20){
    Serial.println("White");
    setColor(255,255,255);
  }
  else if(R<50){
    if(G>130){
      if(B>70){
        Serial.println("Red");
        C=3;
        setColor(255,0,0);
      }
    }
    else if(G>70){
      Serial.println("Pink");
      C=4;
      setColor(255,20,147);
    }
    else if(B>60){
      Serial.println("Yellow");
      C=5;
      setColor(255,255,0);
    }
  }
  else {
    Serial.println("Unknown");
  }
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
}