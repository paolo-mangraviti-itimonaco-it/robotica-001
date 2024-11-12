//HC RS04 Sensore ultrasuoni

const int triggerPort = 8;
const int echoPort = 9;
const int led = 11;
const int distanzaSoglia = 10;
 
void setup() {
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.print( "Sensore Ultrasuoni: Verosimilmente Pronto");
}

void loop() {
  //porta bassa l'uscita del trigger
  digitalWrite( triggerPort, LOW );
  //invia un impulso di 10microsec su trigger
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort, LOW );
  long durata = pulseIn( echoPort, HIGH, 1000 );
  long distanza = 0.034 * durata / 2;
  Serial.print("distanza: ");
  
  //dopo 38ms è fuori dalla portata del sensore
  if( durata > 1000 ) { Serial.println("Fuori portata"); }
  else { 
    Serial.print("cm:"); Serial.println(distanza);
    Serial.print("mt:"); Serial.println(distanza*10);
  }
  
  if(distanza < distanzaSoglia) { digitalWrite(led, HIGH); }
  else { digitalWrite(led, LOW); }

  //pausa tra ogni iterazione un decimo di secondo
  delay(100);
}
