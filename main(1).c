#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

typedef enum {
    NOVI_UNOS = 1,
    PRIKAZ,
    IZMJENA,
    DEAKTIVIRAJ,
    SPREMI,
    UCITAJ,
    SORTIRAJ_PREZIME,
    OBRISI_DATOTEKU,
    IZLAZ
} IzbornikOpcije;

int main(void) {
    Ucenik* glava = NULL;
    int odabir = 0;
    const char* filename = "ucenici.bin";
    do {
        printf("\n=== SKOLSKA EVIDENCIJA ===\n");
        printf("1 - Novi unos\n");
        printf("2 - Prikaz svih aktivnih ucenika\n");
        printf("3 - Izmjena podataka ucenika\n");
        printf("4 - Deaktiviraj ucenika\n");
        printf("5 - Spremi u datoteku\n");
        printf("6 - Ucitaj iz datoteke\n");
        printf("7 - Sortiraj po prezimenu (qsort)\n");
        printf("8 - Obrisi datoteku\n");
        printf("9 - Izlaz\n");
        printf("Odaberi opciju: ");
        scanf("%d", &odabir);

        switch (odabir) {
        case NOVI_UNOS: dodajUcenika(&glava); break;
        case PRIKAZ: ispisiUcenike(glava); break;
        case IZMJENA: azurirajUcenika(glava); break;
        case DEAKTIVIRAJ: deaktivirajUcenika(glava); break;
        case SPREMI: spremiUcenike(glava, filename); break;
        case UCITAJ: ucitajUcenike(&glava, filename); break;
        case SORTIRAJ_PREZIME: sortirajPrezimeQsort(glava); break;
        case OBRISI_DATOTEKU:
            if (remove(filename) == 0)
                printf("Datoteka obrisana.\n");
            else
                perror("Greska pri brisanju datoteke.");
            break;
        case IZLAZ:
            oslobodiMemoriju(&glava);
            printf("Kraj programa.\n");
            break;
        default:
            printf("Nepostojeca opcija!\n");
        }
    } while (odabir != IZLAZ);

    return 0;
}
