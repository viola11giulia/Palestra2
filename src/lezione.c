#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "lezione.h"

/*
* Trova il più piccolo ID intero positivo non ancora utilizzato nella lista di lezioni.
* Scorre la lista confrontando gli ID esistenti e restituisce il primo ID disponibile.
*
* Parametri:
*  head: puntatore alla testa della lista delle lezioni.
*
* Ritorna:
*  Il più piccolo ID intero positivo non usato nella lista.
*/
int trova_id_libero(Lezione *head) {
    int id = 1;
    int trovato;

    while (1) {
        trovato = 0;
        
        // Scorre tutta la lista per verificare se l'ID corrente è usato
        Lezione *corrente = head;
        while (corrente != NULL) {
            if (corrente->id_lezione == id) {
                trovato = 1;
                break;
            }
            corrente = corrente->next;
        }
        
        // Se l'ID non è stato trovato nella lista, lo restituisce
        if (!trovato)
            return id;
        id++; // Prova l'ID successivo
    }
}

/*
* Prende da input i dati necessari per creare una nuova lezione e la inserisce in coda alla lista. 
*
* Parametri:
*  head: puntatore alla testa della lista esistente.
*
* Ritorna:
*  Puntatore alla testa della lista aggiornata.
*/
Lezione* aggiungi_lezione(Lezione *head) {
    Lezione *nuova = malloc(sizeof(Lezione));
    if (!nuova) {
        printf("Errore: memoria non disponibile.\n");
        return head;
    }

    // Richiede un nome contenente solo lettere (senza numeri e simboli)
    while (1) {
        printf("Inserisci il nome della lezione: ");
        scanf("%49s", nuova->nome);
        int valido = 1;
        for (int i = 0; nuova->nome[i] != '\0'; i++) {
            char c = nuova->nome[i];
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
                printf("Errore: il nome deve contenere solo lettere.\n");
                valido = 0;
                break;
            }
        }
        if (valido) break;
    }

    // Richiede una data e controlla che siano presenti solo numeri e '/'
    while (1) {
        printf("Inserisci il giorno della lezione (GG/MM/AAAA): ");
        scanf("%14s", nuova->giorno);
        int valido = 1;
        for (int i = 0; nuova->giorno[i] != '\0'; i++) {
            char c = nuova->giorno[i];
            if (!((c >= '0' && c <= '9') || c == '/')) {
                printf("Errore: il giorno deve contenere solo numeri e '/'.\n");
                valido = 0;
                break;
            }
        }
        if (valido) break;
    }

    // Richiede un orario nel formato HH:MM, con solo numeri e ':''
    while (1) {
        printf("Inserisci l'orario della lezione (HH:MM): ");
        scanf("%5s", nuova->orario);
        int valido = 1;
        for (int i = 0; nuova->orario[i] != '\0'; i++) {
            char c = nuova->orario[i];
            if (!((c >= '0' && c <= '9') || c == ':')) {
                printf("Errore: l'orario deve contenere solo numeri e ':'.\n");
                valido = 0;
                break;
            }
        }
        if (valido) break;
    }

    // Controllo che la durata sia un numero intero positivo
    while (1) {
        printf("Inserisci la durata della lezione in minuti: ");
        if (scanf("%d", &nuova->durata_minuti) != 1) {
            printf("Errore: inserisci un numero valido.\n");
            
            // Elimina eventuali caratteri residui nel buffer
            while (getchar() != '\n'); // pulizia buffer
            continue;
        }
        
        if (nuova->durata_minuti <= 0) {
            printf("Errore: la durata deve essere un numero positivo.\n");
            continue;
        }
        break;
    }

    // Richiesta e controllo del numero massimo di partecipanti
    while (1) {
        printf("Inserisci il numero massimo di partecipanti: ");
        if (scanf("%d", &nuova->max_partecipanti) != 1) {
            printf("Errore: inserisci un numero valido.\n");
            while (getchar() != '\n'); // svuota il buffer
            continue;
        }
        
        if (nuova->max_partecipanti <= 0) {
            printf("Errore: deve essere un numero positivo.\n");
            continue;
        }
        break;
    }

    // Si assegna il più piccolo ID libero alla nuova lezione
    nuova->id_lezione = trova_id_libero(head);

    nuova->partecipanti = 0;
    nuova->next = NULL;

    // Inserimento in lista della nuova lezione
    if (head == NULL) {
        printf("Lezione aggiunta con ID: %d\n", nuova->id_lezione);
        return nuova;
    }
    Lezione *corrente = head;
    while (corrente->next != NULL) {
        corrente = corrente->next;
    }
    corrente->next = nuova;

    printf("Lezione aggiunta con ID: %d\n", nuova->id_lezione);
    return head;
}

/*
* Mostra tutte le lezioni attualmente presenti nella lista, indicando per ciascuna la disponibilità residua. 
* Permette anche la cancellazione di una lezione tramite ID.
*
* Parametri:
*  head: puntatore alla testa della lista delle lezioni.
*
* Ritorna:
*  La testa della lista, eventualmente modificata se una lezione è stata eliminata.
*/
Lezione* visualizza_lezione(Lezione *head) {
    if (head == NULL) {
        printf("Nessuna lezione disponibile.\n");
        return head;
    }

    // Scorre la lista per stampare i dettagli e i posti disponibili delle lezioni
    Lezione *corrente = head;
    printf("Disponibilità delle lezioni:\n");
    while (corrente != NULL) {
        int posti_disponibili = corrente->max_partecipanti - corrente->partecipanti;
        printf("ID: %d | %s - %s alle %s | Posti disponibili: %d/%d\n",
            corrente->id_lezione,
            corrente->nome,
            corrente->giorno,
            corrente->orario,
            posti_disponibili,
            corrente->max_partecipanti);
        corrente = corrente->next;
    }

    // Si richiede conferma per eliminare una lezione
    char scelta;
    do {
        printf("\nVuoi cancellare una lezione? (s/n): ");
        scanf(" %c", &scelta);
        while (getchar() != '\n'); //svuota sempre il buffer 

        if (scelta != 's' && scelta != 'S' && scelta != 'n' && scelta != 'N') {
            printf("Errore: devi inserire solo 's' (si) o 'n' (no).\n");
        }
    } while (scelta != 's' && scelta != 'S' && scelta != 'n' && scelta != 'N');

    if (scelta == 's' || scelta == 'S') {
        int id_da_cancellare;
        printf("Inserisci l'ID della lezione da cancellare: ");
        if (scanf("%d", &id_da_cancellare) != 1) {
            printf("Input non valido.\n");
            while(getchar() != '\n'); // svuota buffer
            return head;
        }

        // Cerca la lezione da eliminare
        Lezione *prev = NULL;
        Lezione *curr = head;
        while (curr != NULL && curr->id_lezione != id_da_cancellare) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            printf("Lezione con ID %d non trovata.\n", id_da_cancellare);
            return head;
        }

        // Rimuove la lezione dalla lista
        if (prev == NULL) {
            head = curr->next;
        } else {
            prev->next = curr->next;
        }

        free(curr);
        printf("Lezione con ID %d cancellata con successo.\n", id_da_cancellare);
    }

    return head;
}

/*
* Se ci sono posti disponibili, registra un cliente a una lezione specifica.
*
* Parametri:
*   head_lezioni: puntatore alla lista di lezioni disponibili.
*   id_lezione: ID della lezione che il cliente vuole prenotare.
*   id_cliente: ID del cliente che deve prenotare una lezione.
*
* Ritorna:
*   1 se la prenotazione è avvenuta con successo,
*   0 in caso di errore (lezione non trovata o piena).
*/
int prenota_lezione(Lezione *head_lezioni, int id_lezione, int id_cliente) {
    // Controlla che l'id della lezione sia positivo
    if (id_lezione <= 0) {
        printf("ID lezione non valido. Deve essere un numero positivo.\n");
        return 0;
    }

    // Cerca la lezione e verifica la disponibilità dei posti
    Lezione *curr_lezione = head_lezioni;
    while (curr_lezione != NULL) {
        if (curr_lezione->id_lezione == id_lezione) {
            
            // Verifica se ci sono ancora posti disponibili
            if (curr_lezione->partecipanti < curr_lezione->max_partecipanti) {
                curr_lezione->partecipanti++;
                return 1;
            } else {
                printf("Posti esauriti per la lezione %d.\n", id_lezione);
                return 0;
            }
        }
        curr_lezione = curr_lezione->next;
    }

    printf("Lezione con ID %d non trovata.\n", id_lezione);
    return 0;
}