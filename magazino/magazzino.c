#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =====================
// DEFINIZIONE STRUCT
// =====================
typedef struct {
    int codice;
    char nome[50];
    int quantita;
    float prezzo;
} Prodotto;

typedef struct {
    Prodotto** prodotti;  // array dinamico di puntatori a Prodotto
    int dimensione;       // numero attuale di prodotti
} Magazzino;

// =====================
// FIRME DELLE FUNZIONI
// =====================

// Inizializza il magazzino
Magazzino* creaMagazzino();

// Aggiunge un prodotto al magazzino
void aggiungiProdotto(Magazzino* mag, int codice, char* nome, int quantita, float prezzo);

// Stampa tutti i prodotti del magazzino
void stampaMagazzino(Magazzino* mag);

// Cerca un prodotto per codice, restituisce il puntatore al prodotto o NULL
Prodotto* cercaProdotto(Magazzino* mag, int codice);

// Libera tutta la memoria
void liberaMagazzino(Magazzino* mag);

// =====================
// MAIN DI TEST
// =====================
int main()
{
    // Creazione magazzino
    Magazzino* mag = creaMagazzino();

    // Aggiunta prodotti
    aggiungiProdotto(mag, 1, "Martello", 10, 12.99);
    aggiungiProdotto(mag, 2, "Cacciavite", 25, 5.49);
    aggiungiProdotto(mag, 3, "Trapano", 5, 89.99);

    // Stampa magazzino
    printf("=== MAGAZZINO ===\n");
    stampaMagazzino(mag);

    // Ricerca prodotto
    printf("\n=== RICERCA PRODOTTO (codice 2) ===\n");
    Prodotto* p = cercaProdotto(mag, 2);
    if(p != NULL)
        printf("Trovato: %s - %.2f euro\n", p->nome, p->prezzo);
    else
        printf("Prodotto non trovato!\n");

    // Ricerca prodotto inesistente
    printf("\n=== RICERCA PRODOTTO (codice 99) ===\n");
    p = cercaProdotto(mag, 99);
    if(p != NULL)
        printf("Trovato: %s - %.2f euro\n", p->nome, p->prezzo);
    else
        printf("Prodotto non trovato!\n");

    // Liberazione memoria
    liberaMagazzino(mag);

    return 0;
}

// =====================
// IMPLEMENTA QUI 👇
// =====================

Magazzino* creaMagazzino()
{
    // TODO
}

void aggiungiProdotto(Magazzino* mag, int codice, char* nome, int quantita, float prezzo)
{
    // TODO
}

void stampaMagazzino(Magazzino* mag)
{
    // TODO
}

Prodotto* cercaProdotto(Magazzino* mag, int codice)
{
    // TODO
}

void liberaMagazzino(Magazzino* mag)
{
    // TODO
}
