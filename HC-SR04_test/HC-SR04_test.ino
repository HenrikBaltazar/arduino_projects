#include <NewPing.h>
 
#define TRIGGER_PIN  10
#define ECHO_PIN     9
#define MAX_DISTANCE 500

const int ledA = 7;
const int ledB = 6;
const int lowDist = 30;
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup()
{
  Serial.begin(9600);
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop()
{
  if(sonar.ping_cm() >= lowDist || sonar.ping_cm() == 0)
  {
    digitalWrite(ledA, HIGH);
    digitalWrite(ledB, LOW);
    delay(1000);
  }
  if(sonar.ping_cm() < lowDist && sonar.ping_cm())
  {
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, HIGH);
    delay(1000);
  }
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
  delay(50);
}
