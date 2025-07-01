#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

int brojStudenata = 0;

typedef enum {
    IZBORNIK_UNOS = 1,
    IZBORNIK_PRIKAZ,
    IZBORNIK_AZURIRANJE,
    IZBORNIK_BRISANJE,
    IZBORNIK_SPREMANJE,
    IZBORNIK_UCITAVANJE,
    IZBORNIK_SORTIRANJE,
    IZBORNIK_PRETRAGA,
    IZBORNIK_IZLAZ
} Izbor;

int main(void) {
    Student *studenti = NULL;
    int izbor;

    do {
        prikaziIzbornik();
        if (scanf("%d", &izbor) != 1) {
            fprintf(stderr, "Neispravan unos.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (izbor) {
            case IZBORNIK_UNOS:
                unesiStudenta(&studenti, &brojStudenata);
                break;
            case IZBORNIK_PRIKAZ:
                prikaziStudente(studenti, brojStudenata);
                break;
            case IZBORNIK_AZURIRANJE:
                azurirajStudenta(studenti, brojStudenata);
                break;
            case IZBORNIK_BRISANJE:
                obrisiStudenta(studenti, brojStudenata);
                break;
            case IZBORNIK_SPREMANJE:
                spremiUDatoteku(studenti, brojStudenata);
                break;
            case IZBORNIK_UCITAVANJE:
                ucitajIzDatoteke(&studenti, &brojStudenata);
                break;
            case IZBORNIK_SORTIRANJE:
                sortirajStudente(studenti, brojStudenata);
                break;
            case IZBORNIK_PRETRAGA: {
                int id;
                printf("Unesite ID studenta za pretragu: ");
                if (scanf("%d", &id) != 1) break;
                Student *s = pretraziStudenta(studenti, brojStudenata, id);
                if (s && s->aktivan) {
                    printf("%d | %s %s | %s | %.2f | Godina %d | %s\n",
                           s->idStudenta, s->ime, s->prezime, s->grad,
                           s->prosjekOcjena, s->godina,
                           s->spol == MUSKO ? "Muško" : s->spol == ZENSKO ? "Žensko" : "Ostalo");
                } else {
                    printf("Student nije pronađen.\n");
                }
                break;
            }
            case IZBORNIK_IZLAZ:
                break;
            default:
                printf("Neispravan izbor.\n");
        }

    } while (izbor != IZBORNIK_IZLAZ);

    oslobodiMemoriju(&studenti);
    return 0;
}
