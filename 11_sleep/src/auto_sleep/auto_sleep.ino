#include <Arduino.h>

// Pins
#define P_LED 13
#define P_INTR 12
#define P_INTR_LED 11

// For how many times should the intr led blink
#define INTR_LED_BLINK_TIMES 5

uint32_t cycles = 0;

/* Function void wait(unsigned long t)
 * -> wait function, equivalent of delay() in arduino and _delay_ms() in AVR.
 *
 *      return: nothing (void)
 *      args: t, time to wait in milliseconds
 */
void wait(uint32_t t) {
    for (uint32_t i = 0; i < t; i++) {
        for (uint32_t j = 0; j < cycles; j++) {
            asm volatile("nop"); // does nothing
        }
    }
}

/* Function void interruptHandler(void)
 * -> called when an interruption occurs
 *
 *      return: nothing (void)
 *      args: nothing (void)
 */
void interruptHandler() {
    for (int i = 0; i < INTR_LED_BLINK_TIMES; i++) {
        digitalWrite(P_INTR_LED, HIGH);
        wait(200);
        digitalWrite(P_INTR_LED, LOW);
        wait(200);
    }
}

/* Function void setup(void)
 * -> where the program starts, called by arduino
 *
 *      return: nothing (void)
 *      args: nothing (void)
 */
void setup() {
    // serial setup
    Serial.begin(115200);

    // pins setup
    pinMode(P_LED, OUTPUT);
    pinMode(P_INTR_LED, OUTPUT);

    // setup a status led
    digitalWrite(P_LED, LOW);

    // start of the calibration program
    while (true) {
        uint32_t startTime = micros();

        // 5 milliseconds test
        for (uint32_t i = 0; i < 5; i++) {
            for (uint32_t j = 0; j < cycles; j++) {
                asm volatile("nop");
            }
        }

        uint32_t timeDelta = micros() - startTime;

        if (timeDelta == 5000) {
            Serial.print("Found a valid cycles value: ");
            Serial.println(cycles);
            break;
        }
        else {
            cycles++;
        }
    }

    // show that the setup calibration is completed
    digitalWrite(P_LED, HIGH);

    // enable interrupts
    attachInterrupt(P_INTR, interruptHandler, RISING);
}

// Main loop
void loop() {
    // useless test code
    digitalWrite(P_LED, LOW);
    wait(500);
    digitalWrite(P_LED, HIGH);
    wait(500);
}
