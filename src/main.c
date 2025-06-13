#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "lezione.h"
#include "abbonamento.h"
#include "prenotazione.h"
#include "report.h"

// Funzione principale che gestisce il menu e le varie operazioni 
int main() {
    // Liste collegate per i dati 
    Cliente* clienti = NULL;
    Lezione* lezioni = NULL;
    Abbonamento* abbonamenti = NULL;
    Prenotazione* prenotazioni = NULL;

    // Variabile per memorizzare la scelta dell'utente 
    int scelta;
    
    do {
        // Menu testuale principale 
        printf("-- Benvenuto nella GV FIT, il fitness creato dalle donne per le donne! --\n");
        printf("1. Iscrivi un nuovo cliente\n");
        printf("2. Aggiungi una nuova lezione\n");
        printf("3. Crea un abbonamento\n");
        printf("4. Visualizza la disponibilità delle lezioni\n");
        printf("5. Prenota una lezione\n");
        printf("6. Gestione abbonamenti\n");
        printf("7. Gestione prenotazioni\n");
        printf("8. Genera report di utilizzo\n");
        printf("9. Visualizza i clienti iscritti\n");
        printf("0. Esci\n");
        printf("Inserisci la tua scelta [0-9]: ");
        scanf("%d", &scelta);

        // Gestione delle opzioni del menu 
        switch (scelta) {
            
            // Iscrizione di un nuovo cliente
            case 1: {
                clienti = aggiungi_cliente(clienti); 
                printf("Premi Invio per continuare...\n");
                while (getchar() != '\n'); // Pulisce eventuali caratteri residui
                getchar();  // Attende che venga premuto Invio dall'utente
                break;
            }
            
            // Inserimento di una nuova lezione
            case 2: {
                lezioni = aggiungi_lezione(lezioni);
                printf("Premi Invio per continuare...\n");
                while (getchar() != '\n'); 
                getchar();  
                break;
            }
            
            // Creazione di un nuovo abbonamento 
            case 3: {
                abbonamenti = crea_abbonamento(abbonamenti, clienti);
                printf("Premi Invio per continuare...\n");
                while (getchar() != '\n'); 
                getchar();  
                break;
            }
            
            // Visualizzazione della disponibilità delle lezioni
            case 4: {
                lezioni = visualizza_lezione(lezioni);
                printf("Premi Invio per continuare...\n");
                while (getchar() != '\n'); 
                getchar();  
                break;
            }

            // Prenotazione di una lezione
            case 5: {
                int id_cliente, id_lezione;
                printf("Inserisci ID cliente: ");
                scanf("%d", &id_cliente);

                // Controllo se il cliente esiste
                Cliente* cliente_trovato = cerca_cliente(clienti, id_cliente);
                    if (!cliente_trovato) {
                    printf("Cliente con ID %d non trovato. Prenotazione annullata.\n", id_cliente);
                    printf("Premi Invio per continuare...\n");
                    while (getchar() != '\n'); // svuota buffer
                    getchar();
                    break;  // Uscita senza la richiesta dell'id della lezione 
                }           

                printf("Inserisci ID lezione da prenotare: ");
                scanf("%d", &id_lezione);

                    if (prenota_lezione(lezioni, id_lezione, id_cliente)) {
                    prenotazioni = aggiungi_prenotazione(prenotazioni, id_cliente, id_lezione);
                    Lezione* l = lezioni;
                        while (l != NULL && l->id_lezione != id_lezione) {
                        l = l->next;
                    }
                    if (l != NULL) {
                    printf("Prenotazione effettuata per la lezione %s alle %s.\n", l->nome, l->orario);
                    }
                }

                printf("Premi Invio per continuare...\n");
                while (getchar() != '\n'); // svuota buffer
                getchar();
                break;
            }

            // Gestione degli abbonamenti 
            case 6: {
                int id_cliente;
                printf("Inserisci ID cliente per gestione abbonamento: ");
                scanf("%d", &id_cliente);
                abbonamenti = gestisci_abbonamento(abbonamenti, id_cliente);
                printf("Premi Invio per continuare...\n");
                while (getchar() != '\n'); 
                getchar();  
                break;
            }
            
            // Gestione delle prenotazioni
            case 7: {
                int id_cliente;
                printf("Inserisci ID cliente per gestione prenotazioni: ");
                scanf("%d", &id_cliente);
                prenotazioni = gestione_prenotazioni(prenotazioni, id_cliente, lezioni);
                printf("Premi Invio per continuare...\n");
                while (getchar() != '\n'); 
                getchar();  
                break;
            }
            
            // Creazione di un report mensile delle prenotazioni
            case 8: { 
                char mese_anno[8];
                printf("Inserisci mese e anno per il report (MM/AAAA): ");
                scanf("%7s", mese_anno);
                report_mensile(prenotazioni, lezioni, mese_anno) ;
                printf("Premi Invio per continuare...\n");
                while (getchar() != '\n'); 
                getchar();  
                break;
            }
            
            // Visualizzazione dei clienti iscritti alla palestra
            case 9: {
            stampa_clienti(clienti);
            printf("Premi Invio per continuare...\n");
            while (getchar() != '\n'); // pulisci buffer
            getchar();
            break;
            }

            // Uscita dal programma 
            case 0:
                printf("Uscita dal programma. Grazie e a presto!\n");
                break;
                
            // Gestione di eventuali input non validi 
            default:
                printf("Scelta non valida. Riprova.\n");
        }
    // Il ciclo continua finchè l'utente non sceglie di uscire
    } while (scelta != 0);

    return 0;
}
