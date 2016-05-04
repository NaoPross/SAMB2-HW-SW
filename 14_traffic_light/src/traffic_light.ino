#include <Arduino.h>
#include <avr/delay.h>

// time
#define T1 70
#define T2 77
#define T3 147
#define T4 154

/* Definitions of traffic lights on PORT C
 * 
 * TL_A  : Mask for traffic light A
 * TL_AR : Bit for RED on TR_A
 * TL_AY : Bit for YELLOW on TR_A
 * TL_AG : Bit fot GREEN on TR_A
 */
#define TL_AR 5
#define TL_AY 4
#define TL_AG 3
#define TL_A (1<<TL_AR | 1<<TL_AY|  1<<TL_AG)

#define TL_BR 2
#define TL_BY 1
#define TL_BG 0
#define TL_B (1<<TL_BR | 1<<TL_BY|  1<<TL_BG)

// On PORT A
#define TL_ON 0 

void setup() {
    DDRC |= TL_A | TL_B;
    DDRC &= ~(1<<TL_ON);
}

void loop() {
    // if PA0 is LOW, blink at .5 Hz
    while (!(PINA & 1<<TL_ON)) {
        PORTC |= 1<<TL_AY | 1<<TL_BY;
        _delay_ms(1000);
        PORTC &= ~(1<<TL_AY | 1<<TL_BY);
        _delay_ms(1000);
    }
    
    PORTC &= 0;   
    // `t` counts how many seconds have passed
    for (uint16_t t = 0; t <= T4; t++) {
    
        // PORTC |= (t < T2) ? 1<<TL_AR : 1;
        // Traffic Light A RED (TL_AR)
        if (t < T2) {
            PORTC |= 1<<TL_AR;
        }
        
        // Traffic Light A YELLOW (TL_AY)
        if (T3 <= t && t < T4) {
            PORTC |= 1<<TL_AY;
        }
        
        // Traffic Light A GREEN (TL_AG)
        if (T2 <= t && t < T3) {
            PORTC |= 1<<TL_AG;
        }
        
        // Traffic Light B RED (TL_BR)
        if (T2 <= t && t < T4) {
            PORTC |= 1<<TL_BR;
        }
        
        // Traffic Light B YELLOW (TL_BY)
        if (T1 <= t && t < T2) {
            PORTC |= 1<<TL_BY;
        }
        
        // Traffic Lifht B GREEN (TL_BG)
        if (t < T1) {
            PORTC |= 1<<TL_BG;
        }
        
        // Wait for 1 Second
        _delay_ms(1000);
        // Reset, everything will be turned back on with the next iteration
        PORTC &= 0;
    }
}
