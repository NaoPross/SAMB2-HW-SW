#include <Arduino.h>

// Main Program DEFINES
#define T_CLK 500
#define P_SENSOR   A0

// LCD Lib communication DEFINES
#define D_TIME     4
#define D_ROWS     2
#define D_COLUMNS 16

#define B_ENABLE 0b00100000
#define B_RW     0b01000000
#define B_RS     0b10000000

/*****************************************************************************
 *                                                                           *
 * LCD COMUNICATION FUNCTIONS                                                *
 *                                                                           *
 * These functions are written to work using the port C and A                *
 * of the ATmega2560.                                                        * 
 *                                                                           *
 * In this program the ports are used in the following way                   *
 *                                                                           *
 * PORT A : Ouput Data Bus to the LCD Display                                *
 * PORT C : LCD RS, RW, E Controller and Photoresistors Reader               *
 *                                                                           *
 *****************************************************************************/

void c_enable(bool value)
{
    PORTC = (value) ? PINC | B_ENABLE : PINC & ~B_ENABLE;
}

void c_rw(bool value)
{
    PORTC = (value) ? PINC | B_RW : PINC & ~B_RW;
}

void c_rs(bool value)
{
    PORTC = (value) ? PINC | B_RS : PINC & ~B_RS;
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

bool write_LCD(const char* text)
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

/*****************************************************************************
 *                                                                           *
 * MAIN PROGRAM                                                              *
 *                                                                           *
 * Shows the sensor value on the display.                                    *
 *                                                                           *
 *****************************************************************************/

void setup()
{
    DDRA = 0xFF;
    DDRC = 0xE0;;
    PORTA = 0x00;
    PORTC = 0x00;
    
    init_LCD();
    clear_LCD();
    write_LCD("Welcome!");
}

void loop()
{
    int sensor_raw = 1024 - analogRead(P_SENSOR);
    
    String sensor_text = String(sensor_raw);

    clear_LCD();
    write_LCD("Sensor: ");
    write_LCD(sensor_text.c_str());
    delay(T_CLK);
}
