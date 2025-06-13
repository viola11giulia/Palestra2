#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include "lezione.h"

// Definizione della struttura Prenotazione, che collega un cliente a una lezione specifica
typedef struct Prenotazione {
int id_cliente; // Identificativo univoco del cliente
int id_lezione; // Identificativo univoco della lezione
struct Prenotazione* next; // Puntatore di tipo Prenotazione per scorrere nella lista 
} Prenotazione; 

/*
* Funzione: gestione_prenotazioni
* ----------------------------------
* Gestisce le prenotazioni effettuate da un cliente specifico, individuato tramite il suo ID.
* La funzione consente all’utente di visualizzare le prenotazioni e scegliere se cancellarle e, in caso di 
* cancellazione, la disponibilità della lezione viene aggiornata correttamente.
*
* Parametri:
*   head: puntatore alla testa della lista delle prenotazioni.
*   id_cliente: ID del cliente di cui si vogliono gestire le prenotazioni.
*   lezioni_head: puntatore alla testa della lista delle lezioni disponibili.
*
* Pre-condizione:
*   La lista delle prenotazioni può essere vuota o contenere una o più prenotazioni.
*   Il parametro id_cliente deve essere un intero positivo.
*   La lista delle lezioni deve essere coerente con gli ID presenti nelle prenotazioni.
*
* Post-condizione:
*   Per ogni prenotazione associata al cliente vengono mostrati i dettagli della lezione collegata (se trovata).
*   L’utente può scegliere se cancellare la prenotazione.
*   Se la prenotazione viene cancellata, i posti occupati della lezione vengono decrementati.
*   Se non sono presenti prenotazioni per il cliente, viene mostrato un messaggio informativo.
*
* Ritorna:
*   Il puntatore alla testa aggiornato della lista delle prenotazioni, che riflette eventuali cancellazioni effettuate.
*/
Prenotazione* gestione_prenotazioni(Prenotazione* head, int id_cliente, Lezione* lezioni_head);

/*
 * Funzione: aggiungi_prenotazione
 * -------------------------------
 * Crea una nuova prenotazione associando un cliente a una lezione 
 * specifica e la aggiunge alla fine della lista delle prenotazioni.
 *
 * Parametri:
 *   head: puntatore alla testa della lista delle prenotazioni esistenti.
 *   id_cliente: ID del cliente che effettua la prenotazione.
 *   id_lezione: ID della lezione per cui si effettua la prenotazione.
 *
 * Pre-condizione:
 *   La lista delle prenotazioni deve essere inizializzata (può essere vuota).
 *   Gli ID del cliente e della lezione devono essere validi.
 *
 * Post-condizione:
 *   Viene creato un nuovo nodo 'Prenotazione' e aggiunto alla lista.
 *   Se la memoria non è disponibile, la lista rimane invariata.
 *
 * Ritorna:
 *   Il puntatore alla testa aggiornata della lista delle prenotazioni.
 */
Prenotazione* aggiungi_prenotazione(Prenotazione* head, int id_cliente, int id_lezione);

#endif