long detect(int E,int T){
  long t; //tiempo
  long d; //distancia
  digitalWrite(T, LOW);
  delayMicroseconds(2);

  digitalWrite(T, HIGH);
  delayMicroseconds(10);     
  digitalWrite(T, LOW);
  
  t = pulseIn(E, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  /*Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println(); */
  //delay(1000);          //Hacemos una pausa de 100ms
  return(d);
}