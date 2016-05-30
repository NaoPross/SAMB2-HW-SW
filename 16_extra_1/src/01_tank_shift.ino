#define BITLED 1
#define BITL0  2
#define BITL1  3
#define BITL2  4

void setup() {
    // L0, L1, L2 are input
    DDRB &= ~(1<<BITL0 | 1<<BITL1 | 1<<BITL2);
    // LED is output
    DDRB |= 1<<BITLED;

    // turn off LED
    PORTB & ~(1<<BITLED);
}

void loop() {
    char sensor = (((PINB & (1<<BITL0 | 1<<BITL1 | 1<<BITL2)) >> 2) & 7;
    
    if (sensor == 0) {
        PORTB |= 1<<BITLED;
        delay(1000);
        PORTB &= ~1<<BITLED;
        delay(1000);
    }
    else if (sensor >= 6) {
        PORTB |= 1<<BITLED;
    }
    else {
        PORTB &= ~1<<BITLED;
    }
}
