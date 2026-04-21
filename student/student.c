#include <stdio.h>
#include <string.h>
#define NVOTI 3

typedef enum{
	INFORMATICA, 
	MATEMATICA, 
	FISICA, 
	INGEGNERIA
} Corso;

typedef struct{
	char materia[20];
	int voto;
} Voto;

typedef struct{
	char nome[30];
	char matricola[10];
	Corso corso;
	Voto voti[NVOTI];
} Studente;

void stampaStudente(Studente *s);

float mediaVoti(Studente *s);

int main()
{
	//Creazione dello studente
	Studente mario;
	strcpy(mario.nome, "Mario Rossi");
	strcpy(mario.matricola, "IN0001");
	mario.corso = INGEGNERIA;
	strcpy(mario.voti[0].materia, "Analisi");
	mario.voti[0].voto = 28;
	strcpy(mario.voti[1].materia, "Programmazione");
	mario.voti[1].voto = 30;
	strcpy(mario.voti[2].materia, "Fisica");
	mario.voti[2].voto = 25;
	stampaStudente(&mario);
}

void stampaStudente(Studente *s)
{
	char *nomeCorso[] = {"Informatica", "Matematica", "Fisica", "Ingegneria"};
	// Stampa delle informazioni di base
	printf("Nome: %s\nMatricola: %s\nCorso: %s\n",
		s->nome, s->matricola, nomeCorso[s->corso]);
	printf("Voti:\n");
	// Stampa dei voti
	for(int i = 0; i < NVOTI; i++)
	{
		printf("- %s: %d\n", s->voti[i].materia, s->voti[i].voto);
	}
	//Stampa media dei voti
	printf("Media: %.2f\n", mediaVoti(s));
}
float mediaVoti(Studente *s)
{
	float media = 0.0;
	for(int i = 0; i < NVOTI; i++)
	{
		media = media + s->voti[i].voto;
	}
	media = (float) media/NVOTI;
	return media;
}
