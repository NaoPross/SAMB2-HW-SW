
int precedente = 0;

void setup()
{
    DDRA = 0b00000000;
    // = 0x00
}

void loop()
{
    if (PINA != precedente) {
        precedente = PINA;
        // resto del codice ...
    }
}
