#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDR 0x02

#define P_SDA A4
#define P_SCL A5


void setup()
{
    Wire.begin();
    Serial.begin(115200);
}

void loop()
{
     Serial.println("[Starting Send]");
     
     Wire.beginTransmission(SLAVE_ADDR);
     
     Wire.write(SLAVE_ADDR);
     Wire.write(0x10);
     Wire.write(0x03);
     
     Wire.endTransmission();
     
     Serial.println("[Starting Read]");
     
     Wire.requestFrom(SLAVE_ADDR, 6);
     
     if (Wire.available()) {
          char c = Wire.read();
          Serial.print(c);
     }
     else {
          Serial.print("[Unavailable]");
     }
     
     Serial.println("");
}