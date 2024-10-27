/*
   Lab IoT e Robotica Educativa ITI A. Monaco di Cosenza - 24/10/2024
 */

const int ORARIO = 1;
const int ANTIORARIO = -1;
// definizione del numero di passi per rotazione - 32 passi per rotazione ma con riduzione 1/64 (circa) (1/63,68395 = )
const int passiPerRotazione = 2048;
const int velocita = 40;
const int primoPin[] = {4};   // Collegamenti ai controller ULN2003
int registro[] = {1};         // registri motori

void eseguiPasso(int senso,int motore)
{
  if (senso == ORARIO)
  {
    for (int i = 0, maschera=1; i < 4; i++, maschera*=2)
    {
      if (registro[motore] == maschera)
      { digitalWrite(primoPin[motore]+i,HIGH); }
      else
      { digitalWrite(primoPin[motore]+i,LOW); }
    }
    registro[motore] *= 2;
  }
  if (senso == ANTIORARIO)
  {
    for (int i = 3, maschera=8; i >=0; i--, maschera/=2)
    {
      if (registro[motore] == maschera)
      { digitalWrite(primoPin[motore]+i,HIGH); }
      else
      { digitalWrite(primoPin[motore]+i,LOW); }
    }
    registro[motore] /= 2;
  }
  if (registro[motore] > 8) registro[motore]=1;
  if (registro[motore] <=0) registro[motore] = 8;
}
void setup() {

// inizializzazione della porta seriale
  Serial.begin(9600);
}

void loop() {
  Serial.println("Rotazione senso orario");
  for (int p=0; p<passiPerRotazione;p++)
  {
    eseguiPasso(ORARIO,1);
    delay(velocita);
  }
  delay(500);
  Serial.println("Rotazione senso antiorario");
  for (int p=passiPerRotazione; p>=0;p--)
  {
    eseguiPasso(ANTIORARIO,1);
    delay(velocita);
  }
  delay(500);
}
