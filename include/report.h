#ifndef REPORT_H
#define REPORT_H

#include "prenotazione.h"
#include "lezione.h"

// Struttura per contare le prenotazioni per ogni lezione
typedef struct Report {
    char nome_lezione [50]; //Nome della lezione a cui si riferisce il conteggio
    int conteggio; //Numero di prenotazioni effettuate 
    struct Report* next; // Puntatore al prossimo nodo della lista 
} Report; 

/*
* Funzione: report_mensile
* ----------------------------------
* Genera un report mensile basato sulle prenotazioni effettuate, mostrando il numero
* di partecipanti per ciascuna lezione, ordinate in modo decrescente per frequenza.
*
* Parametri:
*   prenotazioni: puntatore alla lista delle prenotazioni effettuate.
*   lezioni: puntatore alla lista delle lezioni disponibili.
*   mese_anno: stringa nel formato 'mm/aaaa' che rappresenta il mese e l'anno da analizzare.
*
* Pre-condizione:
*   Le date delle lezioni devono essere nel formato gg/mm/aaaa.
*   La stringa 'mese_anno' deve essere esattamente lunga 7 caratteri.
*   Le liste di prenotazioni e lezioni possono essere vuote o contenere più elementi.
*
* Post-condizione:
*   Viene stampato a schermo un elenco delle lezioni svolte nel mese/anno indicato,
*   accompagnato dal numero di prenotazioni per ciascuna lezione.
*   L'elenco è ordinato in ordine decrescente di partecipazione.
*   Se non sono presenti lezioni prenotate in quel mese, viene mostrato un messaggio informativo.
*   Tutta la memoria allocata per la struttura del report viene liberata prima dell'uscita.
*
* Ritorna:
*   Nessun valore di ritorno, essendo di tipo void, e l’output è solo prodotto a video.
*/
void report_mensile(Prenotazione* prenotazioni, Lezione* lezioni, const char* mese_anno);

#endif