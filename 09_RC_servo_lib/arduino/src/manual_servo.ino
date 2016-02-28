#include <Arduino.h>

#define PIN_PWM 7
#define PIN_SENSOR A0

// human readable config, in milliseconds
#define C_PERIOD 20.0
#define C_PULSE_MAX 2.5     // 180 deg
#define C_PULSE_MIN 0.5     //   0 deg

// Corret the times
const double PERIOD = C_PERIOD / 1000;

const double PULSE_MIN = C_PULSE_MIN / 1000;
const double PULSE_MAX = C_PULSE_MAX / 1000;
const double PULSE_DELTA = (C_PULSE_MAX - C_PULSE_MIN) / 1000;

/* Function Arguments
 *      angle is given in degrees between 0 and 180 
 *      keepTime is for how long the servo should keep the angle, in seconds
 */
int rcServoAngle(int angle, double keepTime)
{
    // Check if the arg is valid
    if (angle < 0 || angle > 180) {
        return -1;
    }

    bool skip = false;
        
    if (keepTime >= 0) {
        skip = true;
    }

    double pulse = PULSE_MIN + angle/180.0 * PULSE_DELTA;
    unsigned long runtime_start = millis();

    while (!skip && millis() - runtime_start < keepTime * 1000) {
        unsigned long start_time = micros();

        digitalWrite(PIN_PWM, HIGH);
        while (micros() - start_time <= pulse * 1000000);

        digitalWrite(PIN_PWM, LOW);
        while (micros() - start_time <= PERIOD * 1000000);

        // disabled for better performance and precision
        // Serial.print("RAN w/ start_time=");
        // Serial.print(start_time);
        // Serial.print(" pulse=");
        // Serial.print(pulse, 6);
        // Serial.print(" period=");
        // Serial.println(PERIOD);
    }

    // ran without errors
    return 0;
}

void setup()
{
    Serial.begin(9600);
    pinMode(PIN_PWM, OUTPUT);
    // set a starting position
    rcServoAngle(0, 0);
}

void loop()
{
    int sensor_raw = analogRead(PIN_SENSOR);
    double sensor_deg = sensor_raw/1024.0*180;

    rcServoAngle(sensor_deg, 0.2);
}
