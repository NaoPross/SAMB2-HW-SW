#ifndef LCD_LIB_HPP
#define LCD_LIB_HPP

#include "Arduino.h"

#define D_TIME 3


int d_pin_data[8];
int d_pin_enable;
int d_pin_rs;
int d_pin_rw;

void init_display(int[8], int, int, int);
void write_text(const char*);

void sent_byte(int);

#endif
