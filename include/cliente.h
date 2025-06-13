#ifndef CLIENTE_H
#define CLIENTE_H

// Definizione della struttura Cliente, che rappresenta un cliente e gestisce i dati dell’utente iscritto e il suo abbonamento
typedef struct Cliente {
int id_cliente; // Identificativo univoco del cliente
char nome [50]; // Nome del cliente (max 50 caratteri)
char cognome [50]; // Cognome del cliente (max 50 caratteri)
struct Cliente* next; // Puntatore di tipo Cliente per scorrere la lista
} Cliente; 

/*
* Funzione: aggiungi_cliente
* ----------------------------------
* Aggiunge un nuovo cliente alla lista dei clienti registrati nella palestra.
*
* Parametri:
*   head: il puntatore alla testa della lista collegata dei clienti.
*
* Pre-condizione:
*   La lista dei clienti può essere vuota (head == NULL) oppure può contenere uno o più elementi.
*
* Post-condizione:
*   Viene allocato dinamicamente un nuovo nodo Cliente con ID univoco.
*   Il nome e il cognome vengono acquisiti da input e validati.
*   Se i dati sono validi, il cliente viene aggiunto alla lista.
*   Se l’input è invalido o la memoria non è disponibile, la lista resta invariata.
*
* Ritorna:
*   Il puntatore alla testa della lista aggiornata.
*/
Cliente* aggiungi_cliente(Cliente *head);

/*
* Funzione: cerca_cliente
* ----------------------------------
* Cerca un cliente all’interno della lista dei clienti registrati, dato il suo ID.
*
* Parametri:
*   head: puntatore alla testa della lista dei clienti.
*   id: identificativo univoco del cliente da cercare.
*
* Pre-condizione:
*   La lista può essere vuota o contenere uno o più elementi.
*   L’ID passato deve essere un intero positivo. 
*
* Post-condizione:
*   La funzione percorre la lista alla ricerca del cliente con l’ID corrispondente.
*   La lista non viene modificata.
*
* Ritorna:
*   Il puntatore al nodo Cliente se trovato,
*   NULL se nessun cliente con l’ID specificato è presente nella lista.
*/
Cliente* cerca_cliente(Cliente *head, int id);

/*
* Funzione: stampa_clienti
* ----------------------------------
* Stampa la lista dei clienti iscritti alla palestra e offre all’utente 
* la possibilità di cancellarne uno.
*
* Parametri:
*   head: puntatore alla testa della lista collegata dei clienti.
*
* Pre-condizione:
*   La lista può essere vuota oppure contenere uno o più clienti.
*
* Post-condizione:
*   Se la lista è vuota, viene mostrato un messaggio informativo.
*   Se la lista non è vuota, tutti i clienti vengono stampati a video (ID, nome, cognome).
*   L’utente può scegliere se cancellare un cliente inserendo il relativo ID.
*   Se l’ID è valido, il cliente viene rimosso dalla lista e la memoria viene liberata.
*   Se l’ID non è trovato o l’input è invalido, la lista rimane invariata.
*
* Ritorna:
*   Il puntatore alla nuova testa della lista dei clienti, che può essere modificata 
*   in caso di cancellazione.
*/
Cliente* stampa_clienti(Cliente* head);

#endif