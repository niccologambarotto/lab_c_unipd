#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
	char valore;
	struct Nodo *next;
}Nodo;

void add(Nodo**lista, char c)
{
	if (*lista == NULL)
	{
		*lista = malloc(sizeof(Nodo));
		(*lista)->valore = c;
		(*lista)->next = NULL;
	}
	else
    	{
        		add(&(*lista)->next, c);
    	}
}

int compareLists(Nodo* lis, Nodo* comp)
{
	if(comp == NULL)
	{ printf("Please, add a comparison pointer");}
	if(lis->valore == comp->valore)
	{
		if(lis == NULL)
		{	return 1;}
		else
		{
			return compareLists((lis->next), (comp->next));
		}
	}
	else 
	{
		return 0;
	}
}

void copyReversed(Nodo* lis, Nodo** copy)
{
	if(*copy == NULL)
	{ printf("Please, add a destination pointer");}
}

int checkPalindrome(Nodo*lis)
{
	return 0;
}

int main()
{
	
	return 0;
}
