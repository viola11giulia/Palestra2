#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "abbonamento.h"

/*
 * Crea un nuovo abbonamento per un cliente esistente.
 *
 * Parametri:
 *  abbonamenti: puntatore alla lista esistente degli abbonamenti.
 *  clienti: puntatore alla lista dei clienti registrati.
 *
 * Ritorna:
 *   Puntatore alla testa della lista aggiornata degli abbonamenti.
 */
Abbonamento* crea_abbonamento(Abbonamento* abbonamenti, Cliente* clienti) {
    Abbonamento* nuovo = malloc(sizeof(Abbonamento));
    if (!nuovo) {
        printf("Errore allocazione memoria\n");
        return abbonamenti;
    }

    // Richiesta dell'ID del cliente e controllo
    int id_input;
    printf("Inserisci ID cliente: ");
    if (scanf("%d", &id_input) != 1 || id_input <= 0) {
        printf("Errore: inserisci un ID valido (numero positivo).\n");
        free(nuovo);
        while (getchar() != '\n'); // svuota buffer
        return abbonamenti;
    }

    //Verifica dell'esistenza del cliente
    if (!cerca_cliente(clienti, id_input)) {
        printf("Errore: nessun cliente trovato con ID %d.\n", id_input);
        free(nuovo);
        while (getchar() != '\n'); // svuota il buffer
        return abbonamenti;
    }
    nuovo->id_cliente = id_input;

    //Input e controllo del tipo di abbonamento
    while (1) {
        printf("Inserisci tipo abbonamento (es. mensile, annuale): ");
        scanf(" %19s", nuovo->tipo);
        int valido = 1;
        for (int i = 0; nuovo->tipo[i] != '\0'; i++) {
            char c = nuovo->tipo[i];
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
                printf("Errore: il tipo deve contenere solo lettere.\n");
                valido = 0;
                break;
            }
        }
        if (valido) break;
    }

    //Input e controllo della data in cui inizia l'abbonamento
    while (1) {
        printf("Inserisci data inizio (gg/mm/aaaa): ");
        scanf(" %10s", nuovo->data_inizio);
        int valido = 1;
        for (int i = 0; nuovo->data_inizio[i] != '\0'; i++) {
            char c = nuovo->data_inizio[i];
            if (!((c >= '0' && c <= '9') || c == '/')) {
                valido = 0;
                break;
            }
        }
        if (!valido) {
            printf("Errore: la data deve contenere solo numeri e '/'. Riprova.\n");
            while (getchar() != '\n'); // svuota buffer
            continue;
        }
        break;
    }

    //Input e controllo della data in cui finisce l'abbonamento
    while (1) {
        printf("Inserisci data fine (gg/mm/aaaa): ");
        scanf(" %10s", nuovo->data_fine);
        int valido = 1;
        for (int i = 0; nuovo->data_fine[i] != '\0'; i++) {
            char c = nuovo->data_fine[i];
            if (!((c >= '0' && c <= '9') || c == '/')) {
                valido = 0;
                break;
            }
        }
        if (!valido) {
            printf("Errore: la data deve contenere solo numeri e '/'. Riprova.\n");
            while (getchar() != '\n'); // svuota buffer
            continue;
        }
        break;
    }

    //Inserisce il nuovo abbonamento in cima alla lista
    nuovo->next = abbonamenti;
    abbonamenti = nuovo;

    printf("Abbonamento creato con successo.\n");

    return abbonamenti;
}

/*
* Confronta due date nel formato 'gg/mm/aaaa'. 
*
* Parametri:
*   data1: stringa rappresentante la prima data.
*   data2: stringa rappresentante la seconda data.
*
* Ritorna:
*  1 se data1 <= data2, oppure 0 se data1 > data2.
*  Se il confronto fallisce, restituisce -1.
*/
int data_minore_uguale(const char *data1, const char *data2) {
    int g1, m1, a1;
    int g2, m2, a2;

    if (sscanf(data1, "%d/%d/%d", &g1, &m1, &a1) != 3) return -1;
    if (sscanf(data2, "%d/%d/%d", &g2, &m2, &a2) != 3) return -1;

    if (a1 < a2) return 1;
    else if (a1 > a2) return 0;
    else {
        if (m1 < m2) return 1;
        else if (m1 > m2) return 0;
        else {
            if (g1 <= g2) return 1;
            else return 0;
        }
    }
}

/*
* Determina lo stato di un abbonamento confrontando le date
* di inizio e di fine con la data odierna.
*
* Parametri:
*   data_inizio: stringa che indica la data di inizio dell’abbonamento.
*   data_fine: stringa che indica la data di scadenza dell’abbonamento.
*   data_oggi: stringa che indica la data odierna fornita dall’utente.
*
* Ritorna:
*   0 se l’abbonamento non è ancora attivo (oggi < inizio),
*   1 se l’abbonamento è attivo (inzio < oggi < fine),
*  -1 se l’abbonamento è scaduto (fine < oggi).
*/
int stato_abbonamento(const char *data_inizio, const char *data_fine, const char *data_oggi) {
    if (data_minore_uguale(data_oggi, data_inizio) == 0) {
        return 0; // abbonamento non ancora attivo
    }
    if (data_minore_uguale(data_fine, data_oggi) == 0) {
        return -1; //abbonamento scaduto
    }
    return 1; //abbonamento attivo
}

/*
* Permette di visualizzare lo stato di un abbonamento di un cliente e di cancellarlo, se richiesto.
*
* Parametri:
*  	head: lista degli abbonamenti.
*  	id_cliente: ID del cliente da cercare.
*
* Ritorna:
*  	La lista aggiornata degli abbonamenti, se uno viene rimosso.
*/
Abbonamento* gestisci_abbonamento(Abbonamento *head, int id_cliente) {
    Abbonamento *attuale = head;
    Abbonamento *precedente = NULL;

    // Funzione per confrontare le due date
    int confronta_date(int g1, int m1, int a1, int g2, int m2, int a2) {
        if (a1 < a2) return -1;
        if (a1 > a2) return 1;
        if (m1 < m2) return -1;
        if (m1 > m2) return 1;
        if (g1 < g2) return -1;
        if (g1 > g2) return 1;
        return 0;
    }

    // Funzione di supporto per ottenere stato abbonamento
    int stato_abbonamento(const char *data_inizio, const char *data_fine, const char *data_oggi) {
        int g_inizio, m_inizio, a_inizio;
        int g_fine, m_fine, a_fine;
        int g_oggi, m_oggi, a_oggi;

        if (sscanf(data_inizio, "%d/%d/%d", &g_inizio, &m_inizio, &a_inizio) != 3) return 2;
        if (sscanf(data_fine, "%d/%d/%d", &g_fine, &m_fine, &a_fine) != 3) return 2;
        if (sscanf(data_oggi, "%d/%d/%d", &g_oggi, &m_oggi, &a_oggi) != 3) return 2;

        if (confronta_date(g_oggi, m_oggi, a_oggi, g_inizio, m_inizio, a_inizio) < 0)
            return 0;  // non ancora attivo
        else if (confronta_date(g_oggi, m_oggi, a_oggi, g_fine, m_fine, a_fine) > 0)
            return 2;  // scaduto
        else
            return 1;  // attivo
    }

    while (attuale != NULL) {
        if (attuale->id_cliente == id_cliente) {
            // Abbonamento trovato
            printf("Abbonamento trovato:\n");
            printf("- Tipo: %s\n", attuale->tipo);
            printf("- Inizio: %s\n", attuale->data_inizio);
            printf("- Fine: %s\n", attuale->data_fine);

            char data_oggi[11];
            printf("Inserisci la data odierna (gg/mm/aaaa): ");
            scanf("%10s", data_oggi);

            int stato = stato_abbonamento(attuale->data_inizio, attuale->data_fine, data_oggi);

            if (stato == 0)
                printf("Abbonamento NON ANCORA ATTIVO.\n");
            else if (stato == 1)
                printf("Abbonamento ATTIVO.\n");
            else
                printf("Abbonamento SCADUTO.\n");

            //Operazione per cancellare un abbonamento a scelta
            char scelta;
            printf("Vuoi cancellare l'abbonamento? (s/n): ");
            scanf(" %c", &scelta);

            if (scelta == 's' || scelta == 'S') {
                if (precedente == NULL) {
                    head = attuale->next;
                } else {
                    precedente->next = attuale->next;
                }
                free(attuale);
                printf("Abbonamento cancellato.\n");
            }

            return head;
        }
        precedente = attuale;
        attuale = attuale->next;
    }

    printf("Nessun abbonamento trovato con ID cliente %d.\n", id_cliente);
    return head;
}