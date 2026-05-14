#include <stdio.h>
#include <stdlib.h>

void inputUtente(int* n, int* m)
{
	printf("Digitare n e m: ");
	scanf("%d %d", n, m);
}

int main()
{
	int n, m;
	//Acquisizione grandezza della matrice
	inputUtente(&n, &m);
	
	//Allocazione della memoria
	int** matrice = (int**) malloc(n * sizeof(int*));
	//Gestione errore
	if(matrice == NULL) 
	{
		printf("Errore nell'allocazione della memoria");
		return -1;
	}
	for(int i = 0; i < n; i++) 
	{
		matrice[i] = (int*) malloc(m * sizeof(int));
			//Gestione errore
		if(matrice[i] == NULL) 
		{
			printf("Errore nell'allocazione della memoria");
			return -1;
		}
	}
	
	//Riempire la matrice
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			matrice[i][j] = i * m + j;
		}
	}
	
	//Stampare la matrice
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			printf("|%d|", matrice[i][j]);
		}
		printf("\n");
	}
	
	//Liberare la memoria
	for(int i = 0; i < n; i++) 
	{
		free(matrice[i]);
	}
	free(matrice);
	return 0;
}
