#include <stdio.h>
#include <string.h>
#define NCONTATTI 4

typedef enum{
	AMICO,
	FAMILIARE,
	COLLEGA
} Tipo;

typedef struct{
	char nome[50];
	char numero[20];
	Tipo tipo;
} Contatto;

void stampaRubrica(Contatto *rubrica);

int main()
{
	Contatto rubrica[NCONTATTI];
	
	//Primo contatto
	strcpy(rubrica[0].nome, "Marco Contarin");
	strcpy(rubrica[0].numero, "334-5472833");
	rubrica[0].tipo = AMICO;
	
	//Secondo contatto
	strcpy(rubrica[1].nome,"Bro");
	strcpy(rubrica[1].numero, "334-4534333");
	rubrica[1].tipo = FAMILIARE;
	
	//Terzo contatto
	strcpy(rubrica[2].nome, "Salah");
	strcpy(rubrica[2].numero, "353-3245678");
	rubrica[2].tipo = COLLEGA;
	
	//Quarto contatto
	strcpy(rubrica[3].nome, "Alessandro Colonna");
	strcpy(rubrica[3].numero, "345-4225457");
	rubrica[3].tipo = AMICO;
	stampaRubrica(rubrica);
}

void stampaRubrica(Contatto *rubrica)
{
	char *nomiContatti[] = {"Amico", "Familiare", "Collega"};
	printf("---RUBRICA---\n");
	for(int i = 0; i < NCONTATTI; i++)
	{
		printf("Nome: %s\nNumero: %s\nTipo: %s\n--------------\n",
			rubrica[i].nome, rubrica[i].numero, nomiContatti[rubrica[i].tipo]);
	}
}
