/*
  Obtener la medición del sensor LM35, usando un promediador.
*/
unsigned long tiempo, lastTime=0;
int timeMuestra = 1000; // periodo de muestreo en milisegundos
int timeCambio, nMuestras = 100;
double EA,mV,temp,error;
double ref = 30;

void setup() {
    Serial.begin(9600);
}

void loop() {
    tiempo = millis();  //da el tiempo en milisegundos desde que se encendió la tarjeta del arduino
    timeCambio = tiempo - lastTime;
    if(timeCambio >= timeMuestra){
      for(int i = 0 ; i < nMuestras ; i++){ //promediador
        EA = analogRead(0);
        mV = EA*5000/1023;
        temp = temp + mV/10;    //Acumulando
        delay(10);
      }
      temp = temp /nMuestras;   //lo promedio
      Serial.println(temp);
      
      error = ref - temp;
      //Serial.println(error);
      
      lastTime = tiempo;
      
      
    }
}
