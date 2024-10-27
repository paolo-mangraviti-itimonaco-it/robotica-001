/*
 * Fonte originaria: Prof. Michele Maffucci 28.10.2020
   Modifica: Lab IoT e Robotica Educativa ITI A. Monaco di Cosenza
 */

// inclusione della libreria Stepper 
#include <Stepper.h>

// definizione del numero di passi per rotazione - 32 passi per rotazione ma con riduzione 1/64 (circa) (1/63,68395 = )
const int passiPerRotazione = 2048;

// creazione dell'istanza della classe stepper

/*
 * IN1 -> 8
 * IN2 -> 9
 * IN3 -> 10
 * IN4 -> 11
 */

Stepper motore01(passiPerRotazione, 8, 10, 9, 11);

void setup() {
  /* 
   * non è necessario impostare i pin di Arduino
   * a cui collegare la scheda dello stepper 
   * vengono gestiti dalla libreria
   */

// imposta la velocità a 15 rpm:
  motore01.setSpeed(15);

// inizializzazione della porta seriale
  Serial.begin(9600);
}

void loop() {
  // imposta una rotazione in senso orario
  Serial.println("Rotazione senso orario");
  motore01.step(passiPerRotazione);
  delay(500);

// imposta una rotazione in senso antiorario
  Serial.println("Rotazione senso antiorario");
  motore01.step(-passiPerRotazione);
  delay(500);
}