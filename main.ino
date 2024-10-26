

// Pines del primer puente H (Motor 1 y Motor 2)

//#include "MPU6050Read.h"


void setup()
{
 

Serial.begin (9600);
pinMode(Encoder1, INPUT);
pinMode(Encoder2, INPUT);
//Mpu = new MPU6050Read();


}




void loop(){
      //Mpu.read();
   
      encoderea();
      if(BRcounter<500){  
        BRMover(255); 
      }
      else{
        BRMover(0);
      }

      if(BLcounter<500){  
        BLMover(255) ;
      
      }
      else{
        BLMover(0);
      }
}