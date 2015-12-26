/* Naoki Pross 11.2015
 * 
 * This program is combined with a breadboard
 * with a set of buttons and a speaker.
 * The microcontrolles does the job to generate
 * the right frequency at the right port when a
 * button is pressed in order to output a tone.
 *
 * WIRING:
 * The pin set as PIN_BTN_START has to be the lowest
 * key that produces the lowest sound.
 */

#include <Arduino.h>

#define PIN_BTN_START 2
#define PIN_BTN_END 5
#define PIN_BTN_SHIFT 6
#define PIN_SPEAKER 7
#define SLEEP_TIME 75

const int keyboard_lenght = PIN_BTN_END +1 - PIN_BTN_START;
const int frequencies[] = {
    262,        // C4   Do
    294,        // D4   Re
    330,        // E4   Mi
    349,        // F4   Fa
    392,        // G4   Sol
    440,        // A4   La
    494,        // B4   Si
    523         // C5   Do
};

int i, keyb_prev_state[] = {0, 0, 0, 0}; 

void log_array(int[], char*, int);
void log_data(int, char*);
void log_data(int, char*, char*);
void copy_array(int*, int*, int);

void setup()
{
    Serial.begin(9600);
    
    for (i = PIN_BTN_START; i <= PIN_BTN_END; i++) {
        pinMode(i, INPUT);
    }
    pinMode(PIN_BTN_SHIFT, INPUT);
    pinMode(PIN_SPEAKER, OUTPUT);
}

void loop()
{
    int shift_state = digitalRead(PIN_BTN_SHIFT);
    int keyb_state[keyboard_lenght];

    // Read every value and stores it into the array
    for (i = PIN_BTN_START; i <= PIN_BTN_END; i++) {
        keyb_state[i - PIN_BTN_START] = digitalRead(i);
    }

    log_array(keyb_state, "keyb_state", keyboard_lenght);
    log_array(keyb_prev_state, "prev_state", keyboard_lenght);
    log_data(shift_state, "shift_state");

    for (i = 0; i < keyboard_lenght; i++) {
        // if something has changed
        if (keyb_state[i] != keyb_prev_state[i]) {      
            if (keyb_state[i] == HIGH) {
                int freq = (shift_state == LOW) ? frequencies[i] : frequencies[i + keyboard_lenght];
                tone(PIN_SPEAKER, freq);
                log_data(freq, "curr_freq", "Hz");
            }
            else {
                noTone(PIN_SPEAKER);
            }
            
            copy_array(keyb_state, keyb_prev_state, keyboard_lenght);
        }
    }

    Serial.println("-----------------------------");
    delay(SLEEP_TIME);
}

void log_array(int arr[], char* title, int size)
{
    Serial.print(title);
    Serial.print(":\t[");
    
    for (i = 0; i < size; i++) {
        Serial.print(arr[i]);

        if (i < size -1) {
            Serial.print(", ");
        }
    }

    Serial.println("]");
}

void log_data(int value, char* title)
{
    log_data(value, title, "");
}

void log_data(int value, char* title, char* unit)
{
    Serial.print(title);
    Serial.print(":\t");
    Serial.print(value);
    Serial.println(unit);
}

void copy_array(int* input, int* output, int size)
{
    for (i = 0; i < size; i++) {
        output[i] = input[i];
    }
}
