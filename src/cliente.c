#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

/*
* Aggiunge un nuovo cliente alla lista collegata dei clienti.
* L'ID cliente viene assegnato automaticamente in ordine crescente.
* Verifica che nome e cognome contengano solo lettere.
* Parametri:
*  head: puntatore al primo elemento della lista clienti.
* Ritorna:
*  Puntatore aggiornato alla testa della lista clienti.
*  Se l'aggiunta fallisce per memoria insufficiente o input errato,
*  ritorna la lista originale senza modifiche.
*/
Cliente* aggiungi_cliente(Cliente *head) {
    static int prossimo_id = 1; // ID assegnato ai nuovi clienti
    
    // Allocazione dinamica per il nuovo cliente
    Cliente *nuovo = malloc(sizeof(Cliente));
    if (nuovo == NULL) {
        printf("Errore: memoria non disponibile.\n");
        return head; // Se non c'è memoria, restituisce la lista originale
    }
    nuovo->id_cliente = prossimo_id++;

    printf("Inserisci il tuo nome: ");
    scanf("%49s", nuovo->nome);
    
    // Controlla che il nome contenga solo lettere
    for (int i = 0; nuovo->nome[i] != '\0'; i++) {
        char c = nuovo->nome[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            printf("Errore: il nome deve contenere solo lettere.\n");
            free(nuovo);
            return head; // Libera memoria per evitare perdite
        }
    }

    printf("Inserisci il tuo cognome: ");
    scanf("%49s", nuovo->cognome);
    
    // Controlla che il cognome contenga solo lettere
    for (int i = 0; nuovo->cognome[i] != '\0'; i++) {
        char c = nuovo->cognome[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            printf("Errore: il cognome deve contenere solo lettere.\n");
            free(nuovo);
            return head;
        }
    }

    nuovo->next = NULL; // Il nuovo nodo sarà in fondo alla lista
    
    // Se la lista è vuota, il nuovo cliente diventa la testa della lista
    if (head == NULL) {
        printf("Cliente iscritto correttamente con ID: %d\n", nuovo->id_cliente);
        return nuovo;
    }
    
    // Scorre la lista fino all'ultimo nodo per aggiungere il nuovo cliente
    Cliente *corrente = head;
    while (corrente->next != NULL) {
        corrente = corrente->next;
    }
    corrente->next = nuovo;
    printf("Cliente iscritto correttamente con ID: %d\n", nuovo->id_cliente);
    return head;
}

/*
* Cerca un cliente nella lista in base all'ID.
* Parametri:
*  head: puntatore al primo elemento della lista clienti.
*  id: ID del cliente da cercare.
* Ritorna:
*  Puntatore al cliente trovato, o NULL se non lo si trova.
*/
Cliente* cerca_cliente(Cliente *head, int id) {
    // Scorre la lista fino a trovare il cliente con ID corrispondente
    while (head != NULL) {
        if (head->id_cliente == id) {
            return head;  // cliente trovato
        }
        head = head->next;
    }
    return NULL;  // cliente non trovato
}

/*
* Visualizza la lista dei clienti iscritti.
* Permette di cancellare un cliente selezionato dall'utente.
* Parametri:
*      head: puntatore al primo elemento della lista clienti.
* Ritorna:
*      Puntatore aggiornato alla testa della lista, dopo eventuali cancellazioni.
*/
Cliente* stampa_clienti(Cliente* head) {
    Cliente* curr = head;

    // Controllo lista vuota o dati invalidi
    if (curr == NULL) {
        printf("Nessun cliente iscritto.\n");
        return head;
    }

    // Verifica se almeno un nodo ha un ID valido
    int clienti_validi = 0;
    Cliente* temp = curr;
    while (temp != NULL) {
        if (temp->id_cliente > 0) {
            clienti_validi = 1;
            break;
        }
        temp = temp->next;
    }

    if (!clienti_validi) {
        printf("Nessun cliente iscritto.\n");
        return head;
    }

    // Stampa tutti i clienti della lista 
    printf("Lista clienti iscritti:\n");
    while (curr != NULL) {
        if (curr->id_cliente > 0) {
            printf("ID: %d - Nome: %s - Cognome: %s\n", curr->id_cliente, curr->nome, curr->cognome);
        }
        curr = curr->next;
    }

    char scelta;
    // Ciclo per ottenere una risposta valida dall'utente
    do {
        printf("\nVuoi cancellare un cliente? (s/n): ");
        scanf(" %c", &scelta);

        if (scelta != 's' && scelta != 'S' && scelta != 'n' && scelta != 'N') {
            printf("Errore: devi inserire solo 's' (si) o 'n' (no).\n");
            // Svuota buffer in caso di input errato per evitare loop infiniti
            while (getchar() != '\n');
        }
    } while (scelta != 's' && scelta != 'S' && scelta != 'n' && scelta != 'N');

    if (scelta == 's' || scelta == 'S') {
        int id_da_cancellare;
        printf("Inserisci l'ID del cliente da cancellare: ");
        
        // Controlla che l'input sia valido
        if (scanf("%d", &id_da_cancellare) != 1) {
            printf("Input non valido.\n");
            while (getchar() != '\n');
            return head;
        }

        Cliente *prev = NULL;
        Cliente *curr = head;
        
        // Cerca il cliente da cancellare nella lista
        while (curr != NULL && curr->id_cliente != id_da_cancellare) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            printf("Cliente con ID %d non trovato.\n", id_da_cancellare);
            return head;
        }

        // Rimuove il cliente dalla lista aggiornando i puntatori
        if (prev == NULL) {
            head = curr->next;
        } else {
            prev->next = curr->next;
        }

        free(curr);
        printf("Cliente con ID %d cancellato con successo.\n", id_da_cancellare);
    }

    return head;
}