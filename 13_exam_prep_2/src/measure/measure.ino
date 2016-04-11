/*
    Naoki Pross 2B, 4.4.2016
    
    NOTE:
    This program must be compiled for Arduino Mega 2560 or Mega ADK.
    
    Complie w/
    `$ arduino --verify --board arduino:avr:megaADK`
 */

#include <avr/delay.h>

/* OUTPUT PORT CONFIGURATION */
#define PORT_OUT_DDR DDRC   // AVR Data Direction Register
#define PORT_OUT_PIN PINC   // AVR Pins Input Register
#define PORT_OUT_REG PORTC  // AVR Pins Output Register

// Output Devices / Jumpers
#define DISPLAY 0x0F
#define RESET   0x10
#define TRIGGER 0x20

/* INPUT PORT CONFIGURATION */
#define PORT_IN_DDR DDRA    // Same as above  GAYYYYYYY Z E Y SONO SWAPPATI 
#define PORT_IN_PIN PINA
#define PORT_IN_OUT PORTA

// Input Jumpers
#define PAUSE 0x01
#define CLOCK 0x02
#define STAB  0x04
#define DUTY  0x08
#define S7    0x40

void wait_s7() {
    while (!(PORT_IN_PIN & S7));
    while (PORT_IN_PIN & S7);
}

void setup() {
    PORT_OUT_DDR |= (DISPLAY | RESET | TRIGGER);
    PORT_IN_DDR |= ~(PAUSE | CLOCK | STAB | DUTY);
}

void loop() { 
    /* Implementazione 7.3.1 [accensione] */        
    // Wait until STAB goes UP
    while (!(PORT_IN_PIN & STAB));
    
    for (uint8_t i = 1; i <= 0xF ; i++) {
        PORT_OUT_REG |= i & DISPLAY; // show i
        _delay_ms(500);
        PORT_OUT_REG &= ~DISPLAY;    // turn off
    }
    wait_s7();
    
    /* Implementazione 7.3.2 [controllo clock] */
    uint16_t clk_count = 0;
    
    PORT_OUT_REG |= 8 & DISPLAY;
    
    while (clk_count <= 2000) {
        while (!(PORT_IN_PIN & CLOCK));
        while (PORT_IN_PIN & CLOCK);
        clk_count++;
    }
    
    PORT_OUT_REG &= ~DISPLAY;
    PORT_OUT_REG &= 0xF & DISPLAY;
    
    while (clk_count <= 4000) {
        while (!(PORT_IN_PIN & CLOCK));
        while (PORT_IN_PIN & CLOCK);
        clk_count++;
    }
    
    wait_s7();
    
    /* Implementazione 7.3.3 [misurazione] */
    do {
        uint16_t clk_count_t[] = {0, 0};
        
        for (uint8_t i = 0; i < 2; i++) {
            while (!(PORT_IN_PIN & DUTY));
            while (PORT_IN_PIN & DUTY) {
                while (!(PORT_IN_PIN & CLOCK));
                while (PORT_IN_PIN & CLOCK);
                clk_count_t[i]++;
            }
        }
    } while (PORT_IN_PIN & S7); 
}
