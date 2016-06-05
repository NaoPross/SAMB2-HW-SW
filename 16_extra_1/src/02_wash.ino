// on PORT B
#define MASKSTART 0x01;
#define MASKFILL  0x06;
#define MASKTEMP  0x08;
#define MASKDONE  0x10;

// on PORT D
#define MASKWATER 0x01;
#define MASKW_DIR 0x02;
#define MASKHEAT  0x04;
#define MASKPOWDER 0x08;


void setup() {
    // output
    DDRB &= ~(MASKSTART | MASKFILL | MASKTEMP | MASKDONE);
    // input
    DDRD |= (MASKWATER | MASKW_DIR | MASKHEAT | MASKPOWDER);
}

void loop() {
    // wait for MASKSTART to go up
    while (!(PINB & MASKSTART));
    
    // open sink (and set fill mode)
    PORTD |= (W_DIR | MASKWATER);
    // wait for the sensor
    while (!(PINB & MASKFILL));
    // close sink (and set flush mode)
    PORTD &= ~(W_DIR | MASKWATER);

    // turn on heat
    PORTD |= MASKHEAT;
    // wait for the sensor
    while (!(PINB & MASKTEMP == 6));
    // turn off heat
    PORTD &= ~MASKHEAT;
    
    // add poweder
    PORTD |= MASKPOWDER;
    // wait at least 1 second
    delay(1000);
    // stop powder signal
    PORTD &= ~MASKPOWDER;

    // wait for the sensor
    while (!(PINB & MASKDONE));
    // open sink (already set on fush mode)
    PORTD |= MASKWATER;
}
