#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =====================
// DEFINIZIONE STRUCT
// =====================
typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    int id;
    char cliente[100];
    int numeroCamera;
    Data checkIn;
    Data checkOut;
} Prenotazione;

typedef struct {
    Prenotazione** prenotazioni;
    int dimensione;
} Hotel;

// =====================
// FIRME DELLE FUNZIONI
// =====================

// Inizializza l'hotel
Hotel* creaHotel();

// Aggiunge una prenotazione
void aggiungiPrenotazione(Hotel* hotel, int id, char* cliente, int numeroCamera,
                          Data checkIn, Data checkOut);

// Stampa tutte le prenotazioni
void stampaHotel(Hotel* hotel);

// Cerca prenotazioni per cliente, restituisce array di puntatori
// aggiorna 'trovate' con il numero di prenotazioni trovate
Prenotazione** cercaPerCliente(Hotel* hotel, char* cliente, int* trovate);

// Controlla se una camera è libera in una certa data
// restituisce 1 se libera, 0 se occupata
int isCameraLibera(Hotel* hotel, int numeroCamera, Data data);

// Libera tutta la memoria
void liberaHotel(Hotel* hotel);

// =====================
// FUNZIONI DI UTILITA'
// =====================

// Confronta due date: restituisce 1 se a è precedente a b, 0 altrimenti
int dataPrecedente(Data a, Data b)
{
    if(a.anno != b.anno) return a.anno < b.anno;
    if(a.mese != b.mese) return a.mese < b.mese;
    return a.giorno < b.giorno;
}

// =====================
// MAIN DI TEST
// =====================
int main()
{
    Hotel* hotel = creaHotel();

    // Aggiunta prenotazioni
    aggiungiPrenotazione(hotel, 1, "Mario Rossi", 101,
                        (Data){1, 6, 2024}, (Data){5, 6, 2024});
    aggiungiPrenotazione(hotel, 2, "Luigi Bianchi", 202,
                        (Data){3, 6, 2024}, (Data){8, 6, 2024});
    aggiungiPrenotazione(hotel, 3, "Mario Rossi", 303,
                        (Data){10, 6, 2024}, (Data){15, 6, 2024});
    aggiungiPrenotazione(hotel, 4, "Anna Verdi", 101,
                        (Data){10, 6, 2024}, (Data){12, 6, 2024});

    // Stampa
    printf("=== PRENOTAZIONI HOTEL ===\n");
    stampaHotel(hotel);

    // Cerca per cliente
    printf("\n=== PRENOTAZIONI DI Mario Rossi ===\n");
    int trovate = 0;
    Prenotazione** pren = cercaPerCliente(hotel, "Mario Rossi", &trovate);
    for(int i = 0; i < trovate; i++)
        printf("Camera %d | Check-in: %02d/%02d/%d | Check-out: %02d/%02d/%d\n",
               pren[i]->numeroCamera,
               pren[i]->checkIn.giorno, pren[i]->checkIn.mese, pren[i]->checkIn.anno,
               pren[i]->checkOut.giorno, pren[i]->checkOut.mese, pren[i]->checkOut.anno);
    free(pren);

    // Controlla disponibilità camera
    printf("\n=== DISPONIBILITA' CAMERA 101 il 3/6/2024 ===\n");
    Data dataTest = {3, 6, 2024};
    if(isCameraLibera(hotel, 101, dataTest))
        printf("Camera 101 e' libera!\n");
    else
        printf("Camera 101 e' occupata!\n");

    printf("\n=== DISPONIBILITA' CAMERA 303 il 12/6/2024 ===\n");
    dataTest = (Data){12, 6, 2024};
    if(isCameraLibera(hotel, 303, dataTest))
        printf("Camera 303 e' libera!\n");
    else
        printf("Camera 303 e' occupata!\n");

    // Liberazione memoria
    liberaHotel(hotel);

    return 0;
}

// =====================
// IMPLEMENTA QUI 👇
// =====================

Hotel* creaHotel()
{
	Hotel* hotel = malloc(sizeof(Hotel));
	if(hotel == NULL)
	{
		printf("Errore nell'allocazione della memoria");
		return NULL;
	}
	hotel->prenotazioni = NULL;
	hotel->dimensione = 0;
	return hotel;
}

void aggiungiPrenotazione(Hotel* hotel, int id, char* cliente, int numeroCamera,
                          Data checkIn, Data checkOut)
{
	Prenotazione** temp = realloc(hotel->prenotazioni, (hotel->dimensione + 1) * sizeof(Prenotazione*));
	if(temp == NULL)
	{
		printf("Errore nell'allocazione della memoria");
	}
	hotel->prenotazioni = temp;
	hotel->prenotazioni[hotel->dimensione] = malloc(sizeof(Prenotazione));
	hotel->prenotazioni[hotel->dimensione]->id = id;
	strcpy(hotel->prenotazioni[hotel->dimensione]->cliente, cliente);
	hotel->prenotazioni[hotel->dimensione]->numeroCamera = numeroCamera;
	hotel->prenotazioni[hotel->dimensione]->checkIn = checkIn;
	hotel->prenotazioni[hotel->dimensione]->checkOut = checkOut;
	hotel->dimensione++;
}

void stampaHotel(Hotel* hotel)
{
	printf("Stampa delle prenotazioni:\n");
	for(int i = 0; i < hotel->dimensione; i++)
	{
		printf("ID: %d | Cliente: %s | N°Camera: %d | Check-In: %d-%d-%d | Check-out: %d-%d-%d\n",
		hotel->prenotazioni[i]->id, hotel->prenotazioni[i]->cliente, hotel->prenotazioni[i]->numeroCamera, 
		hotel->prenotazioni[i]->checkIn.giorno, hotel->prenotazioni[i]->checkIn.mese, hotel->prenotazioni[i]->checkIn.anno,
		hotel->prenotazioni[i]->checkOut.giorno,hotel->prenotazioni[i]->checkOut.mese, hotel->prenotazioni[i]->checkOut.anno);
	}
}

Prenotazione** cercaPerCliente(Hotel* hotel, char* cliente, int* trovate)
{
	Prenotazione** prentoazioniCliente = malloc((hotel->dimensione) * sizeof(Prenotazione*));
	if(prentoazioniCliente == NULL)
	{
		printf("Errore nell'allocazione della memoria");
		return NULL;
	}
	*trovate = 0;
	for(int i = 0; i < hotel->dimensione; i++)
	{
		if(strcmp(hotel->prenotazioni[i]->cliente, cliente) == 0)
		{
			prentoazioniCliente[*trovate] = hotel->prenotazioni[i];
			(*trovate) ++;
		}
	}
	return prentoazioniCliente;
}

int isCameraLibera(Hotel* hotel, int numeroCamera, Data data)
{
    for(int i = 0; i < hotel->dimensione; i++)
    {
        if(hotel->prenotazioni[i]->numeroCamera == numeroCamera)
        {
            // la camera è OCCUPATA se data è nell'intervallo
            if(!dataPrecedente(data, hotel->prenotazioni[i]->checkIn) &&
                dataPrecedente(data, hotel->prenotazioni[i]->checkOut))
            {
                return 0;  // occupata!
            }
        }
    }
    return 1;  // libera!
}

void liberaHotel(Hotel* hotel)
{
	for(int i = 0; i < hotel->dimensione; i++)
	{
		free(hotel->prenotazioni[i]);
	}
	free(hotel->prenotazioni);
	free(hotel);
}
