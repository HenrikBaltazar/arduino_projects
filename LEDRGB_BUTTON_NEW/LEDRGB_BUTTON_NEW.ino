int redpin=9;      //Pin 9
int greenpin=10;    //Pin 10
int bluepin=11;      //Pin 11
int buzzer=7;

void setup()
{
  Serial.begin(9600); //Inicia a serial com um baud rate de 9600
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  long tecladoA0=0; //Cria variável para ler o teclado ligado ao pino A0
  for(int i=0;i<100;i++) //Laço para fazer 100 leituras
  {
    tecladoA0 = tecladoA0+analogRead(A0); //Soma a leitura anterior com a leitura atual de A0
  }
  tecladoA0 = tecladoA0/100;
  if(tecladoA0 > 0 && tecladoA0 < 310){
    Serial.print("Teclado A0 = NUMERO 1 ->"); //Imprime no Serial Monitor "Teclado A0 = "
    Serial.println(tecladoA0); //Imprime o valor de A0
    Serial.print("\n\n"); //Pula 2 linha no Serial Monitor
    analogWrite(redpin, 255);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);
    digitalWrite(buzzer, HIGH);delay(100);digitalWrite(buzzer, LOW);
  }
  if(tecladoA0 > 310 && tecladoA0 < 460){
    Serial.print("Teclado A0 = NUMERO 2 ->"); //Imprime no Serial Monitor "Teclado A0 = "
    Serial.println(tecladoA0); //Imprime o valor de A0
    Serial.print("\n\n"); //Pula 2 linha no Serial Monitor
    analogWrite(redpin, 0);
    analogWrite(greenpin, 255);
    analogWrite(bluepin, 0);
    digitalWrite(buzzer, HIGH);delay(100);digitalWrite(buzzer, LOW);
    
  }
  if(tecladoA0 > 460){
    Serial.print("Teclado A0 = NUMERO 3 ->"); //Imprime no Serial Monitor "Teclado A0 = "
    Serial.println(tecladoA0); //Imprime o valor de A0
    Serial.print("\n\n"); //Pula 2 linha no Serial Monitor
    analogWrite(redpin, 0);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 255);
    digitalWrite(buzzer, HIGH);delay(100);digitalWrite(buzzer, LOW);
  }

}
