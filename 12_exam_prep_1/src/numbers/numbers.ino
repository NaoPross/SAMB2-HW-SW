#include <Arduino.h>

// on PORT A
#define START 0x01
#define S0    0x02
#define S1    0x04

// on PORT C
#define LEDS  0x0F

#define D_TIME 500

void setup() {
    DDRA &= ~(START | S0 | S1);
    DDRC |= LEDS;
}

void loop() {
    while (!(PINA & START)); // off
    while (PINA & START);    // on
    delay(D_TIME);
    while (!(PINA & START)); // off

    while (PINA & START) {   // while on
        bool _s0 = (PINA & S0);
        bool _s1 = (PINA & S1);

        if (!_s0 && !_s1) {
            PORTC = 0x01;
        } else if (!_s0 && _s1) {
            PORTC = 0x03;
        } else if (_s0 && !_s1) {
            PORTC = 0x07;
        } else if (_s0 && _s1) {
            PORTC = 0x0F;
        } 
    }

    PORTC &= 0x00;
}