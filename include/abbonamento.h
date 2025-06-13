#ifndef ABBONAMENTO_H
#define ABBONAMENTO_H

#include "cliente.h"

// Definizione della struttura Abbonamento, che gestisce i dati dell'utente iscritto e il suo abbonamento
typedef struct Abbonamento {
    int id_cliente; // Identificativo univoco del cliente
    char tipo[20]; // Tipologia dell'abbonamento
    char data_inizio[11]; // Data in cui inizia l'abbonamento in formato "gg/mm/aaaa" (max 10 caratteri)
    char data_fine[11];  // Data in cui finisce l'abbonamento in formato "gg/mm/aaaa" (max 10 caratteri)
    struct Abbonamento* next; // Puntatore di tipo Abbonamento per scorrere la lista
} Abbonamento; 

int stato_abbonamento(const char *data_inizio, const char *data_fine, const char *data_oggi);
/*
* Funzione: crea_abbonamento
* ----------------------------------
* Crea un nuovo abbonamento per un cliente esistente, richiedendo dati all’utente
* (tipo, data inizio, data fine) e aggiunge il nuovo abbonamento all’inizio della lista.
*
* Parametri:
*   abbonamenti: puntatore alla testa della lista degli abbonamenti esistenti.
*   clienti: puntatore alla lista dei clienti registrati.
*
* Pre-condizione:
*   La lista dei clienti deve essere inizializzata (può anche essere vuota).
*   L’utente deve fornire un ID cliente valido e già presente nella lista.
*   I dati richiesti (tipo, data inizio, data fine) devono essere forniti in formato corretto.
*
* Post-condizione:
*   Se tutti i dati sono validi, viene creato un nuovo nodo 'Abbonamento'.
*   Il nuovo abbonamento viene inserito all'inizio della lista degli abbonamenti.
*   Se l’input è errato o il cliente non esiste, la funzione non modifica la lista.
*
* Ritorna:
*   Il puntatore alla nuova testa della lista 'Abbonamento', eventualmente aggiornata.
*/
Abbonamento* crea_abbonamento(Abbonamento* abbonamenti, Cliente* clienti);

/*
* Funzione: gestisci_abbonamento
* ----------------------------------
* Cerca e gestisce l’abbonamento di un cliente dato il suo ID e mostra lo stato attuale
* (non ancora attivo, attivo, scaduto) in base alla data odierna inserita dall’utente, 
* offrendo poi anche la possibilità di cancellarlo.
*
* Parametri:
*   head: puntatore alla testa della lista degli abbonamenti.
*   id_cliente: ID del cliente di cui si vuole verificare o cancellare l’abbonamento.
*
* Pre-condizione:
*   La lista può essere vuota o contenere più abbonamenti.
*   L’ID del cliente deve essere un numero intero positivo.
*   L’utente deve fornire una data valida nel formato gg/mm/aaaa per il confronto.
*
* Post-condizione:
*   Se esiste un abbonamento associato al cliente, si mostrano le sue informazioni.
*   Il sistema richiede la data odierna e valuta lo stato tra 'non ancora attivo' (0), 
*   'attivo' (1) e 'scaduto' (2). 
*   L’utente può decidere se cancellare l’abbonamento e in tal caso il nodo viene rimosso e liberato. 
*   Se nessun abbonamento è associato al cliente, viene mostrato un messaggio.
*
* Ritorna:
*   Il puntatore alla testa aggiornata della lista 'Abbonamento', eventualmente modificata.
*/
Abbonamento* gestisci_abbonamento(Abbonamento *head, int id_cliente);

/*
* Funzione: visualizza_abbonamento
* ---------------------------------
* Visualizza tutti gli abbonamenti attivi presenti nella lista.
* Per ogni abbonamento mostra le relative informazioni.
*
* Parametri:
*  head: puntatore alla testa della lista degli abbonamenti.
*
* Pre-condizione:
*  La lista degli abbonamenti deve essere inizializzata (può essere vuota).
*
* Post-condizione:
*  Nessuna modifica alla lista o agli abbonamenti.
*  Viene stampata a schermo la lista degli abbonamenti.
*
* Ritorna:
*   Nessun valore di ritorno, essendo di tipo void. 
*/
void visualizza_abbonamento(Abbonamento* head);

#endif
