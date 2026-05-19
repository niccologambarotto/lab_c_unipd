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
// IMPLEMENTA QUI
// =====================

Magazzino* creaMagazzino()
{
	Magazzino* mag = malloc(sizeof(Magazzino));
	//Gestione errore
	if(mag == NULL) 
	{
		printf("Errore nell'allocazione della memoria");
		return NULL;
	}
	mag->dimensione = 0;
	mag->prodotti = NULL;
	return mag;
}

void aggiungiProdotto(Magazzino* mag, int codice, char* nome, int quantita, float prezzo)
{
	//mag->prodotti[mag->dimensione]
	//Riallocazione memoria
	Prodotto** temp = realloc(mag->prodotti, (mag->dimensione + 1) * sizeof(Prodotto*)); 
	if(temp == NULL) 
	{
		printf("Errore nell'allocazione della memoria");
	}
	mag->prodotti = temp;
	mag->prodotti[mag->dimensione] = malloc(sizeof(Prodotto));
	if(mag->prodotti[mag->dimensione] == NULL) 
	{
		printf("Errore nell'allocazione della memoria");
	}
	
	mag->prodotti[mag->dimensione]->codice = codice;
	strcpy(mag->prodotti[mag->dimensione]->nome, nome);
	mag->prodotti[mag->dimensione]->quantita = quantita;
	mag->prodotti[mag->dimensione]->prezzo = prezzo;
	mag->dimensione++;
}

void stampaMagazzino(Magazzino* mag)
{
	printf("Stampa dei prondotti presenti in magazzino:\n");
	for(int i = 0; i < mag->dimensione; i++)
	{
		printf("Codice: %d | Nome: %s | Quantita': %d | Prezzo: %.2f\n", 
			mag->prodotti[i]->codice, mag->prodotti[i]->nome, mag->prodotti[i]->quantita, mag->prodotti[i]->prezzo);
	}
	
}

Prodotto* cercaProdotto(Magazzino* mag, int codice)
{
	for(int i = 0; i < mag->dimensione; i++)
	{
		if(mag->prodotti[i]->codice == codice)
		{
			return mag->prodotti[i];
		}
	}
	return NULL;
}

void liberaMagazzino(Magazzino* mag)
{
	for(int i = 0; i < mag->dimensione; i++)
	{
		free(mag->prodotti[i]);
	}
	free(mag->prodotti);
	free(mag);
}
