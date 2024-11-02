#include "Gripper.h"

Gripper::Gripper(int pinservo1_,int pinservo2_){
    pinservo1=pinservo1_;
    pinservo2=pinservo2_;
}
void Gripper::setup(){
    myservo1.attach(pinservo1);
    myservo2.attach(pinservo2);
}
void Gripper::abrir(){
    myservo1.write(90);    
    myservo2.write(90);  

}
void Gripper::cerrar(){
    myservo1.write(0);  
    myservo2.write(0); 
}
 