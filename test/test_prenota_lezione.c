#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lezione.h"

// Funzione di supporto per creare una lezione
Lezione* crea_lezione_test(int id, const char* nome, const char* giorno, const char* orario, int max_partecipanti) {
    Lezione* l = malloc(sizeof(Lezione));
    l->id_lezione = id;
    strncpy(l->nome, nome, sizeof(l->nome));
    strncpy(l->giorno, giorno, sizeof(l->giorno));
    strncpy(l->orario, orario, sizeof(l->orario));
    l->durata_minuti = 60;
    l->max_partecipanti = max_partecipanti;
    l->partecipanti = 0;
    l->next = NULL;
    return l;
}

int main() {
    Lezione* l1 = crea_lezione_test(1, "Zumba", "15/06/2025", "10:00", 2);

    // Test 1: prima prenotazione
    int esito = prenota_lezione(l1, 1, 101);
    if (esito == 1 && l1->partecipanti == 1)
        printf("✅ Test 1 superato: prima prenotazione accettata.\n");
    else
        printf("❌ Test 1 fallito.\n");

    // Test 2: seconda prenotazione
    esito = prenota_lezione(l1, 1, 102);
    if (esito == 1 && l1->partecipanti == 2)
        printf("✅ Test 2 superato: seconda prenotazione accettata.\n");
    else
        printf("❌ Test 2 fallito.\n");

    // Test 3: terza prenotazione oltre il limite
    esito = prenota_lezione(l1, 1, 103);
    if (esito == 0 && l1->partecipanti == 2)
        printf("✅ Test 3 superato: prenotazione rifiutata, posti esauriti.\n");
    else
        printf("❌ Test 3 fallito.\n");

    free(l1);
    return 0;
}
