#include <Arduino.h>
#include "Constants.h"
const int IN1 = 24;
const int IN2 = 22;
const int IN3 = 28;
const int IN4 = 26;
const int ENA = 10;  // PWM para Motor 1
const int ENB = 11;  // PWM para Motor 2

// Pines del segundo puente H (Motor 3 y Motor 4)
const int IN5 = 30;
const int IN6 = 32;
const int IN7 = 34;
const int IN8 = 36;
const int ENC = 12;  // PWM para Motor 3
const int END = 13;  // PWM para Motor 4
class Chasis{
  public:
  Chasis();
  void setup();
  void BLMover();
  void FLMover();
  void FRMover();
  void BRMover();
  void moverXY();
  void trampa();
  void encoderea();
  bool FRForward =true;
  bool FLForward = true;
  bool BRForward =true;
  bool BLForward = true;
  int vxn;
  int vxy;
  float Power;
  
  private:
  int vxn;
  int vxy;
  float Power;
  


}