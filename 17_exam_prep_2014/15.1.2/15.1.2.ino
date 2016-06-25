/* Naoki Pross 2E - 06.2016 - Esame parziale di elettronica
 *
 * Descrizione: 
 *      Accensione e verifica dei segnali
 */

#include <Arduino.h>

/* I/O Pins */
// Input
#define DIN0    8
#define DIN1    9
#define DIN2    10
#define DIN3    11
#define DIN4    12
#define DIN5    13
#define DIN6    A0
#define START   A1

// Output
#define DOUT0   0
#define DOUT1   1
#define DOUT2   2
#define DOUT3   3
#define PLAY    4
#define DL6     5
#define DOUT6   6
#define DOUT7   7


void setup() {
    pinMode(DL6, OUTPUT);
    pinMode(PLAY, OUTPUT);
    pinMode(START, INPUT);
}

void loop() {
    if (digitalRead(START)) {
        digitalWrite(PLAY, HIGH);
        delay(3000);
        digitalWrite(PLAY, LOW);
        digitalWrite(DL6, HIGH);
        delay(500);
        digitalWrite(DL6, LOW);
    }
}
