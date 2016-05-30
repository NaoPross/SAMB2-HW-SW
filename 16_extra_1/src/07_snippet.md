**Consegna: spiega cosa fanno le istruzioni sottostanti**

`if((PINB & 0x40) == 0) {`
Controlla se il bit 3 è spento.

`PORTB = PORTB | 0x40;`
Se è spento lo accende

`} else {`
altrimenti

`PORTB = PORTB & ~0x40;`
spegne il bit 3.

`}`
