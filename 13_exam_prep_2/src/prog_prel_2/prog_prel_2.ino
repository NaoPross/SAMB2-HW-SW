/*
    Naoki Pross 2B, 4.4.2016
    
    NOTE:
    This program must be compiled for Arduino Mega 2560 or Mega ADK.
    
    Complie w/
    `$ arduino --verify --board arduino:avr:megaADK`
 */

#include <Arduino.h>
#include <avr/delay.h>

/* OUTPUT PORT CONFIGURATION */
#define PORT_OUT_DDR DDRC   // AVR Data Direction Register
#define PORT_OUT_PIN PINC   // AVR Pins Input Register
#define PORT_OUT_REG PORTC  // AVR Pins Output Register

#define DISPLAY 0x0F
#define RESET   0x10
#define TRIGGER 0x20

/* INPUT PORT CONFIGURATION */
#define PORT_IN_DDR DDRA    // same as above
#define PORT_IN_PIN PINA
#define PORT_IN_OUT PORTA

#define PAUSE 0x01
#define CLOCK 0x02
#define STAB  0x04
#define DUTY  0x08
#define S7    0x40


void waitS7() {
    while (!(PORT_IN_PIN & S7));
    while (PORT_IN_PIN & S7);
}

void setup() {
    PORT_OUT_DDR |= (DISPLAY | RESET | TRIGGER);
    PORT_IN_DDR |= ~(PAUSE | CLOCK | STAB | DUTY);
}

void loop() {
    // Display "8"
    PORT_OUT_REG |= (8 & DISPLAY);  // & DISPLAY to prevent overwriting
    waitS7();
    PORT_OUT_REG &= ~DISPLAY; // off
    
    // Display "F"
    PORT_OUT_REG |= (0xF & DISPLAY);
    waitS7();
    PORT_OUT_REG &= ~DISPLAY;
}
