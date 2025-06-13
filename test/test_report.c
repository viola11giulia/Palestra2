#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/prenotazione.h"
#include "../include/lezione.h"
#include "../include/report.h"

// Funzione di supporto per creare una lezione
Lezione* crea_lezione_test(int id, const char* nome, const char* giorno) {
    Lezione* l = malloc(sizeof(Lezione));
    l->id_lezione = id;
    strncpy(l->nome, nome, sizeof(l->nome));
    strncpy(l->giorno, giorno, sizeof(l->giorno));
    strcpy(l->orario, "10:00");
    l->durata_minuti = 60;
    l->max_partecipanti = 10;
    l->partecipanti = 0;
    l->next = NULL;
    return l;
}

// Funzione di supporto per creare una prenotazione
Prenotazione* crea_prenotazione_test(int id_cliente, int id_lezione, Prenotazione* next) {
    Prenotazione* p = malloc(sizeof(Prenotazione));
    p->id_cliente = id_cliente;
    p->id_lezione = id_lezione;
    p->next = next;
    return p;
}

int main() {
    // Crea lezioni
    Lezione* l1 = crea_lezione_test(1, "Yoga", "05/06/2025");
    Lezione* l2 = crea_lezione_test(2, "Pilates", "15/06/2025");
    l1->next = l2;

    // Crea prenotazioni: 2 per Yoga, 1 per Pilates
    Prenotazione* p3 = crea_prenotazione_test(103, 2, NULL);
    Prenotazione* p2 = crea_prenotazione_test(102, 1, p3);
    Prenotazione* p1 = crea_prenotazione_test(101, 1, p2);

    // Esegui report
    printf("🧪 Esecuzione report per 06/2025:\n");
    report_mensile(p1, l1, "06/2025");

    // Cleanup
    free(p1);
    free(p2);
    free(p3);
    free(l2);
    free(l1);

    return 0;
}
