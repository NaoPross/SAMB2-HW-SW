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

// in seconds
#define E1_TIMEOUT 2

void setup() {
    DDRC |= (1<<E1 | 1<<E2 | 1<<E3 | 1<<M);
    DDRC &= ~(1<<START | 1<<S1 | 1<<S2 | 1<<S3);
}

void loop() {
    // wait for START to go HIGH
    while (!(PINC & 1<<START));
    // tempo per poter premere e rilasciare 
    _delay_ms(1500);

    // close E3
    PORTC &= ~(1<<E3);

    bool startState = 0;
    uint16_t e1Time = millis();

    // while START  not been pressed
    while (!startState) {
        // check START state
        startState = PINC & 1<<START;

        // if $timeSpent is less than 2 seconds
        if (millis() - e1Time <= E1_TIMEOUT*1000) {
            // turn on E1
            PORTC |= 1<<E1;
        } else {
            // turn off E1
            PORTC &= ~(1<<E1);
        }

        // if S2 is 0 and S3 is 1
        if (!(PINC & 1<<S2) && PINC & 1<<S3) {
            PORTC |= 1<<E2;
        } else {
            PORTC &= ~(1<<E2);
        }

        // if S1 is 0
        if (!(PINC & 1<<S1)) {
            // turn on E3
            PORTC |= 1<<E3;
        } else {
            PORTC &= ~(1<<E3);
        }

        // if S2 is 0 or S3 is 0
        if (!(PINC & 1<<S2) || !(PINC & 1<<S3)) {
            // turn on the motor
            PORTC |= 1<<M;
        } else {
            PORTC &= ~(1<<M);
        }
    }

    // turn off everything
    // PORTC &= ~(1<<E1 | 1<<E2 | 1<<E2 | 1<<M);
}