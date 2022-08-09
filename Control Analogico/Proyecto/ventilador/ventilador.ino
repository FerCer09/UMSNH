const int IN1 = 6;
const int IN2 = 7;
const int sal = 8;
int i=0;
void setup() {
  // put your setup code here, to run once:
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(sal,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  //giro hacia la derecha
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  //Encendido graduado
  for(i=0;i<=255;i++){
    analogWrite(sal,i);
    Serial.println(i);
    delay(20);
  }
  //apagado gradua
 for(i=255;i>=0;i--){
    analogWrite(sal,i);
    Serial.println(i);
    delay(20);
  }
}
