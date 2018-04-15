void setup()
{
  Serial.begin(9600); //Inicia a serial com um baud rate de 9600
}

void loop()
{
  long tecladoA0=0; //Cria variável para ler o teclado ligado ao pino A0
  
  for(int i=0;i<100;i++) //Laço para fazer 100 leituras
  {
    tecladoA0 = tecladoA0+analogRead(A0); //Soma a leitura anterior com a leitura atual de A0
  }
  
  tecladoA0 = tecladoA0/100;
  
  Serial.print("Teclado A0 = "); //Imprime no Serial Monitor "Teclado A0 = "
  Serial.println(tecladoA0); //Imprime o valor de A0
  Serial.print("\n\n"); //Pula 2 linha no Serial Monitor
  
  delay(100); //Aguarda 100 milissegundos

}
