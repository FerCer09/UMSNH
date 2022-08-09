unsigned long tiempo, lastTime=0;
int timeMuestra = 1000; // periodo de muestreo en milisegundos
int timeCambio, nMuestras = 100;
double EA,mV,temp,error;
double ref = 38.5,control,kp=10,ki=0.1,erracum;
////////VENTILADOR:
const int IN1 = 6;
const int IN2 = 7;
const int sal = 8;
int i=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(sal,OUTPUT);
  ////////VENTILADOR
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  tiempo = millis();  //da el tiempo en milisegundos desde que se encendió la tarjeta del arduino
    timeCambio = tiempo - lastTime;
    if(timeCambio >= timeMuestra){
      for(int i = 0 ; i < nMuestras ; i++){ //promediador
        EA = analogRead(0);
        mV = EA*5000/1023;
        temp = temp + mV/10;    //Acumulando
        delay(25);
      }
      temp = temp /nMuestras;   //lo promedio
      Serial.print(temp);
      Serial.print(",");
      Serial.print(ref);
      Serial.print(",");
      error = ref - temp;
      erracum += error*timeCambio;
      control = -(kp*error+ki*erracum);
      
      if(control>127){
        control=127;
      }else if(control<-127){
        control=-127;
      }
      control= control +127;
     // Serial.print(error);
     // Serial.print(" ");
      Serial.println(control);
      analogWrite(sal,control);
      //S
      lastTime = tiempo;
      
      
    }
}
