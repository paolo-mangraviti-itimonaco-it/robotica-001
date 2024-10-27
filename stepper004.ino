/*
   Lab IoT e Robotica Educativa ITI A. Monaco di Cosenza - 24/10/2024
 */

const int ORARIO = 1;
const int ANTIORARIO = -1;
// definizione del numero di passi per rotazione - 32 passi per rotazione ma con riduzione 1/64 (circa) (esattamente 1/63,68395)
const int passiPerRotazione = 2048;
const int velocita = 10;
const int primoPin[] = {4};   // Collegamenti ai controller ULN2003
int registro[] = {1};         // registri motori

void eseguiPasso(int senso,int motore)
{
  if (senso == ORARIO) { for (int i=0,maschera=1; maschera < 16; maschera*=2, i++) { digitalWrite(primoPin[motore]+i,(registro[motore] == maschera)?HIGH:LOW); } registro[motore]*=2; }
  else if (senso == ANTIORARIO) { for (int i=4,maschera=8; maschera >0; maschera/=2,i--) { digitalWrite(primoPin[motore]+i,(registro[motore] == maschera)?HIGH:LOW); } registro[motore]/=2; }
  //{ Serial.print((registro[motore] == maschera)?HIGH:LOW); } registro[motore]*=2; Serial.println(); }
  //{ digitalWrite(primoPin[motore]+i,(registro[motore] == maschera)?HIGH:LOW); }
  //{ Serial.print((registro[motore] == maschera)?HIGH:LOW); } registro[motore]/=2; Serial.println(); }
  //{ digitalWrite(primoPin[motore]+i,(registro[motore] == maschera)?HIGH:LOW); } registro[motore]/=2; }

  registro[motore] = (registro[motore] > 8)?1:((registro[motore] <=0)?8:registro[motore]);
  //if (registro[motore] > 8) registro[motore]=1; else if (registro[motore] <=0) registro[motore] = 8;
}
void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int p=0; p<passiPerRotazione;p++)  { eseguiPasso(ORARIO,1); delay(velocita); }
  delay(2000);
  for (int p=0; p<passiPerRotazione;p++)  { eseguiPasso(ANTIORARIO,1); delay(velocita); }
  delay(2000);
}