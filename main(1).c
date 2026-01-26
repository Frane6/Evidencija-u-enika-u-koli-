#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

int main(void) {
    Student* Studenti = NULL;
    int Izbor;

    do {
        PrikaziIzbornik();
        if (scanf("%d", &Izbor) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (Izbor) {
        case 1:
            UnesiStudenta(&Studenti, &BrojStudenata);
            break;
        case 2:
            PrikaziStudente(Studenti, BrojStudenata);
            break;
        case 3:
            AzurirajStudenta(Studenti, BrojStudenata);
            break;
        case 4:
            ObrisiStudenta(Studenti, BrojStudenata);
            break;
        case 5:
            SpremiUDatoteku(Studenti, BrojStudenata);
            break;
        case 6:
            UcitajIzDatoteke(&Studenti, &BrojStudenata);
            break;
        case 7:
            SortirajStudente(Studenti, BrojStudenata);
            break;
        case 8: {
            int Id;
            printf("Unesite ID studenta za pretragu: ");
            if (scanf("%d", &Id) != 1) break;
            Student* S = PretraziStudenta(Studenti, BrojStudenata, Id);
            if (S && S->Aktivan) {
                printf("%d | %s %s | %s | %.2f | Godina %d | %s\n",
                    S->IdStudenta, S->Ime, S->Prezime, S->Grad,
                    S->ProsjekOcjena, S->Godina,
                    S->Spol == Musko ? "Muško" : S->Spol == Zensko ? "Žensko" : "Ostalo");
            }
            else {
                printf("Student nije pronađen.\n");
            }
            break;
        }
        case 9:
            printf("Izlaz iz programa.\n");
            break;
        case 10: { // Brisanje datoteke
            char naziv[50];
            printf("Unesite naziv datoteke za brisanje: ");
            scanf("%s", naziv);
            ObrisiDatoteku(naziv);
            break;
        }
        case 11: { // Kopiranje datoteke
            char izvor[50], odrediste[50];
            printf("Unesite naziv izvorne datoteke: ");
            scanf("%s", izvor);
            printf("Unesite naziv odredišne datoteke: ");
            scanf("%s", odrediste);
            KopirajDatoteku(izvor, odrediste);
            break;
        }
        case 12: { // Preimenovanje datoteke
            PreimenujDatoteku("stari.dat", "novi.dat");
            break;
        }
        default:
            printf("Neispravan izbor.\n");
        }
    } while (Izbor != 9);

    OslobodiMemoriju(&Studenti);
    return 0;
}
