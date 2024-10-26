#include "I2Cdev.h"
#include "MPU6050.h"
#include <Arduino.h>

class MPU6050Read {
  public:
  MPU6050Read();
  void read();
  void setup();
  calibrate();
  private:
  MPU6050 mpu(0x68); 

};

