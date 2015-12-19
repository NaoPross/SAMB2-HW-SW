/* PINS                                     CHEAT SHEET
 * @-----------------------------------@    @--------------@
 * | AtMega2560 PORTC Wiring           |    | Binary | Hex |
 * @-----------------------------------@    @--------------@
 * | Bit | Pin | Connected To | Mode   |    | 0b0000 | 0x0 |
 * @-----------------------------------@    | 0b0001 | 0x1 |
 * |  7  |  30 | 1 chf        | INPUT  |    | 0b0010 | 0x2 | 
 * |  6  |  31 | 50 cts       | INPUT  |    | 0b0100 | 0x5 |
 * |  5  |  32 | 20 cts       | INPUT  |    | 0b1000 | 0x8 |
 * |  4  |  33 | 10 cts       | INPUT  |    |--------|-----|--------------@
 * |-----|-----|--------------|--------|    | 0b1111 | 0xF | 0b0110 | 0x6 |
 * |  3  |  34 | LED RED      | OUTPUT |    | 0b1110 | 0xE | 0b1010 | 0xA |
 * |  2  |  35 | LED BLUE     | OUTPUT |    | 0b1101 | 0xD | 0b1100 | 0xC |
 * |  1  |  36 | LED GREEN    | OUTPUT |    | 0b1011 | 0xB | 0b1110 | 0xE |
 * |  0  |  37 | Buy Coffee   | INPUT  |    | 0b0111 | 0x7 |        |     |
 * @-----------------------------------@    @--------------@--------------@
 * 
 * Data Direction Register C
 * 
 * This register sets the pin mode of every pin connected to the
 * port C. Every bit can be either 0 or 1, to be set as OUTPUT or
 * INPUT.
 *
 * Port C Data Register
 *
 * This register can be used to set the value of every pin connected
 * to the port C. For every bit, 1 will turn the output on 0 will turn
 * it off.
 * 
 * Port C Input Pins Address
 *
 * This register contains the actual value measured on the port C.
 */

#include <Arduino.h>

#define COFFEE_PRICE 130


int credit, prev_status;

void blink(int, int, int);

void setup() {
#ifdef DEBUG
	Serial.begin(9600);
#endif

    DDRC = 0x0E;                // Set INPUT and OUTPUT Pins
    PORTC = PINC & 0xF6;        // Turn on LED RED

    prev_status = 0x00;
	credit = 0;
}

void loop() {
    
    // Ignore the output ports value
    int input_status = PINC & 0xF1;

#ifdef DEBUG
    Serial.print("PinC: ");
    Serial.println(input_status, BIN);
    Serial.print("Credit: ");
    Serial.println(credit);
#endif

    if (input_status != prev_status) {
        switch(input_status) {
        case 0x10:
            credit += 10;
            break;
            
        case 0x20:
            credit += 20;
            break;

        case 0x40:
            credit += 50;
            break;

        case 0x80:
            credit += 100; 
            break;
            
        case 0x01:
            if (credit >= COFFEE_PRICE) {
                blink(0xFA, 4, 250);
                credit -= COFFEE_PRICE;
            }
            else {
                blink(0xF6, 4, 250);
            }
            break;
        }
        
        if (credit >= COFFEE_PRICE) {
            blink(0xFC, 1, 5);              // Blink is used to set the color
        }
        else {
            blink(0xF6, 1, 5);
        }
    } 

    prev_status = input_status;
    delay(250);
}

void blink(int color, int times, int _delay) {
    for (int i = 0; i < times; i++) {
        PORTC = PINC | 0x0E;
        delay(_delay);
        PORTC = PINC & color;
        delay(_delay);
    }
}
