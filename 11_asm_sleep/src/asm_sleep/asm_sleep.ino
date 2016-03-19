#include <Arduino.h>

void sleepMicro(int t)
{
    asm volatile (
        "ldi r16, %%r;\n"
        ".sleep:\n"
            "ldi r18, 5;\n"
            ".delay:\n"
                "dec r18;\n"
                "brne .delay;\n" // z flag <> 0
        "dec r16;\n"
        "brne .sleep;\n"
        : "=r" (t)
    );
}

void setup()
{
    pinMode(13, OUTPUT);
}

void loop()
{
    digitalWrite(13, HIGH);
    sleepMicro(1000000);
    digitalWrite(13, LOW);
    sleepMicro(1000000);
}
