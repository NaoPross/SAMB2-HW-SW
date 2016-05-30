// on PORT B
// fine corsa
#define BITCSUP 0
#define BITCINF 1
// pulsante
#define BITBTN  2

// on PORT D
// motore
#define BITMUP  0 // salire
#define BITMDW  1 // scendere


bool door_open;

void setup() {
    DDRB &= ~(1<<BITCSUP | 1<<BITCINF | 1<<BITBTN);
    DDRD |= (1<<BITMUP | 1<<BITMDW);

    PORTD |= 1<<BITMDW;
    while (!(PINB & 1<<BITCINF));
    PORTD &= ~(1<<BITMDW);

    door_open = false;
}

void loop() {
    // wait for a buttonpress
    while (!(PINB & 1<<BITBTN)); 
    
    if (door_open) {
        PORTD |= 1<<BITMDW;
        while (!(PINB & 1<<BITCINF));
        PORTD &= ~(1<<BITMDW);
    }
    else {
        PORTD |= 1<<BITMUP;
        while (!(PINB & 1<<BITCSUP));
        PORTD &= ~(1<<BITMUP);
    }

    door_open = !door_open;
}
