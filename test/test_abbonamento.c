#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/abbonamento.h"
#include "../include/cliente.h"

// Funzione di supporto per creare un cliente
Cliente* crea_cliente_test(int id) {
    Cliente* c = malloc(sizeof(Cliente));
    c->id_cliente = id;
    strcpy(c->nome, "Mario");
    strcpy(c->cognome, "Rossi");
    c->next = NULL;
    return c;
}

// Funzione di supporto per creare un abbonamento
Abbonamento* crea_abbonamento_test(int id_cliente, const char* tipo, const char* inizio, const char* fine) {
    Abbonamento* a = malloc(sizeof(Abbonamento));
    a->id_cliente = id_cliente;
    strncpy(a->tipo, tipo, sizeof(a->tipo));
    strncpy(a->data_inizio, inizio, sizeof(a->data_inizio));
    strncpy(a->data_fine, fine, sizeof(a->data_fine));
    a->next = NULL;
    return a;
}

int main() {
    Cliente* cliente = crea_cliente_test(1);
    Abbonamento* abbonamento = crea_abbonamento_test(1, "mensile", "01/06/2025", "30/06/2025");

    // Test 1: Abbonamento attivo
    const char* data_oggi = "01/06/2025";
    int stato = stato_abbonamento(abbonamento->data_inizio, abbonamento->data_fine, data_oggi);
    if (stato == 1)
        printf("✅ Test 1 superato: abbonamento attivo correttamente rilevato.\n");
    else
        printf("❌ Test 1 fallito.\n");

    // Test 2: Abbonamento non ancora attivo
    data_oggi = "30/05/2025";
    stato = stato_abbonamento(abbonamento->data_inizio, abbonamento->data_fine, data_oggi);
    if (stato == 0)
        printf("✅ Test 2 superato: abbonamento non ancora attivo rilevato.\n");
    else
        printf("❌ Test 2 fallito.\n");

    // Test 3: Abbonamento scaduto
    data_oggi = "01/07/2025";
    stato = stato_abbonamento(abbonamento->data_inizio, abbonamento->data_fine, data_oggi);
    if (stato == -1)
        printf("✅ Test 3 superato: abbonamento scaduto rilevato correttamente.\n");
    else
        printf("❌ Test 3 fallito.\n");

    free(cliente);
    free(abbonamento);
    return 0;
}
