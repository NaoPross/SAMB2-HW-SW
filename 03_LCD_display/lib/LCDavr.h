#ifndef _LCDAVR_H_
#define _LCDAVR_H_

#include <avr/delay.h>

class LCDavr {
private:
    /* time required for the LCD to execute an instruction,
     * D_TIME (seconds) > ~ 1/270Hz
     */
    const int D_TIME = 5;

    // data bus and control port
    volatile uint8_t *BUSPORT, *CTLPORT;
    // LCD enable, command/data, read/write
    int E, RS, RW;
    int lines, cols;

    void setup();

public:
    LCDavr(volatile uint8_t* , volatile uint8_t*, int, int, int, int, int);
    // ~LCDavr();

    void put(char);
    int write(char const*);
    int writeLine(char const*);
    void clear();
};

LCDavr::LCDavr(volatile uint8_t *_BUSPORT, volatile uint8_t *_CTLPORT,
    int _E, int _RS, int _RW, int  _lines, int _cols) {
    BUSPORT = _BUSPORT;
    CTLPORT = _CTLPORT;
    E = _E;
    RS = _RS;

    lines = _lines;
    cols = _cols;

    setup();
}

void LCDavr::setup() {
    *CTLPORT |= E;
    _delay_ms(D_TIME);
    *BUSPORT = 0x1C;
    *CTLPORT &= ~(RW | RS | E);
    _delay_ms(D_TIME);
}

void LCDavr::put(char ch) {
    // function set
    *CTLPORT |= (RS | E);
    *CTLPORT &= ~RW;
    *BUSPORT = ch;
    _delay_ms(D_TIME);
    *CTLPORT &= ~E;
}

int LCDavr::write(char const *text) {
    size_t len = strlen(text);

    // text is larger than the size of the display
    if (len > cols) {
        return -1;
    }

    for (int i = 0; i < len; i++) {
        put(text[i]);
    }

    return 0;
}


#endif