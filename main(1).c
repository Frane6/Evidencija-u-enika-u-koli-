#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

int main(void) {
    Student* Studenti = NULL;
    int Izbor;                    //5

    do {
        PrikaziIzbornik();
        if (scanf("%d", &Izbor) != 1) { while (getchar() != '\n'); continue; }
        switch (Izbor) {
        case 1: UnesiStudenta(&Studenti, &BrojStudenata); break;
        case 2: PrikaziStudente(Studenti, BrojStudenata); break;
        case 3: AzurirajStudenta(Studenti, BrojStudenata); break;
        case 4: ObrisiStudenta(Studenti, BrojStudenata); break;
        case 5: SpremiUDatoteku(Studenti, BrojStudenata); break;
        case 6: UcitajIzDatoteke(&Studenti, &BrojStudenata); break;
        case 7: SortirajStudente(Studenti, BrojStudenata); break;
        case 12: {
            PreimenujDatoteku("stari.dat", "novi.dat");
            break;
        }
        case 8: {
            int Id; printf("Unesite ID: "); if (scanf("%d", &Id) != 1) break;
            Student* S = PretraziStudenta(Studenti, BrojStudenata, Id);
            if (S && S->Aktivan) printf("%d | %s %s\n", S->IdStudenta, S->Ime, S->Prezime);
            else printf("Student nije pronađen.\n");
            break;
        }
        case 9: break;
        
        default: printf("Neispravan izbor.\n");
        }
    } while (Izbor != 9);

    OslobodiMemoriju(&Studenti);
    return 0;
}
