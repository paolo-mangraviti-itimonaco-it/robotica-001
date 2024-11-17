/*
   Lab IoT e Robotica Educativa ITI A. Monaco di Cosenza - 24/10/2024
 */

const bool ORARIO = true;
const bool ANTIORARIO = false;
// definizione del numero di passi per rotazione - 32 passi per rotazione ma con riduzione 1/64 (circa) (esattamente 1/63,68395)
const int passiPerRotazione = 2048;
const int velocita = 70;
const int numeroMotori = 1;                  // numero totali dei motori
const short unsigned int primoPin[] = {4};   // Collegamenti ai controller ULN2003
short unsigned int registro[] = {1};         // registro dei motori

void outputDigitale(int dati,int pin,int numeroBit)
{ for (int e = 0,maschera = 1; e < numeroBit; e++,maschera <<= 1,pin++) if ((dati & maschera) == 0) digitalWrite(pin,LOW); else digitalWrite(pin,HIGH); }

void eseguiPasso(bool senso,int motore)
{
  outputDigitale(registro[motore],primoPin[motore],4);

  if (senso == ORARIO) { registro[motore] <<= 1; }
  else if (senso == ANTIORARIO) { registro[motore]>>=1; }

  registro[motore] = (registro[motore] > 8)?1:((registro[motore] <= 0)?8:registro[motore]);
}

void inizializzaMotori(int motore) { for (int i=0; i<4; i++) pinMode(primoPin[motore]+i,OUTPUT); }

void setup() {
  Serial.begin(9600);
  for (int m = 0; m<numeroMotori; m++) { inizializzaMotori(m); }
}

void loop() {
  for (int p=0; p<passiPerRotazione;p++)  { eseguiPasso(ORARIO,0); delay(velocita); }
  delay(2000);
  for (int p=0; p<passiPerRotazione;p++)  { eseguiPasso(ANTIORARIO,0); delay(velocita); }
  delay(2000);
}
