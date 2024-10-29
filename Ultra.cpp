#include "Ultra.h"

Ultra::Ultra(int trig_pin_, int echo_pin_){
    trig_pin_=trig_pin_;
    echo_pin=echo_pin_;
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
}

// Función para medir la distancia de un sensor ultrasónico
long Ultra::medirDistancia() {
  // Limpiar el pin Trig
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  // Enviar un pulso de 10 microsegundos al pin Trig
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  // Leer el tiempo que tarda en recibir el pulso de vuelta (Echo)
  duracion = pulseIn(echo_pin, HIGH);
  Serial.print(duracion);

  // Calcular la distancia en cm
  distancia = duracion * 0.034 / 2;

  return distancia;
}
