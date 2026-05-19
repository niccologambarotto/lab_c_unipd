#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =====================
// DEFINIZIONE STRUCT
// =====================
typedef struct {
    int id;
    char titolo[100];
    char genere[50];
    int anno;
    float valutazione;  // da 0.0 a 10.0
} Film;

typedef struct {
    Film** films;
    int dimensione;
} Catalogo;

// =====================
// FIRME DELLE FUNZIONI
// =====================

// Inizializza il catalogo
Catalogo* creaCatalogo();

// Aggiunge un film al catalogo
void aggiungiFilm(Catalogo* cat, int id, char* titolo, char* genere, int anno, float valutazione);

// Stampa tutti i film del catalogo
void stampaCatalogo(Catalogo* cat);

// Cerca un film per titolo, restituisce il puntatore al film o NULL
Film* cercaFilmPerTitolo(Catalogo* cat, char* titolo);

// Restituisce tutti i film di un certo genere (array di puntatori)
// aggiorna il valore di 'trovati' con il numero di film trovati
Film** filtraPerGenere(Catalogo* cat, char* genere, int* trovati);

// Libera tutta la memoria
void liberaCatalogo(Catalogo* cat);

// =====================
// MAIN DI TEST
// =====================
int main()
{
    // Creazione catalogo
    Catalogo* cat = creaCatalogo();

    // Aggiunta film
    aggiungiFilm(cat, 1, "Inception", "Fantascienza", 2010, 8.8);
    aggiungiFilm(cat, 2, "Il Padrino", "Drammatico", 1972, 9.2);
    aggiungiFilm(cat, 3, "Interstellar", "Fantascienza", 2014, 8.6);
    aggiungiFilm(cat, 4, "Joker", "Drammatico", 2019, 8.4);
    aggiungiFilm(cat, 5, "Avatar", "Fantascienza", 2009, 7.8);

    // Stampa catalogo
    printf("=== CATALOGO FILM ===\n");
    stampaCatalogo(cat);

    // Ricerca per titolo
    printf("\n=== RICERCA PER TITOLO (Joker) ===\n");
    Film* f = cercaFilmPerTitolo(cat, "Joker");
    if(f != NULL)
        printf("Trovato: %s (%d) - %.1f/10\n", f->titolo, f->anno, f->valutazione);
    else
        printf("Film non trovato!\n");

    // Ricerca per titolo inesistente
    printf("\n=== RICERCA PER TITOLO (Titanic) ===\n");
    f = cercaFilmPerTitolo(cat, "Titanic");
    if(f != NULL)
        printf("Trovato: %s (%d) - %.1f/10\n", f->titolo, f->anno, f->valutazione);
    else
        printf("Film non trovato!\n");

    // Filtro per genere
    printf("\n=== FILM DI FANTASCIENZA ===\n");
    int trovati = 0;
    Film** fantascienza = filtraPerGenere(cat, "Fantascienza", &trovati);
    for(int i = 0; i < trovati; i++)
        printf("- %s (%d)\n", fantascienza[i]->titolo, fantascienza[i]->anno);
    free(fantascienza);

    // Liberazione memoria
    liberaCatalogo(cat);

    return 0;
}

// =====================
// IMPLEMENTA QUI 👇
// =====================

Catalogo* creaCatalogo()
{
	Catalogo* cat = malloc(sizeof(Catalogo));
	if(cat == NULL)
	{
		printf("Errore nell'allocazione della memoria");
		return NULL;
	}
	cat->dimensione = 0;
	cat->films = NULL;
	return cat;
}

void aggiungiFilm(Catalogo* cat, int id, char* titolo, char* genere, int anno, float valutazione)
{
	Film** temp = realloc(cat->films, (cat->dimensione + 1) * sizeof(Film*));
	if(temp == NULL)
	{
		printf("Errore nell'allocazione della memoria");
	}
	cat->films = temp;
	cat->films[cat->dimensione] = malloc(sizeof(Film));
	cat->films[cat->dimensione]->id = id;
	strcpy(cat->films[cat->dimensione]->titolo, titolo);
	strcpy(cat->films[cat->dimensione]->genere, genere);
	cat->films[cat->dimensione]->anno = anno;
	cat->films[cat->dimensione]->valutazione = valutazione;
	cat->dimensione++;
}

void stampaCatalogo(Catalogo* cat)
{
	printf("Stampa del catalogo:\n");
	for(int i = 0; i < cat->dimensione; i++)
	{
		printf("Indice: %d | Titolo: %s | Genere: %s | Anno: %d | Valutazione: %.1f\n",
			cat->films[i]->id, cat->films[i]->titolo, cat->films[i]->genere, cat->films[i]->anno, cat->films[i]->valutazione);
	}
}

Film* cercaFilmPerTitolo(Catalogo* cat, char* titolo)
{
	for(int i = 0; i < cat->dimensione; i++)
	{
		if(strcmp(cat->films[i]->titolo, titolo) == 0)
		{
			return cat->films[i];
		}
	}
	return NULL;
}

Film** filtraPerGenere(Catalogo* cat, char* genere, int* trovati)
{
	Film** filmconquelgenere = malloc((cat->dimensione) * sizeof(Film*));
	if(filmconquelgenere == NULL)
	{
		printf("Errore nell'allocazione della memoria");
		return NULL;
	}
	*trovati = 0;
	for(int i = 0; i < cat->dimensione; i++)
	{
		if(strcmp(cat->films[i]->genere, genere) == 0)
		{
			filmconquelgenere[*trovati] = cat->films[i];
			(*trovati) ++;
		}
	}
	return filmconquelgenere;
}

void liberaCatalogo(Catalogo* cat)
{
	for(int i = 0; i < cat->dimensione; i++)
	{
		free(cat->films[i]);
	}
	free(cat->films);
	free(cat);
}
