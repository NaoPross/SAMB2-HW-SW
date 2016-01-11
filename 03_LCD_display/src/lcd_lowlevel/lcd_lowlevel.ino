#define D_TIME 250

//                84218421
#define ENABLE  0b00010000
#define RW      0b00100000
#define RS      0b01000000
#define DISABLE 0b00000000

void setup()
{
    // ARDUINO SETUP
    // Serial Log
    Serial.begin(9600);
    delay(1000);

    // Data Bus
    DDRC = 0xFF;
    /** CONTROL BUS
     * 
     * Enable : 0x40
     * RW     : 0x20
     * RS     : 0x10
     */
    DDRA = 0x70;


    // LCD SETUP
    // Function Set 
    PORTA = ENABLE;
    delay(D_TIME);
    PORTC = 0x38;
    delay(D_TIME);
    PORTA = DISABLE;
    delay(D_TIME);
    PORTC = 0x00;

    // Turn ON
    PORTA = ENABLE;
    delay(D_TIME);
    PORTC = 0x0E;
    delay(D_TIME);
    PORTA = DISABLE;
    delay(D_TIME);
    PORTC = 0x00;

    // Entry Mode Set
    PORTA = ENABLE;
    delay(D_TIME);
    PORTC = 0x06;
    delay(D_TIME);
    PORTA = DISABLE;
    delay(D_TIME);
    PORTC = 0x00; 

    // PROGRAM
    // Write 'W'
    PORTA = ENABLE | RS;
    delay(D_TIME);
    PORTC = 0x57; 
    delay(D_TIME);
    PORTA = DISABLE | RS;
    delay(D_TIME);
    PORTC = 0x00;
}

void loop()
{
    delay(1000);
}
