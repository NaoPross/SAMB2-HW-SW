/* Naoki Pross 2E - 06.2016 - Esame parziale di elettronica
 *
 * Descrizione: 
 *      Programma finale
 */

#include <Arduino.h>

/* I/O Pins */
// Input
#define MODO_VOL 8
#define DIN1    9
#define STOP    10
#define S200B0  11
#define S200B1  12
#define S200B2  13
#define S200B3  A0
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

// constants
#define MUTE  3
#define MIN   2
#define MEDIO 1
#define MAX   0


void setup() {
    pinMode(DOUT0, OUTPUT);
    pinMode(DOUT1, OUTPUT);
    pinMode(PLAY, OUTPUT);
    pinMode(DL6, OUTPUT);

    pinMode(MODO_VOL, INPUT);
    pinMode(STOP, INPUT);
    pinMode(S200B0, INPUT);
    pinMode(S200B1, INPUT);
    pinMode(S200B2, INPUT);
    pinMode(S200B3, INPUT);
    pinMode(START, INPUT);
}

void loop() {
    digitalWrite(DL6, LOW);
    digitalWrite(PLAY, LOW);

    if (digitalRead(START)) {
        digitalWrite(DOUT0, HIGH);
        digitalWrite(DOUT1, HIGH);
        delayMicroseconds(50);
        digitalWrite(PLAY, HIGH);

        while (!digitalRead(STOP)) {
            digitalWrite(DL6, LOW);
            digitalWrite(PLAY, LOW);

            if (digitalRead(MODO_VOL)) {
                char s200 = digitalRead(S200B0) | digitalRead(S200B1) << 1;
                switch (s200) {
                case MUTE:
                    digitalWrite(DOUT0, LOW);
                    digitalWrite(DOUT1, LOW);
                    digitalWrite(DL6, HIGH);
                    delay(500);
                    break;
                case MIN:
                    digitalWrite(DOUT0, LOW);
                    digitalWrite(DOUT1, HIGH);
                    digitalWrite(DL6, HIGH);
                    delay(1500);
                    break;
                case MEDIO:
                    digitalWrite(DOUT0, HIGH);
                    digitalWrite(DOUT1, LOW);
                    digitalWrite(DL6, HIGH);
                    delay(2500);
                    break;
                case MAX:
                    digitalWrite(DOUT0, HIGH);
                    digitalWrite(DOUT1, HIGH);
                    digitalWrite(DL6, HIGH);
                    delay(3500);
                    break;
                }
            }
        }

        digitalWrite(DL6, HIGH);
        delay(1500);
    }
}
