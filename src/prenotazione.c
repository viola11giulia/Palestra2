#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h"
#include "lezione.h"

/*
* Cerca e restituisce una lezione nella lista a partire dal suo ID.
*
* Parametri:
*   head: puntatore alla testa della lista di lezioni.
*   id_lezione: identificatore numerico della lezione da cercare.
*
* Ritorna:
*   Puntatore alla lezione trovata, oppure NULL se non è presente nella lista.
*/
Lezione* cerca_lezione(Lezione* head, int id_lezione) {
    Lezione* curr = head;
    while (curr != NULL) {
        if (curr->id_lezione == id_lezione)
            return curr;
        curr = curr->next;
    }
    return NULL; //Nessuna lezione trovata con l'ID dato
}

/*
* Gestisce la visualizzazione e l’eventuale cancellazione delle prenotazioni effettuate da un cliente.
*
* Parametri:
*   head: puntatore alla testa della lista delle prenotazioni.
*   id_cliente: identificatore numerico del cliente.
*   lezioni_head: puntatore alla testa della lista delle lezioni.
*
* Ritorna:
*   La testa della lista delle prenotazioni aggiornata.
*/
Prenotazione* gestione_prenotazioni(Prenotazione* head, int id_cliente, Lezione* lezioni_head) {
    Prenotazione* corrente = head;
    Prenotazione* precedente = NULL;
    int trovata = 0;
    int scelta;

    while (corrente != NULL) {
        if (corrente->id_cliente == id_cliente) {
            trovata = 1;

            // Cerca la lezione associata alla prenotazione
            Lezione* lez = cerca_lezione(lezioni_head, corrente->id_lezione);
            if (lez != NULL) {
                //Stampa di tutti i dettagli della lezione trovata
                printf("Prenotazione trovata:\n");
                printf(" - Lezione: %s\n", lez->nome);
                printf(" - Giorno: %s\n", lez->giorno);
                printf(" - Orario: %s\n", lez->orario);
            } else {
                //Lezione non più esistente 
                printf("Prenotazione trovata ma lezione non trovata (ID: %d).\n", corrente->id_lezione);
            }

            //Richiesta di cancellazione della prenotazione
            printf("Vuoi cancellare questa prenotazione? (1 = sì, 0 = no): ");
            scanf("%d", &scelta);

            if (scelta == 1) {
                // Seleziona la lezione per decrementare i partecipanti
                if (lez != NULL && lez->partecipanti > 0) {
                    lez->partecipanti--; // Decrementa i posti occupati
                }

                // Rimuove la prenotazione dalla lista
                if (precedente == NULL) {
                    head = corrente->next;
                } else {
                    precedente->next = corrente->next;
                }
                
                //Libera la memotia del nodo eliminato 
                Prenotazione* temp = corrente;
                corrente = corrente->next;
                free(temp);
                printf("Prenotazione cancellata con successo.\n");
            } else {
                precedente = corrente;
                corrente = corrente->next;
            }
        } else {
            precedente = corrente;
            corrente = corrente->next;
        }
    }
    // Nessuna prenotazione trovata
    if (!trovata) {
        printf("Nessuna prenotazione trovata per il cliente con codice %d.\n", id_cliente);
    }
    return head;
}

/*
* Crea una nuova prenotazione e la inserisce all'inizio della lista. 
* 
* Parametri: 
*   head: puntatore alla testa della lista delle prenotazioni.
*   id_cliente: identificatore del cliente che effettua la prenotazione. 
*   id_lezione: identificatore della lezione prenotata. 
*
* Ritorna: 
*   La nuova testa della lista, con la prenotazione appena aggiunta.
*/
Prenotazione* aggiungi_prenotazione(Prenotazione* head, int id_cliente, int id_lezione) {
    // Alloca memoria per la nuova prenotazione
    Prenotazione* nuova = malloc(sizeof(Prenotazione));
    if (!nuova) {
        printf("Errore di allocazione della memoria.\n");
        return head; // Restituisce la lista originale se fallisce l'allocazione
    }
    
    // Inizializzazione dei campi della nuova prenotazione
    nuova->id_cliente = id_cliente;
    nuova->id_lezione = id_lezione;
    
    // Inserisce la nuova prenotazione in testa alla lista collegata
    nuova->next = head;
    
    // Restituisce il puntatore alla nuova testa della lista 
    return nuova;
}