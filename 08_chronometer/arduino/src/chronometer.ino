#include <Arduino.h>

#define P_BUTTON 4

unsigned long time_start, time_millis;
double time_seconds;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (digitalRead(P_BUTTON) == HIGH) {
        while (digitalRead(P_BUTTON) == HIGH);

        time_start = millis();

        while (digitalRead(P_BUTTON) == LOW) {
            time_millis = millis() - time_start;
            time_seconds = time_millis / 1000;

            Serial.print("Current Time:");
            Serial.println(time_seconds, 3);
        }
    }

    delay(500);
}
