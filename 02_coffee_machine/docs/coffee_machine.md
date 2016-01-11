# Macchina del caffé con Aruno Mega ADK
*Naoki Pross 2B/E*

## Elettronica
Purtroppo la piastra sperimentale aveva delle limitayzioni fisiche in quanto
dimensioni, quindi non era possibile far stare tutti i bottoni per una macchina
del caffé con fuzionalità completa.

## Software
### Funzionalità
La mancanza di spazio sulla piastra sperimentale non ha permesso di aggiungere
un tasto per poter richiedere il resto.

Azioni possibili dalla macchina:

  - Bottoni per simulare le monete da 1 CHF, 50 CTS, 20 CTS, 10 CTS
  - Bottone per richiedere il caffé
  - LED RGB che indica lo stato nel seguente modo:
    - ROSSO: Il credito non è sufficiente
    - VERDE: Il credito è sufficiente
    - BLU  : Preparazione in corso

### Codice 
Per comprendere meglio in funzionamento del Chip ad un livello più basso
ho evitato di utilizzare le funzioni di alto livello fornite da Arduino.
Quindi ho usato l'accesso normale alla porta C, dividendo in due parti il byte,
la prima per leggere lo stato dei bottoni per simulare la moneta,
e la seconda per controllare il LED RGB e il bottone per acquistare il caffé.

Tabella della porta C:

| Bit | Pin | Connected to | Mode   |
|----:|----:|:-------------|:-------|
|  7  |  30 | 1 chf        | INPUT  |
|  6  |  31 | 50 cts       | INPUT  |
|  5  |  32 | 20 cts       | INPUT  |
|  4  |  33 | 10 cts       | INPUT  |
|  3  |  34 | LED Red      | OUTPUT |
|  2  |  35 | LED Blue     | OUTPUT |
|  1  |  36 | LED Green    | OUTPUT |
|  0  |  37 | Buy Coffee   | INPUT  |

Inoltre essendo molto rapido il controllo dello stato dei bottoni,
ho potuto rendere il sistema non bloccante per rendere il software piu
realistico.

Questo meccanismo viene controllato da un condizionale all'inizio del loop
```C++
void loop()
{
  int input_status = PINC & 0xF1;
  if (input_status != prev_status) {
    ...
    prev_status = input_status;
  }
}
```

Il resto del codice si trova al git *samb2_hw_and_sw* nel mio profilo su
GitHib.
