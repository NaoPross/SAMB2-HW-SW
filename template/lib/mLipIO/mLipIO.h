/* Esame parziale Elettronico AFC 2016
 * Naoki Pross 2E
 *
 * Description:
 *      This file contains the definitions for the I/O pins used with the custom
 *      Arduino Shield built for the exam. This pin configuration has been
 *      tested with Arduino Uno, Arduino Mega and Arduino MegaADK.
 */

#ifndef _MLIPIO_H_
#define _MLIPIO_H_

/* output pins */
#define DOUT0   0
#define DOUT1   1
#define DOUT2   2
#define DOUT3   3
#define DOUT4   4
#define DOUT5   5
#define DOUT6   6
#define DOUT7   7

/* input pins */
#define DIN0    8
#define DIN1    9
#define DIN2    10
#define DIN3    11
#define DIN4    12
#define DIN5    13
#define DIN6    A0
#define DIN7    A1

/* macros to setup every pin on the bus */
#define SETUP_OUTPUT_PINS( ) \
    do { \
        pinMode(DOUT0, OUTPUT); \
        pinMode(DOUT1, OUTPUT); \
        pinMode(DOUT2, OUTPUT); \
        pinMode(DOUT3, OUTPUT); \
        pinMode(DOUT4, OUTPUT); \
        pinMode(DOUT5, OUTPUT); \
        pinMode(DOUT6, OUTPUT); \
        pinMode(DOUT7, OUTPUT); \
    } while (0);

#define SETUP_INPUT_PINS( ) \
    do { \
        pinMode(DIN0, INPUT); \
        pinMode(DIN1, INPUT); \
        pinMode(DIN2, INPUT); \
        pinMode(DIN3, INPUT); \
        pinMode(DIN4, INPUT); \
        pinMode(DIN5, INPUT); \
        pinMode(DIN6, INPUT); \
        pinMode(DIN7, INPUT); \
    } while (0);

#endif /* _MLIPIO_H_ */
