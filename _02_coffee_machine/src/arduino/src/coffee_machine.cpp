/* PINS
 * -------------------------------------
 * | AtMega2560 PORTC Wiring           |
 * -------------------------------------
 * | Bit | Pin | Connected To | Mode   |
 * -------------------------------------
 * |  7  |  30 | 1 chf        | INPUT  | 
 * |  6  |  31 | 50 cts       | INPUT  | 
 * |  5  |  32 | 20 cts       | INPUT  |  
 * |  4  |  33 | 10 cts       | INPUT  |
 * |  3  |  34 | LED RED      | OUTPUT | 
 * |  2  |  35 | LED GREEN    | OUTPUT |  
 * |  1  |  36 | LED BLUE     | OUTPUT | 
 * |  0  |  37 | Stop Serial  | INPUT  | 
 * -------------------------------------
 * 
 * Data Direction Register C
 * 
 * This register contains the value of 
 * 8 bits connected to the port C. Every
 * bit can be set either as 1 or 0, which 
 * will set the pin as either OUTPUT or 
 * INPUT.
 *
 * In this case:
 * DDRC = 0b 0000 1110 = 0x 0 E
 *
 */

#include <Arduino.h>

#define COFFEE_PRICE 130

#define DEBUG 

int credit;

void led_off() {
	PORTC &= 0xF1;
}

void setup() {
	// Serial.begin(9600);
	credit = 0;
    DDRC = 0x0E
}

void loop() {
    // Ignore the output ports value
    int input_status = PORTC & 0xF0;

    switch(input_status) {
    // 0001 0000
    case 0x10:
        credit += 10;
        break;
    // 0010 0000
    case 0x20:
        credit += 20;
        break;
    // 0100 0000
    case 0x50:
        credit += 50;
        break;
    // 1000 0000
    case 0x80:
        credit += 100; 
        break;
    }
    
    // If the credit il higher than the price of the
    // coffee turn on LED n
    PORTC |= (credit >= COFFEE_PRICE) ? 0x05 : PORTC;

}
