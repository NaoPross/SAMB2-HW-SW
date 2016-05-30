#define BITS1 0
#define BITS2 1
#define BITS4 2
#define BITLED_GRANDE  3
#define BITLED_MEDIA   4
#define BITLED_PICCOLA 5

uint16_t big = 0, medium = 0, small = 0;

void setup() {
    // input
    DDRB &= ~(1<<BITS1 | 1<<BITS2 | 1<<BITS3);
    // output
    DDRB |= (1<<BITLED_PICCOLA | 1<<BITLED_MEDIA | 1<<BITLED_GRANDE);
}

void loop() {
    // aspetta che passa il prossimo
    while (!(PINB & 1<<BITS1));
    // spegni tutti i led
    PINB &= ~(1<<BITLED_PICCOLA | 1<<BITLED_MEDIA | 1<<BITLED_GRANDE);

    // scatola grande
    if (!(PINB & 1<<BITS3)) {
        PINB |= 1<<BITLED_GRANDE;
        big++;
    }
    // scatola media 
    else if (!(PINB & 1<<BITS2)) {
        PINB |= 1<<BITLED_MEDIA;
        medium++;
    }
    // scatola piccola
    else if (!(PINB & 1<<BITS1)) {
        PINB |= 1<<BITLED_PICCOLA;
        small++;
    }
}
