#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Utilaj
{
	char *denumire;
	int an, sector;
	struct Utilaj *urm;
}Utlj;

Utlj* introducere(Utlj* prim)
{
	Utlj* q;
	q = (Utlj*)malloc(sizeof(Utlj));
	q->denumire = (char*)malloc(50 * sizeof(char));
	printf("\nIntroduceti denumirea: ");
	scanf_s("%s", q->denumire, 50);
	printf("Introduceti anul: ");
	scanf_s("%d", &q->an);
	printf("Introduceti sectorul: ");
	scanf_s("%d", &q->sector);
	q->urm = prim;
	prim = q;
	return prim;
}

void afisare(Utlj* prim)
{
	Utlj* q;
	q = prim;
	printf("\n");
	while (q != NULL)
	{
		printf("Denumire: %s \tAn: %d \tSector: %d\n", q->denumire, q->an, q->sector);
		q = q->urm;
	}
}

void afisare_an(Utlj* prim)
{
	Utlj* q;
	int an;
	q = prim;
	printf("\nIntroduceti anul: ");
	scanf_s("%d", &an);
	while (q != NULL)
	{
		if(q->an<an)
			printf("Denumire: %s \tAn: %d \tSector: %d\n", q->denumire, q->an, q->sector);
		q = q->urm;
	}
}

void litera_mare(Utlj* prim)
{
	Utlj* q;
	q = prim;
	while (q != NULL)
	{
		if (97 <= q->denumire[0] && q->denumire[0] <= 123)
			q->denumire[0] = toupper(q->denumire[0]);
		q = q->urm;
	}
	afisare(prim);
}

void salvare_fisier(Utlj* prim)
{
	FILE* fisier;
	fisier = fopen("utilaj_sector.txt", "wt");
	Utlj* q;
	q = prim;
	int sect;
	printf("\nIntroduceti sectorul: ");
	scanf_s("%d", &sect);
	while (q != NULL)
	{
		if (q->sector == sect)
			fprintf(fisier, "Denumire: %s \tAn: %d \tSector: %d\n", q->denumire, q->an, q->sector);
		q = q->urm;
	}
	fclose(fisier);
}

Utlj* stergere(Utlj* prim)
{
	Utlj* q, * p;
	char denum[50];
	printf("Introduceti denumirea: ");
	scanf_s("%s", denum, 50);
	if (prim != NULL)
	{
		if (strcmp(prim->denumire, denum) == 0)
		{
			q = prim;
			prim = prim->urm;
			free(q->denumire);
			free(q);
			return prim;
		}
		q = prim;
		while (q->urm != NULL && strcmp(q->urm->denumire, denum) != 0)
			q = q->urm;
		if (q->urm != NULL)
		{
			p = q->urm;
			q->urm = q->urm->urm;
			free(p->denumire);
			free(p);
		}
		return prim;
	}
	else return prim;
}

int main()
{
	Utlj* prim;
	prim = NULL;
	int optiune;
	printf("1. Introducerea unui utilaj nou\n");
	printf("2. Afisarea utilajelor din depozit\n");
	printf("3. Afisarea utilajelor cu au anul fabicatiei mai mic decat un an dat de la tastatura\n");
	printf("4. Transformarea primei litere din denumirea utilajelor in litera mare\n");
	printf("5. Salvarea tuturor utilajelor dintr-un anumit sector intr-un fisier text\n");
	printf("6. Stergerea unui utilaj precizat prin denumire\n");
	printf("7. Iesire\n");
	do {
		printf("Introduceti optiunea: ");
		scanf_s("%d", &optiune);
		switch (optiune)
		{
		case 1:
			prim=introducere(prim);
			break;
		case 2:
			afisare(prim);
			break;
		case 3:
			afisare_an(prim);
			break;
		case 4:
			litera_mare(prim);
			break;
		case 5:
			salvare_fisier(prim);
			break;
		case 6:
			prim = stergere(prim);
			break;
		case 7:
			exit(0);
			break;
		default:
			printf("Optiune invalida!");
			break;
		}
	} while (1);
}