/*
   Lab IoT e Robotica Educativa ITI A. Monaco di Cosenza - 24/10/2024
 */

const int ORARIO = 1;
const int ANTIORARIO = -1;
// definizione del numero di passi per rotazione - 32 passi per rotazione ma con riduzione 1/64 (circa) (1/63,68395 = )
const int passiPerRotazione = 2048;
const int velocita = 40;
const int primoPin = 4;   // Collegamenti ai controller ULN2003
int registroMotore = 1;         // registri motori

void eseguiPasso(int senso)
{
  if (senso == ORARIO)
  {
    for (int i = 0, maschera=1; i < 4; i++, maschera*=2)
    {
      if (registroMotore == maschera)
      { digitalWrite(primoPin+i,HIGH); }
      else
      { digitalWrite(primoPin+i,LOW); }
    }
    registroMotore *= 2;
  }
  if (senso == ANTIORARIO)
  {
    for (int i = 3, maschera=8; i >=0; i--, maschera/=2)
    {
      if (registroMotore == maschera)
      { digitalWrite(primoPin+i,HIGH); }
      else
      { digitalWrite(primoPin+i,LOW); }
    }
    registroMotore /= 2;
  }
  if (registroMotore > 8) registroMotore=1;
  if (registroMotore <=0) registroMotore = 8;
}
void setup() {

// inizializzazione della porta seriale
  Serial.begin(9600);
}

void loop() {
  Serial.println("Rotazione senso orario");
  for (int p=0; p<passiPerRotazione;p++)
  {
    eseguiPasso(ORARIO);
    delay(velocita);
  }
  delay(500);
  Serial.println("Rotazione senso antiorario");
  for (int p=passiPerRotazione; p>=0;p--)
  {
    eseguiPasso(ANTIORARIO);
    delay(velocita);
  }
  delay(500);
}
