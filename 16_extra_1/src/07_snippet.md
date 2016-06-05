**Consegna: spiega cosa fanno le istruzioni sottostanti**

Controlla se il bit 6 è spento.   
```if((PINB & 0x40) == 0) {```

Se è spento lo accende  
```   PORTB = PORTB | 0x40;```  
```} else {```  

spegne il bit 6.  
```   PORTB = PORTB & ~0x40;```  
```}```
