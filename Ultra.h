#include <Arduino.h>

class Ultra{
  public:
    long duracion;
    long distancia;
    Ultra(int trig_pin_, int echo_pin_);
  long medirDistancia();
    
  private:
    int trig_pin;
    int echo_pin;
  
};




