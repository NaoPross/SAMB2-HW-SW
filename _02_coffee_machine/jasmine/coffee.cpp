/* Ho corretto il codice e ho aggiunto alcuni commenti
 * i commenti che iniziano con "CORR:" sono delle correzioni
 * o delle spiegazioni sulla correzione. Mentre gli altri sono
 * per me per capire.
 *
 * Comunque é un buon lavoro C;
 */

#define PIN_LED_RED 22
#define PIN_LED_GREEN 23
#define PIN_LED_BLUE 24
#define PIN_LED_CAFFE 25
#define PIN_LED_THE 26

#define TASTO_CAFFE 30
#define TASTO_THE 31
#define TASTO_RESTO 40

#define UNFR 32
#define CINQUANTACT 33
#define VENTICT 34
#define DIECICT 35

#define COSTO_CAFFE 1.20
#define COSTO_THE 1.10

#define SLEEP_UNO 1000
#define SLEEP_DUE 4000

/* CORR: Le seguenti variabili non sono necessarie
 *       perché sono dirchiarate localmente.
 *       
 *       int led;
 *       float moneta_mancante, resto, costo;
 *       char bevanda;
 *       
 *       La seguente variabile non é necessaria
 *      
 *       int scelta;
 */

float conto;

/* CORR: Solitamente si mette le funzioni alla fine dopo il
 *       programma principale, quindi nel nostro caso dopo
 *       il setup() e il loop(), ma non é importantissimo,
 *       é solo per rendere il tutto più comprensibile.
 */

void procedimento (char* bevanda) {
  // CORR: Si possono creare delle variabili dette LOCALI
  int led;
  float moneta_mancante, resto, costo;

  if (bevanda == "caffe") {
    costo = COSTO_CAFFE;
    led = PIN_LED_CAFFE;

  } else if (bevanda == "the") {
    costo = COSTO_THE;
    led = PIN_LED_THE;
  }

  Serial.print("Ha scelto il ");
  Serial.println(bevanda);
  digitalWrite(led, HIGH);

  if (conto >= costo) {
    // Preparazione Bevanda
    digitalWrite(PIN_LED_GREEN, LOW);
    delay(SLEEP_UNO);
    digitalWrite(PIN_LED_GREEN, HIGH);
    Serial.println("Bevanda in preparazione");
    digitalWrite(PIN_LED_BLUE, LOW);
    delay(SLEEP_DUE);
    digitalWrite(PIN_LED_BLUE, HIGH);
    digitalWrite(led, LOW);
    Serial.println("Ora e possibile prendere la bevanda");

    // Modifica del conto
    conto -= costo;
    Serial.print("Il suo conto attuale e di ");
    Serial.print(conto);
    Serial.println(" Fr");

    // if (conto == 0) {

    // CORR: In qualsiasi caso l'utente devei premere il tasto resto per terminare
    //       gli acquisti

    Serial.println("Se ha terminato gli acquisti la preghiamo di premere il tasto resto");

    /* CORR: In questo caso la persona dovrebbe poter comperare
     *       ancora qualcos'altro se vuole, quindi il resto non
     *       deve essere ancora calcolato. 
     *
     *       Codice che c'era qua:
     * 
     *       } else if (conto > costo) {
     *        resto = conto - costo;
     *
     *        if (digitalRead(TASTO_RESTO) == HIGH) {
     *          Serial.println("Prego ritirare il resto");
     *          Serial.print("RESTO = ");
     *          Serial.println(resto);
     *          resto = 0;
     *        }
     *      }
     */  

  // Se non ci sono abbastanza soldi e il conto non é 0
  } else if (conto != 0) {
    moneta_mancante = costo - conto;
    mancanza_credito (moneta_mancante);
  }
}

/* CORR: Modificando in questo modo si generalizza lo scopo della funzione
 *       Inoltre questa funzione viene utilizzata una volta sola, non ha molto
 *       senso poiché non elimina alcuna riperizione ma ok.
 */
void mancanza_credito (float moneta_mancante) {
  Serial.println("Spiacenti, conto insufficente. Inserire altra moneta");
  Serial.print("Mancano ");
  Serial.print(moneta_mancante);
  Serial.println("Fr");

  // Lampeggia il LED_RED
  digitalWrite(PIN_LED_RED, LOW);
  delay(SLEEP_UNO);
  digitalWrite(PIN_LED_RED, HIGH);
  delay(SLEEP_UNO);
  digitalWrite(PIN_LED_RED, LOW);
  delay(SLEEP_UNO);
  digitalWrite(PIN_LED_RED, HIGH);
}

// CORR: Ho cambiato il nome per capire a cosa serve
void mostra_credito () {
  Serial.print("Il suo conto e di ");
  Serial.print(conto);
  Serial.println("Fr.");
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_CAFFE, OUTPUT);
  pinMode(PIN_LED_THE, OUTPUT);
  
  pinMode(TASTO_CAFFE, INPUT);
  pinMode(TASTO_THE, INPUT);
  pinMode(UNFR, INPUT);
  pinMode(CINQUANTACT, INPUT);
  pinMode(VENTICT, INPUT);
  pinMode(DIECICT, INPUT);

  // CORR: Il digitalWrite può essere usato solo dopo aver
  //       initializzato il pin com pinMode()
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_BLUE, HIGH);
 
  conto = 0;
}

void loop() {
  // CORR: Mi pare si può usare i classici caratteri ASCII tipo \t o \n
  Serial.println("\n\nSe desidera vedere i prezzi schiacciare il pulsante corrispondente\n\n");

  // Aspetta finché non inserisce della moneta, e se premuti i bottoni delle bibite: mostra il prezzo 
  while (digitalRead(UNFR) == LOW && digitalRead(CINQUANTACT) == LOW && digitalRead(VENTICT) == LOW && digitalRead(DIECICT) == LOW) {

    if (digitalRead(TASTO_CAFFE) == HIGH) {
      Serial.print("Il caffe costa ");
      Serial.println(COSTO_CAFFE);
      Serial.println("");

      while (digitalRead(TASTO_CAFFE) == HIGH);
      
    } else if (digitalRead(TASTO_THE) == HIGH) {
      Serial.print("Il the costa ");
      Serial.println(COSTO_THE);
      Serial.println("");

      while (digitalRead(TASTO_THE) == HIGH);
    }
  }

  // Finché non viene richiesto il resto
  while (digitalRead(TASTO_RESTO) == LOW) {

    if (digitalRead(UNFR) == HIGH) {
      conto += 1;
      mostra_credito();
      while (digitalRead(UNFR) == HIGH);
    }
    
    if (digitalRead(CINQUANTACT) == HIGH) {
      conto += 0.5;
      mostra_credito();
      while (digitalRead(CINQUANTACT) == HIGH);
    }
    
    if (digitalRead(VENTICT) == HIGH) {
      conto += 0.2;
      mostra_credito();
      while (digitalRead(VENTICT) == HIGH);
    }
    
    if (digitalRead(DIECICT) == HIGH) {
      conto += 0.1;
      mostra_credito();
      while (digitalRead(DIECICT) == HIGH);
    }   

    if (digitalRead(TASTO_CAFFE) == HIGH) {
      digitalWrite(PIN_LED_THE, LOW);
      procedimento("caffe");

    } else if (digitalRead(TASTO_THE) == HIGH) {
      digitalWrite(PIN_LED_CAFFE, LOW);
      procedimento ("the");
    }
  }

  /* CORR: Questo if non serve perché se il programma
   *       é arrivato qui vuol dire che il tasto TASTO_RESTO
   *       é stato premuto per forza poiché é l'unica condizione
   *       che interrompe il while qui sopra.
   *       
   *       if (digitalRead(TASTO_RESTO) == HIGH) {
   */
  if (conto == 0) {
    Serial.println("\nArrivederci!");

  } else {
    Serial.print("\nPrego, ritiri i suoi ");
    Serial.print(conto);
    Serial.println(" Fr");
    Serial.println("Arrivederci!");

    conto = 0;
  }
  while (digitalRead(TASTO_RESTO) == HIGH);

  // Reset
  conto = 0;
}
