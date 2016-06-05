attende che `PB1` diventi 1  
```while (!(PINB & 0x01));```

spegne `PB1`  
```PORTB &= ~0x02;```
