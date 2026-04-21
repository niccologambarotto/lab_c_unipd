#include <stdio.h>
#define CARTEPERMANO 3

// Definizione dei Valori
typedef enum {
    ASSO, DUE, TRE, QUATTRO, CINQUE,
    SEI, SETTE, OTTO, NOVE, DIECI,
    JACK, DONNA, RE
} Valore;

// Definizione dei Semi
typedef enum{
	CUORI,
	QUADRI,
	FIORI,
	PICCHE
} Seme;

typedef struct{
	Seme seme;
	Valore val;
	} Carta;
	
void stampaMano(Carta *mano);

int main()
{
	Carta mano[CARTEPERMANO];
	mano[0].val = ASSO;
	mano[0].seme = CUORI;
	
	mano[1].val = ASSO;
	mano[1].seme = PICCHE;
	
	mano[2].val = ASSO;
	mano[2].seme = FIORI;
	
	stampaMano(mano);
}

void stampaMano(Carta *mano)
{
	char *nomiSemi[]   = {"Cuori", "Quadri", "Fiori", "Picche"};
	char *nomiValori[] = {"Asso", "Due", "Tre", "Quattro", "Cinque",
                      "Sei", "Sette", "Otto", "Nove", "Dieci",
                      "Jack", "Donna", "Re"};
	for (int i = 0; i < CARTEPERMANO; i++) {
		printf("%s di %s\n", nomiValori[mano[i].val], nomiSemi[mano[i].seme]);
	}
	
}
