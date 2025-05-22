#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "funkcije.h"

static void prikaziIzbornik() {
	printf("\n--- IZBORNIK ---\n");
	printf("1. Dodaj ucenika\n");
	printf("2. Prikazi sve ucenike\n");
	printf("3. Azuriraj ucenika\n");
	printf("4. Obrisi ucenika\n");
	printf("5. Pretrazi ucenika\n");
	printf("0. Izlaz\n");
	printf("Odabir: ");
}

int main() {
	int izbor;

	do {
		prikaziIzbornik();
		scanf("%d", &izbor);

		switch ((IzbornikOpcije)izbor) {
		case DODAJ_UCENIKA: dodajUcenika(); break;
		case PRIKAZI_UCENIKE: prikaziUcenike(); break;
		case AZURIRAJ_UCENIKA: azurirajUcenika(); break;
		case OBRISI_UCENIKA: obrisiUcenika(); break;
		case PRETRAZI_UCENIKA: pretraziUcenika(); break;
		case IZLAZ: printf("Izlaz iz programa.\n"); break;
		default: printf("Neispravan unos!\n");
		}
	} while (izbor != 0);

	return 0;
}