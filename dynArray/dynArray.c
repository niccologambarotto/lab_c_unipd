#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct DynArray
{
	int *data;
	int size;
	int capacity;
}DynArray;

void inizializza(DynArray *arr, int capacity_iniziale)
{
    arr->data = malloc(sizeof(int) * capacity_iniziale);
    if(arr->data == NULL)
    {
        printf("Errore: memoria insufficiente!\n");
        return;
    }
    arr->capacity = capacity_iniziale;
    arr->size = 0;  
}

// aggiunge un elemento in fondo, se l'array è pieno raddoppia la capacità con realloc
void push_back(DynArray *arr, int valore)
{
	if(arr->size == arr->capacity) 
	{
		int *temp = realloc(arr->data, sizeof(int) * 2 *arr->capacity);
		if(temp == NULL) 
		{
            		printf("Errore: realloc fallita!\n");
            		return;
		}
		arr->data = temp;
		arr->capacity *= 2;
	}
	arr->data[arr->size] = valore;
	arr->size++;
}

// restituisce il valore all'indice specificato
int get(DynArray *arr, int index)
{
	if(index >= 0 && index < arr->size)
   	{
		return arr->data[index];
	}
	printf("Errore: indice %d fuori range!\n", index);
	return 0;
}

// modifica il valore all'indice specificato
void set(DynArray *arr, int index, int valore)
{
	if(index >= 0 && index < arr->size)
   	{
		arr->data[index] = valore;
	}
	else {printf("Errore: indice %d fuori range!\n", index);}
}

void stampa(DynArray *arr)
{
	for(int i = 0; i < arr->size; i++)
	{
		printf("Stampa: %d\n", arr->data[i]);
	}
}

void libera(DynArray *arr)
{
	free(arr->data);
	arr->data = NULL;
	arr->size = 0;
	arr->capacity = 0;
}

int main()
{
    DynArray arr;
    inizializza(&arr, 3);

    // Test push_back
    printf("=== PUSH 10, 20, 30 ===\n");
    push_back(&arr, 10);
    push_back(&arr, 20);
    push_back(&arr, 30);
    stampa(&arr);
    printf("Size: %d | Capacity: %d\n", arr.size, arr.capacity);

    // Test realloc automatico
    printf("\n=== PUSH 40, 50 (dovrebbe raddoppiare la capacity) ===\n");
    push_back(&arr, 40);
    push_back(&arr, 50);
    stampa(&arr);
    printf("Size: %d | Capacity: %d\n", arr.size, arr.capacity);

    // Test get
    printf("\n=== GET ===\n");
    printf("Elemento in posizione 0: %d\n", get(&arr, 0));
    printf("Elemento in posizione 2: %d\n", get(&arr, 2));
    get(&arr, 10);  // indice fuori range

    // Test set
    printf("\n=== SET posizione 1 = 999 ===\n");
    set(&arr, 1, 999);
    stampa(&arr);
    set(&arr, 10, 999);  // indice fuori range

    // Test libera
    printf("\n=== LIBERA ===\n");
    libera(&arr);
    printf("Size: %d | Capacity: %d\n", arr.size, arr.capacity);

    return 0;
}
