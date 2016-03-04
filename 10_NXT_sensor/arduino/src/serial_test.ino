#include <Arduino.h>
#include <Wire.h>


void setup()
{
    Wire.begin();
    Serial.begin(9600);
}

void loop()
{
    Serial.println("Starting Send");

    Wire.beginTransmission(0x01);
    Wire.write(0x02);
    Wire.write(0x00);
    Wire.write(0x03);
    Wire.endTransmission();

    Serial.println("Starting Read");
    Wire.requestFrom(0x01, 1);

    if (Wire.available()) {
        char b = Wire.read();
        char next[3];

        if (b == 0x56) {
            Serial.print("Got a 0x56\n");

            for (int i = 0; i < 3; i++) {
                Wire.requestFrom(0x01, 1);
                if (Wire.available()) {
                    next[i] = Wire.read();
                }
                else {
                    break;
                }
            }

            Serial.println(next);
        }
        else {
            Serial.print("Got ");
            Serial.println(b, HEX);
        }
    }

    delay(500);
}
