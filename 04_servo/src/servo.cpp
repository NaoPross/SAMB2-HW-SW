#include <Arduino.h>

#define D_TIME     4
#define D_ROWS     2
#define D_COLUMNS 16

/** LCD COMUNICATION FUNCTIONS
 *
 * These functions are written to work using the port C and A of
 * the ATmega2560. 
 * 
 * In this program the ports are used in the following way
 *
 * PORT A : Ouput Data Bus to the LCD Display
 * PORT C : LCD RS, RW, E Controller and Photoresistors Reader
 */

void c_enable(bool value)
{
    if (value)
        PORTC = PINC | 0b00100000;
    else
        PORTC = PINC & 0x11011111;
}

void c_rw(bool value)
{
    if (value)
        PORTC = PINC | 0b01000000;
    else
        PORTC = PINC & 0b10111111;
}

void c_rs(bool value)
{
    if (value)
        PORTC = PINC | 0b10000000;
    else
        PORTC = PINC | 0x01111111;
}

void init_LCD()
{
    // 'Function Setup'
    c_enable(true);
    delay(D_TIME);
    
    // FS Command
    PORTA = 0x38;
    delay(D_TIME);
    c_enable(false);

    // 'Display On'
    c_enable(true);
    delay(D_TIME);
    
    // ON Command
    PORTA = 0x0E;
    delay(D_TIME);
    c_enable(false);

    // 'Entry Mode Set'
    c_enable(true);
    delay(D_TIME);

    // EMS Command
    PORTA = 0x06;
    delay(D_TIME);
    c_enable(false);
}

void clear_LCD()
{
    // Clear Command 
    c_enable(true);
    delay(D_TIME);

    PORTA = 0x01;
    delay(D_TIME);
    c_enable(false);
}

// Send arg char to LCD CGRAM
void charto_LCD(char chr)
{
    // Init
    c_enable(true);
    c_rs(true);
    c_rw(false);
    delay(D_TIME);
    // Send
    PORTA = chr;
    delay(D_TIME);
    c_enable(false);
    // Reset
    c_rs(false);
}

bool write_LCD(char* text)
{
    bool success = false;
    for (int i = 0; text[i] != '\0'; i++) {
        if (i > 15) {
            success = false;
            break;
        }
        else {
            charto_LCD(text[i]);
        }
    }

    return success;
}

/** MAIN PROGRAM
 *
 *
 */

void setup()
{
    DDRA = 0xFF;
    DDRC = 0xE0;;
    PORTA = 0x00;
    PORTC = 0x00;
    
    init_LCD();
    clear_LCD();
    write_LCD("Hello World");
}

void loop()
{
    delay(500);
}
