#define  s0 35  
#define s1 33
#define s2 29
#define s3 27
#define  out 31

int data = 0;  
float R = 0;
float G = 0;
float B = 0;
int C;

const int rows = 5;
const int cols = 6;

int currentRow = 0;
int currentCol = 0;
int lastSensorValue = 0;

int matriz[rows][cols];

void setup() {
  Serial.begin(9600);
   pinMode(s0, OUTPUT);    // pin modes
   pinMode(s1, OUTPUT);
   pinMode(s2, OUTPUT);
   pinMode(s3, OUTPUT);
   pinMode(out, INPUT);

   Serial.begin(9600);   // initialize the serial monitor baud rate
   
   digitalWrite(s0, HIGH);  // Putting S0/S1 on HIGH/HIGH levels means the output frequency scaling is at 100%  (recommended)
   digitalWrite(s1, HIGH); // LOW/LOW is off HIGH/LOW is 20% and  LOW/HIGH is  2%
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
    currentCol = 0; // Reset column
    currentRow++;   // Move to the next row
  }

  if (currentRow >= rows) {
    Serial.println("Array is full. No more values can be stored.");
    // Optionally, you can reset the array or start overwriting
    currentRow = 0; // Uncomment this to overwrite from the start
    currentCol = 0; // Uncomment this to overwrite from the start
  }
  
  lastSensorValue=Color;
  }

  delay(1000);
}

int color(){
  digitalWrite(s2, LOW);        // S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
  digitalWrite(s3, LOW);
  //Serial.print("Red  value= "); 
  R = GetData();                   // Executing GetData function to get the value

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  //Serial.print("Blue value= ");
  B = GetData();

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  //Serial.print("Green value= ");
  G = GetData();

  Serial.println();

  if (R==13 && B==11 && G==14){
    C=1;
   }
   else if(R>=124 && B>=20 && G>=40){
    C=2;
  }
  return C;
  delay(2000);
}

int GetData(){
   data = pulseIn(out, LOW);       // here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   return data;
}