#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h"
#include "lezione.h"
#include "report.h"

/*
 * Genera un report mensile che mostra il numero di prenotazioni per
 * ogni lezione effettuate nel mese specificato (formato "MM/AAAA").
 *
 * Parametri:
 *  prenotazioni: puntatore alla lista delle prenotazioni.
 *  lezioni: puntatore alla lista delle lezioni.
 *  mese_anno: stringa nel formato "MM/AAAA".
 *
 * Ritorna: 
 *  Nessun valore di ritorno essendo una funzione di tipo void.
 */
void report_mensile(Prenotazione* prenotazioni, Lezione* lezioni, const char* mese_anno) {
    Report* report = NULL;
    Prenotazione* curr = prenotazioni;
    while (curr != NULL) {
        
        // Ricerca della lezione associata all'ID prenotato
        Lezione* l = lezioni;
        while (l != NULL && l->id_lezione != curr->id_lezione)
            l = l->next;

        // Verifica che la lezione sia valida e abbia una data corretta
        if (l != NULL && strlen(l->giorno) >= 10) {
            // Confronta mese e anno nella stringa "gg/mm/aaaa"
            if (strncmp(l->giorno + 3, mese_anno, 7) == 0) {
                // Cerca la lezione nel report
                Report* r = report;
                int trovato = 0;
                while (r != NULL) {
                    if (strcmp(r->nome_lezione, l->nome) == 0) {
                        r->conteggio++;
                        trovato = 1;
                        break;
                    }
                    r = r->next;
                }

                // Se non trovata, si aggiunge come nuovo nodo
                if (!trovato) {
                    Report* nuovo = malloc(sizeof(Report));
                    if (nuovo != NULL) {
                        strcpy(nuovo->nome_lezione, l->nome);
                        nuovo->conteggio = 1;
                        nuovo->next = report;
                        report = nuovo;
                    }
                }
            }
        }
        curr = curr->next;
    }

    // Ordina il report per conteggio decrescente
    int scambiato;
    do {
        scambiato = 0;
        Report* r = report;
        while (r != NULL && r->next != NULL) {
            if (r->conteggio < r->next->conteggio) {
                // Scambia i dati tra i due nodi
                char tmp_nome[50];
                int tmp_conteggio;

                strcpy(tmp_nome, r->nome_lezione);
                tmp_conteggio = r->conteggio;

                strcpy(r->nome_lezione, r->next->nome_lezione);
                r->conteggio = r->next->conteggio;

                strcpy(r->next->nome_lezione, tmp_nome);
                r->next->conteggio = tmp_conteggio;

                scambiato = 1;
            }
            r = r->next;
        }
    } while (scambiato);

    // Output del report
    printf("Report Utilizzo Lezioni per %s \n", mese_anno);
    if (report == NULL) {
        printf("Nessuna prenotazione trovata per questo periodo.\n");
    } else {
        Report* r = report;
        while (r != NULL) {
            printf("Lezione: %s | Prenotazioni: %d\n", r->nome_lezione, r->conteggio);
            r = r->next;
        }
    }

    // Libera la memoria dinamica usata per il report
    while (report != NULL) {
        Report* temp = report;
        report = report->next;
        free(temp);
    }
}