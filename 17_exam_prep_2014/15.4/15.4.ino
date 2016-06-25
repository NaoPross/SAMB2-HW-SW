/* Naoki Pross 2E - 06.2016 - Esame parziale di elettronica
 *
 * Descrizione: 
 *      Esegui Canzone
 */

#include <Arduino.h>

/* I/O Pins */
// Input
#define DIN0    8
#define DIN1    9
#define STOP    10
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
    pinMode(DOUT0, OUTPUT);
    pinMode(DOUT1, OUTPUT);
    pinMode(START, INPUT);
    pinMode(STOP, INPUT);
}

void loop() {
    digitalWrite(DL6, LOW);
    digitalWrite(PLAY, LOW);

    if (digitalRead(START)) {
        digitalWrite(DOUT0, HIGH);
        digitalWrite(DOUT1, HIGH);
        delayMicroseonds(50);
        digitalWrite(PLAY, HIGH);
        
        while (!digitalRead(STOP));

        digitalWrite(DL6, HIGH);
        delay(1500);
    }
}
