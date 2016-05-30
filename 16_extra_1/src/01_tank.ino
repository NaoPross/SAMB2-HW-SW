#define BITLED 1
#define BITL0  2
#define BITL1  3
#define BITL2  4

bool led_state = false;

void setup() {
    // L0, L1, L2 are input
    DDRB &= ~(1<<BITL0 | 1<<BITL1 | 1<<BITL2);
    // LED is output
    DDRB |= 1<<BITLED;

    // turn off LED
    PORTB & ~(1<<BITLED);
}

void loop() {
    // 10% (all off) -> blink
    if (!(PINB & (1<<BITL0 | 1<<BITL1 | 1<<BITL2))) {
        if (led_state)
            PORTB &= ~(1<<BITLED);
        else 
            PORTB |= 1<<BITLED;

        delay(1000);
        led_state = !led_state;
    }
    // 80% (L1 and L2 on) -> turn on
    else if ((PINB & 1<<BITL1) && (PINB & 1<<BITL2)) {
        PORTB |= 1<<BITLED;
        led_state = true;
    }
    // none of the two -> turn off
    else {
        PORTB &= ~(1<<BITLED);
        led_state = false;
    }
}
