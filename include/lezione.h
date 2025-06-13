#ifndef LEZIONE_H
#define LEZIONE_H

// Definizione della struttura Lezione, che rappresenta una lezione di fitness disponibile alla prenotazione 
typedef struct Lezione {
int id_lezione; // Identificativo univoco della lezione
char nome [50]; // Nome della lezione (max 50 caratteri)
char giorno [15]; // Data del giorno della lezione in formato GG/MM/AAAA (max 15 caratteri)
char orario [6]; // Orario della lezione in formato "HH:MM" (max 6 caratteri)
int durata_minuti; //Durata in minuti della lezione
int max_partecipanti; // Numero massimo dei partecipanti
int partecipanti; // Numero attuale dei partecipanti 
struct Lezione* next; // Puntatore di tipo Lezione per scorrere la lista
} Lezione;  

/*
* Funzione: aggiungi_lezione
* ----------------------------------
* Aggiunge una nuova lezione alla lista delle lezioni disponibili nella palestra.
* 
* Parametri:
*   head: puntatore alla testa della lista collegata delle lezioni già presenti.
*
* Pre-condizione:
*   La lista può essere vuota (head == NULL) o contenere una o più lezioni.
*   La funzione presume che il tipo Lezione sia definito e che esista una funzione
*   esterna 'trova_id_libero' che restituisce il primo ID disponibile.
*
* Post-condizione:
*   Viene allocato un nuovo nodo Lezione e popolato con i dati inseriti dall’utente.
*   I dati vengono controllati: il nome può contenere solo lettere, il giorno solo numeri e '/',
*   l'orario solo numeri e ':', durata e partecipanti devono essere numeri positivi.
*   La nuova lezione viene inserita in coda alla lista.
*   Il campo 'id_lezione' viene assegnato automaticamente tramite 'trova_id_libero'.
*
* Ritorna:
*   Il puntatore alla testa della lista delle lezioni, eventualmente aggiornata.
*   Se la memoria non è disponibile, la lista rimane invariata.
*/
Lezione* aggiungi_lezione(Lezione *head);

/*
* Funzione: visualizza_lezione
* ----------------------------------
* Mostra l’elenco delle lezioni disponibili con indicazione dei posti liberi,
* e offre all’utente la possibilità di cancellarne una specificando l’ID.
*
* Parametri:
*   head: puntatore alla testa della lista collegata delle lezioni.
*
* Pre-condizione:
*   La lista può essere vuota o contenere una o più lezioni.
*
* Post-condizione:
*   Se la lista è vuota, viene mostrato un messaggio informativo.
*   Se la lista contiene lezioni, ciascuna viene stampata a video con ID, 
*   nome, giorno, orario e numero di posti disponibili.
*   L’utente può scegliere se cancellare una lezione inserendo un ID esistente.
*   Se l’ID è valido, la lezione viene rimossa dalla lista e la memoria viene liberata.
*   Se l’ID non è presente o l’input è invalido, la lista rimane uguale.
*
* Ritorna:
*   Il puntatore alla testa della lista aggiornata, potenzialmente modificata 
*   in caso di cancellazione.
*/
Lezione* visualizza_lezione(Lezione *head);

/*
* Funzione: prenota_lezione
* ----------------------------------
* Permette di prenotare un posto in una lezione specifica, dato il suo ID.
* Verifica se la lezione esiste e se ci sono ancora posti disponibili.
*
* Parametri:
*   head_lezioni: puntatore alla testa della lista delle lezioni disponibili.
*   id_lezione: identificativo univoco della lezione da prenotare.
*   id_cliente: identificativo del cliente.
*
* Pre-condizione:
*   La lista delle lezioni deve essere inizializzata (può anche essere vuota).
*   L'ID della lezione deve essere un intero positivo.
*
* Post-condizione:
*   Se la lezione esiste e ha ancora posti disponibili, il numero di partecipanti 
*   viene incrementato.
*   Se la lezione non esiste o non ha posti disponibili, la prenotazione non viene effettuata.
*   In caso di errore, non viene fatta nessuna modifica alla lista.
*
* Ritorna:
*   1 se la prenotazione è stata eseguita con successo, oppure
*   0 se la prenotazione non è possibile (lezione non trovata, ID non valido o posti esauriti).
*/
int prenota_lezione(Lezione *head_lezioni, int id_lezione, int id_cliente);

#endif