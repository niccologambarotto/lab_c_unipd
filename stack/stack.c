#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* Definire una struct Nodo con i campi:

valore (intero)
next → puntatore al nodo successivo */

typedef struct Nodo
{
	int valore;
	struct Nodo *next;
}Nodo;

/* Definire una struct Stack con il campo:

top → puntatore al nodo in cima alla pila */

typedef struct Stack
{
	Nodo *top;
}Stack;

/* Implementare le seguenti funzioni:

inizializza_stack(...) → inizializza lo stack a vuoto
push(...) → aggiunge un elemento in cima
pop(...) → rimuove e restituisce il valore in cima
peek(...) → restituisce il valore in cima senza rimuoverlo
is_empty(...) → controlla se lo stack è vuoto
stampa_stack(...) → stampa tutti gli elementi */

void inizializza_stack(Stack *s)
{
	s->top = NULL;
}

void push(Stack *s, int valore)
{
	Nodo* n = malloc(sizeof(Nodo));
	if (n == NULL)
	{
	    	printf("Errore: memoria insufficiente!\n");
	    	return;
	}
	n->valore = valore;
	n->next = s->top;
	s->top = n;
}

int is_empty(Stack *s)
{
	return s->top == NULL;  // restituisce direttamente 1 o 0
}

int pop(Stack *s)
{
	if(!is_empty(s))
	{
		Nodo* temp = s->top;
		s->top = s->top->next;
		int val = temp->valore;
		free(temp);
		return val;
	}
	else {return 0;}
}

int peek(Stack *s)
{
	if(!is_empty(s))
	{
		return s->top->valore;
	}
	else {return 0;}
}

void stampa_stack(Stack *s)
{
    if(is_empty(s))
    {
        printf("Stack vuoto\n");
        return;
    }
    Nodo* temp = s->top;
    while(temp != NULL)  // ci fermiamo quando temp è NULL
    {
        printf("Stampa: %d\n", temp->valore);
        temp = temp->next;
    }
}

int main()
{
    Stack s;
    inizializza_stack(&s);

    // Test push
    printf("=== PUSH 1, 2, 3 ===\n");
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    stampa_stack(&s);

    // Test peek
    printf("\n=== PEEK ===\n");
    printf("Valore in cima: %d\n", peek(&s));
    printf("Stack dopo peek:\n");
    stampa_stack(&s);  // deve essere uguale a prima

    // Test pop
    printf("\n=== POP ===\n");
    printf("Valore rimosso: %d\n", pop(&s));
    printf("Stack dopo pop:\n");
    stampa_stack(&s);

    // Test stack vuoto
    printf("\n=== SVUOTO LO STACK ===\n");
    pop(&s);
    pop(&s);
    pop(&s);  // questo dovrebbe trovare lo stack vuoto
    stampa_stack(&s);

    return 0;
}
