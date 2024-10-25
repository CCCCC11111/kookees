#define  s0 35      //Module pins wiring
#define s1 33
#define s2 29
#define s3 27
#define  out 31

int data=0;
int R=0;
int B=0;
int G=0;
int SumR=0;
int SumB=0;
int SumG=0;
int promB=0;
int promG=0;
int promR=0;

void setup() {
  pinMode(s0,OUTPUT);    //pin modes
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(out,INPUT);

  Serial.begin(9600);   //intialize the serial monitor baud rate
   
  digitalWrite(s0,HIGH);  //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100%  (recommended)
  digitalWrite(s1,LOW);
}
int x=0;

void loop() {
  x++;

  digitalWrite(s2, LOW);        // S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
  digitalWrite(s3, LOW);
  //Serial.print("Red  value= "); 
  R = GetData(); 
  SumR=SumR+R;

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  //Serial.print("Blue  value= ");
  B = GetData();
  SumB=SumB+B;

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  //Serial.print("Green value= ");
  G = GetData();
  SumG=SumG+G;

  
  if (x==1000){
    x=0;
    //Serial.println(SumR);
    //Serial.println(SumB);
    //Serial.println(SumG);
    promR=SumR/1000;
    promB=SumB/1000;
    promG=SumG/1000;
    Serial.println(promR);
    Serial.println(promB);
    Serial.println(promG);
    Serial.println();
  }

}

int GetData(){
  data=pulseIn(out,LOW);       //here  we wait until "out" go LOW, we start measuring the duration and stops when "out"  is HIGH again
  return data;
}