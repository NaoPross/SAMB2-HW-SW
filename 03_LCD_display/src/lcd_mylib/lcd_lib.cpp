#include "lcd_lib.hpp"

void init_display(int pin_data[], int pin_enable, int pin_rs, int pin_rw)
{
    for (int i = 0; i < 8; i++) {
        d_pin_data[i] = pin_data[i];
    }
    d_pin_enable = pin_enable;
    d_pin_rs     = pin_rs;
    d_pin_rw     = pin_rw;

    // Function Set
    digitalWrite(d_pin_enable, HIGH);
    
}

void write_text(const char* text)
{
    for (int i = 0; text[i] != '\0'; i++) {
        
    }
}

void send_byte(int data)
{
    for (int i = 0; i < 8; i++) {
        
    }
}
