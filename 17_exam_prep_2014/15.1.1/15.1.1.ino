/* Naoki Pross 2E - 06.2016 - Esame parziale di elettronica
 *
 * Descrizione: 
 *      Accensione e verifica dei segnali
 */

#include <Arduino.h>

/* I/O Pins definition */
// Input
#define DIN0    8
#define DIN1    9
#define DIN2    10
#define DIN3    11
#define DIN4    12
#define DIN5    13
#define DIN6    A0
#define DIN7    A1

// Output
#define DOUT0   0
#define DOUT1   1
#define DOUT2   2
#define DOUT3   3
#define DOUT4   4
#define DL6     5
#define DOUT6   6
#define DOUT7   7


void setup() {
    pinMode(DL6, OUTPUT);
}

void loop() {
    digitalWrite(DL6, HIGH);
    delay(250);
    digitalWrite(DL6, LOW);
    delay(250);
}
