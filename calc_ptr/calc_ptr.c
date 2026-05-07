#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Operazione
{
	char nome[50];
	double (*operazione)(double, double);
}Operazione;

double addizione(double a, double b)
{
	return a + b;
}

double sottrazione(double a, double b)
{
	return a - b;
}

double moltiplicazione(double a, double b)
{
	return a * b;
}

double divisione(double a, double b)
{
    if(b == 0)
    {
        printf("Errore: divisione per zero!\n");
        return 0;
    }
    return a / b;
}

void esegui(Operazione *op, double a, double b)
{
	printf("Risultato: %.2f\n", op->operazione(a, b));
}

void stampa_menu(Operazione *ops, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%d. %s\n", i, ops[i].nome);
	}
}

int main()
{
    Operazione ops[4];

    // Inizializza le operazioni
    strcpy(ops[0].nome, "addizione");
    ops[0].operazione = addizione;

    strcpy(ops[1].nome, "sottrazione");
    ops[1].operazione = sottrazione;

    strcpy(ops[2].nome, "moltiplicazione");
    ops[2].operazione = moltiplicazione;

    strcpy(ops[3].nome, "divisione");
    ops[3].operazione = divisione;

    // Stampa il menu
    printf("=== CALCOLATRICE ===\n");
    stampa_menu(ops, 4);

    // Chiedi input all'utente
    int scelta;
    double a, b;
    printf("\nScegli operazione (0-3): ");
    scanf("%d", &scelta);

    if(scelta < 0 || scelta > 3)
    {
        printf("Errore: scelta non valida!\n");
        return 1;
    }

    printf("Inserisci primo numero: ");
    scanf("%lf", &a);
    printf("Inserisci secondo numero: ");
    scanf("%lf", &b);

    // Esegui l'operazione scelta
    printf("\n%s tra %.2f e %.2f\n", ops[scelta].nome, a, b);
    esegui(&ops[scelta], a, b);

    return 0;
}
