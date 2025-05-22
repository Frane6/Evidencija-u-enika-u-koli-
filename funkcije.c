#define _CRT_SECURE_NO_WARNINGS
#include "funkcije.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Dinamičko učitavanje svih učenika iz datoteke
int ucitajStudente(Student** ucenici) {
	FILE* fp = fopen(DATA_FILE, "r");
	if (!fp) {
		perror("Greska pri otvaranju datoteke"); 
		return 0;
	}

	int count = 0;
	Student temp;
	while (fscanf(fp, "%d %s %s %f", &temp.id, temp.ime, temp.prezime, &temp.prosjek) == 4) {
		Student* novi = realloc(*ucenici, (count + 1) * sizeof(Student));                       //17
		if (!novi) {
			perror("Greska pri alokaciji memorije");
			fclose(fp);
			return count;
		}
		*ucenici = novi;
		(*ucenici)[count++] = temp;
	}

	fclose(fp);
	return count;
}

int spremiStudente(Student* ucenici, int brojStudenata) {
	FILE* fp = fopen(DATA_FILE, "w");
	if (!fp) {
		perror("Greska pri spremanju datoteke");
		return 0;
	}

	for (int i = 0; i < brojStudenata; i++) {
		fprintf(fp, "%d %s %s %.2f\n", ucenici[i].id, ucenici[i].ime, ucenici[i].prezime, ucenici[i].prosjek);
	}

	fclose(fp);
	return 1;
}

void dodajUcenika() {
	FILE* fp = fopen(DATA_FILE, "a");
	if (!fp) {
		perror("Greska pri otvaranju datoteke");                  //22
		return;
	}

	Student u;
	printf("Unesite ID, ime, prezime, prosjek: ");
	scanf("%d %s %s %f", &u.id, u.ime, u.prezime, &u.prosjek);

	fprintf(fp, "%d %s %s %.2f\n", u.id, u.ime, u.prezime, u.prosjek);
	fclose(fp);
	printf("Ucenik dodan.\n");
}

void prikaziUcenike() {
	Student* ucenici = NULL;
	int broj = ucitajStudente(&ucenici);

	printf("Popis ucenika:\n");
	for (int i = 0; i < broj; i++) {
		printf("ID: %d, Ime: %s, Prezime: %s, Prosjek: %.2f\n",
			ucenici[i].id, ucenici[i].ime, ucenici[i].prezime, ucenici[i].prosjek);
	}

	free(ucenici);
}

void azurirajUcenika() {
	Student* ucenici = NULL;
	int broj = ucitajStudente(&ucenici);
	int trazeniId;
	printf("Unesite ID ucenika za azuriranje: ");
	scanf("%d", &trazeniId);

	int found = 0;
	for (int i = 0; i < broj; i++) {
		if (ucenici[i].id == trazeniId) {
			printf("Unesite novo ime, prezime, prosjek: ");
			scanf("%s %s %f", ucenici[i].ime, ucenici[i].prezime, &ucenici[i].prosjek);
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("Ucenik nije pronadjen.\n");
	}
	else {
		spremiStudente(ucenici, broj);
		printf("Ucenik azuriran.\n");
	}

	free(ucenici);
}

void obrisiUcenika() {
	Student* ucenici = NULL;
	int broj = ucitajStudente(&ucenici);
	int trazeniId;
	printf("Unesite ID ucenika za brisanje: ");
	scanf("%d", &trazeniId);

	int noviBroj = 0;
	Student* novi = malloc(broj * sizeof(Student));
	for (int i = 0; i < broj; i++) {
		if (ucenici[i].id != trazeniId) {
			novi[noviBroj++] = ucenici[i];
		}
	}

	if (noviBroj == broj) {
		printf("Ucenik nije pronadjen.\n");
	}
	else {
		spremiStudente(novi, noviBroj);
		printf("Ucenik obrisan.\n");
	}

	free(ucenici);
	free(novi);
}

void pretraziUcenika() {
	Student* ucenici = NULL;
	int broj = ucitajStudente(&ucenici);
	int trazeniId;
	printf("Unesite ID za pretragu: ");
	scanf("%d", &trazeniId);

	for (int i = 0; i < broj; i++) {
		if (ucenici[i].id == trazeniId) {
			printf("Pronadjen: ID: %d, Ime: %s, Prezime: %s, Prosjek: %.2f\n",
				ucenici[i].id, ucenici[i].ime, ucenici[i].prezime, ucenici[i].prosjek);
			free(ucenici);
			return;
		}
	}

	printf("Ucenik nije pronadjen.\n");
	free(ucenici);
}
