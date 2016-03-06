/** SERIAL i2c TEST PROGRAM
 *
 * Naoki Pross 2B/E SAMB HW & SW 2015/16
 *
 */

#include <Arduino.h>
#include <Wire.h>


#define P_SDA 3
#define P_SCL 2


volatile bool scl_changed;
volatile int sda_state, scl_state;

void interrupt_service_routine()
{
    sda_state = digitalRead(P_SDA);
    scl_state = !scl_state;
    scl_changed = true;
}

void setup()
{
    // Wire.begin();
    Serial.begin(115200);
    
    attachInterrupt(
        digitalPinToInterrupt(P_SCL),
        interrupt_service_routine,
        CHANGE
    );

    scl_state = digitalRead(P_SCL);
    scl_changed = false;
}

void loop()
{
    if (scl_changed == true) {
        Serial.print("SDA=");
        Serial.println(sda_state);
        Serial.print("SCL=");
        Serial.println(scl_state);
        scl_changed = false;
    }
}
