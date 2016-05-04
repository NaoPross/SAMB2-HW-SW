#include <Arduino.h>
#include <avr/delay.h>

// Bits definitions on PORT C
#define START 0
// Sensors: 0 = submerged
#define S1    1
#define S2    2
#define S3    3

// Valves: 1 = OPEN
#define E1    4
#define E2    5
#define E3    6

// Motor: 1 = RUNNING
#define M     7

// in milliseconds
#define E1_TIMEOUT 2000

void setup() {
    // set output
    DDRC |= (1<<E1 | 1<<E2 | 1<<E3 | 1<<M);
    // set input
    DDRC &= ~(1<<START | 1<<S1 | 1<<S2 | 1<<S3);
}

void loop() {
    // wait for START to go HIGH
    while (!(PINC & 1<<START));
    // tempo per poter premere e rilasciare (simulazione)
    _delay_ms(1500);

    // turn off E3
    PORTC &= ~(1<<E3);

    uint16_t e1_time = millis();

    while (PINC & 1<<S3) {
        if (millis() - e1_time <= E1_TIMEOUT) {
            // turn on E1
            PORTC |= 1<<E1;
        } else {
            // turn off E1
            PORTC &= ~(1<<E1);
        }

        // if S2 is 0
        if (!(PINC & 1<<S2)) {
            // turn on M
            PORTC |= 1<<M;
            // turn off E2
            PORTC &= ~(1<<E2);
        }
    }

    // turn off E2
    PORTC &= ~(1<<E2);
    // turn on E3
    PORTC |= 1<<E3;
    // wait for S2 to go up
    while (!(PINC & 1<<S2));
    // turn off M
    PORTC &= ~(1<<M);
    // wait for S1 to go up
    while (!(PINC & 1<<S1));
}