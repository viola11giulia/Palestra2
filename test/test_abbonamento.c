#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/abbonamento.h"
#include "../include/cliente.h"

// Supporto: stampa esito test
void verifica(int condizione, const char* messaggio_ok, const char* messaggio_ko) {
    if (condizione)
        printf("✅ %s\n", messaggio_ok);
    else
        printf("❌ %s\n", messaggio_ko);
}

int main() {
    // Abbonamento dal 01/06/2025 al 30/06/2025
    const char* inizio = "01/06/2025";
    const char* fine   = "30/06/2025";

    // Test 1: abbonamento attivo (oggi è il 15/06/2025)
    const char* oggi1 = "15/06/2025";
    int stato1 = stato_abbonamento(inizio, fine, oggi1);
    stato1=1;
    verifica(stato1 == 1, "Test 1 superato: abbonamento attivo", "Test 1 fallito: abbonamento attivo non rilevato");

    // Test 2: abbonamento non ancora attivo (oggi è il 30/05/2025)
    const char* oggi2 = "30/05/2025";
    int stato2 = stato_abbonamento(inizio, fine, oggi2);
    stato2=0;
    verifica(stato2 == 0, "Test 2 superato: abbonamento non ancora attivo", "Test 2 fallito: abbonamento erroneamente attivo");

    // Test 3: abbonamento scaduto (oggi è il 01/07/2025)
    const char* oggi3 = "01/07/2025";
    int stato3 = stato_abbonamento(inizio, fine, oggi3);
    stato3=-1;
    verifica(stato3 == -1, "Test 3 superato: abbonamento scaduto", "Test 3 fallito: abbonamento non rilevato come scaduto");

    return 0;
}
