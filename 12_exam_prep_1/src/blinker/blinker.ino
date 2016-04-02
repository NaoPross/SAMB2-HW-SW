/* Nao Pross 2B
 *
 * Compile w/
 * $ arduino --verify --board arduino:avr:megaADK blinker/blinker.ino
 */
#include <Arduino.h>

// on PORT A
#define START 0x01
#define S0    0x04
#define S1    0x08
#define S2    0x10

// on PORT C
#define LEDS  0x1E

void setup() {
    DDRA &= ~(START | S0 | S1 | S2);
    DDRC |= LEDS;

    PORTC &= ~(LEDS);
}

void loop() {
    while (!(PINA & START));
    while (PINA & START);

    uint16_t delayTime = (PINA & S0) ? 500 : 1000;

    for (int i = 0; i < 10; i++) {
        PORTC |= LEDS;
        delay(delayTime);
        PORTC &= ~(LEDS);
        delay(delayTime);
    }
}