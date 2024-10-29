#include <Arduino.h>
#include <Servo.h>

class Gripper{
  public:
    Gripper(int servopin1_, int servopin2_);
  void abrir();
  void cerrar();
    
  private:
    int pinservo1;
    int pinservo2;
    Servo myservo1;
    Servo myservo2;
};