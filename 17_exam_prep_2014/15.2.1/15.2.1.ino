/* Naoki Pross 2E - 06.2016 - Esame parziale di elettronica
 *
 * Descrizione: 
 *      Funzione Selettore
 */

#include <Arduino.h>

/* I/O Pins */
// Input
#define DIN0    8
#define DIN1    9
#define DIN2    10
#define S200B0  11
#define S200B1  12
#define S200B2  13
#define S220B3  A0
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
    pinMode(S200B0, INPUT);
    pinMode(S200B1, INPUT);
    pinMode(S200B2, INPUT);
    pinMode(S200B3, INPUT);
    pinMode(DL6, OUTPUT);
}

void loop() {
    digitalWrite(DL6, LOW);

    char s200 = ~(digitalRead(S200B0) | digitalWrite(S200B1) << 1 |
        digitalRead(S200B2) << 2 | digitalRead(S200B3) << 3);

    if (s200 == 6) {
        digitalWrite(DL6, HIGH);
        delay(1000);
        digitalWrite(DL6, LOW);
        delay(1000);
    }
    else if (s200 == 9 || s200 == 0xA) {
        digitalWrite(DL6, HIGH);
        delay(200);
        digitalWrite(DL6, LOW);
        delay(1000);
    }
}
