//Ângulos do Servomotor

#define abre 90
#define fecha 180
#define centro 90
#define esquerda 0
#define direita 180
// Definições dos Pinos
#define olhos 8
#define irPin 2

#include <Servo.h>

Servo servoboca,servocabeca;

int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)

boolean powerstatus = false;
boolean statuscentrocabeca = false;
boolean cabecaesq = true;
boolean cabecadir = false;
boolean bocafechada = true;

void setup()
{
  pinMode(olhos, OUTPUT);
  pinMode(irPin, INPUT);

servoboca.attach(9);
  servocabeca.attach(10);

servoboca.write(fecha);
  servocabeca.write (135);
  digitalWrite(olhos, LOW);
}

void loop()
{
  int key = getIRKey(); //Fetch the key
  if(key != 0)
  {
    if (key == 149) //Botão de Power
    {
      powerstatus = powerstatus ^1;
      if(powerstatus == 1)
      {
        digitalWrite(olhos, HIGH);
        servocabeca.write (centro);
        delay(300);
        servoboca.write(abre);
        delay(100);
        servoboca.write (fecha);
        delay(135);
        cabecadir = false;
        cabecaesq = false;
      }
    }

if (powerstatus == 1)
    {

      switch(key)
      {

case 144: //CH Down - Fecha a Boca
        if (bocafechada == LOW)
        {
          servoboca.write(fecha);
          delay(500);
          bocafechada = HIGH;
          break;
        }
        else //Pisca os olhos se a boca já estiver fechada
        {
          digitalWrite(olhos, LOW);
          delay(150);
          digitalWrite(olhos, HIGH);
          delay(150);
          digitalWrite(olhos, LOW);
          delay(150);
          digitalWrite(olhos, HIGH);
          break;
        }

case 145: //CH Up - Abre a boca
        if (bocafechada == HIGH)
        {
          servoboca.write(abre);
          delay(500);
          bocafechada = LOW;
          break;
        }
        else //Pisca os olhos se a boca já estiver aberta
        {
          digitalWrite(olhos, LOW);
          delay(150);
          digitalWrite(olhos, HIGH);
          delay(150);
          digitalWrite(olhos, LOW);
          delay(150);
          digitalWrite(olhos, HIGH);
          break;
        }

case 146: //VOL Right - Move a cabeça para direita
        if (cabecadir == false & cabecaesq == false || cabecadir == true & cabecaesq == false)
        {
          servocabeca.write(direita);
          delay(150);
          cabecadir = true;
          break;
        }
        else if (cabecadir == false & cabecaesq == true)
        {
          servocabeca.write(centro);
          delay(150);
          cabecaesq = false;
          break;
        }

case 147: //VOL Left - Move a cabeça para esquerda
        if (cabecadir == false & cabecaesq == false ||cabecadir == false & cabecaesq == true)
        {
          servocabeca.write(esquerda);
          delay(150);
          cabecaesq = true;
          break;
        }
        else if (cabecadir == true & cabecaesq == false)
        {
          servocabeca.write(centro);
          delay(150);
          cabecadir = false;
          break;
        }

case 148: //Botão Mute - Faz SIM com a cabeça e pisca os olhos
        servoboca.write(abre);
        delay(150);
        digitalWrite(olhos, LOW);
        servoboca.write(fecha);
        delay(150);
        digitalWrite(olhos, HIGH);
        servoboca.write(abre);
        delay(150);
        digitalWrite(olhos, LOW);
        servoboca.write(fecha);
        delay(200);
        digitalWrite(olhos, HIGH);
        break;

case 165: // Botão AV/TV - Faz NÃO com a cabeça e pisca os olhos
        servocabeca.write(45);
        delay(150);
        servocabeca.write(135);
        delay(150);
        digitalWrite(olhos, LOW);
        servocabeca.write(45);
        delay(150);
        digitalWrite(olhos, HIGH);
        servocabeca.write(135);
        delay(150);
        digitalWrite(olhos, LOW);
        servocabeca.write(centro);
        delay(150);
        digitalWrite(olhos, HIGH);

         cabecadir = false;

         cabecaesq = false;

         break;

      }
    }
    else
    {
      servoboca.write(180);
      delay(150);
      servocabeca.write(135);
      delay(300);
      digitalWrite(olhos, LOW);
    }
  }
}

int getIRKey()
{
  int data[12];
  int i;

while(pulseIn(irPin, LOW) < start_bit); //Wait for a start bit

for(i = 0 ; i < 11 ; i++)
    data[i] = pulseIn(irPin, LOW); //Start measuring bits, I only want low pulses

for(i = 0 ; i < 11 ; i++) //Parse them
  {
    if(data[i] > bin_1) //is it a 1?
      data[i] = 1;
    else if(data[i] > bin_0) //is it a 0?
      data[i] = 0;
    else
      return -1; //Flag the data as invalid; I don't know what it is! Return -1 on invalid data
  }

int result = 0;
  for(i = 0 ; i < 11 ; i++) //Convert data bits to integer
      if(data[i] == 1) result |= (1<<i); // Atenção - Substitua o * por outro Sinal de menor que (<) 

return result; //Return key number // Limitação do editor usado pelo Site
}
//Fim do sketch


