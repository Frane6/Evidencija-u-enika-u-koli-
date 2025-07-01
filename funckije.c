#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

void prikaziIzbornik(void) {
    printf("\n=== IZBORNIK STUDENATA ===\n");
    printf("1 - Unesi novog studenta\n");
    printf("2 - Prikazi sve studente\n");
    printf("3 - Ažuriraj podatke studenta\n");
    printf("4 - Obriši studenta\n");
    printf("5 - Spremi u datoteku\n");
    printf("6 - Učitaj iz datoteke\n");
    printf("7 - Sortiraj studente\n");
    printf("8 - Pretraži po ID-u\n");
    printf("9 - Izlaz\n");
    printf("Odabir: ");
}

void unesiStudenta(Student **studenti, int *broj) {
    Student *privremeno = realloc(*studenti, (*broj + 1) * sizeof(Student));
    if (!privremeno) {
        perror("Greška pri alokaciji memorije");
        return;
    }
    *studenti = privremeno;

    Student *s = &(*studenti)[*broj];

    printf("Unesite ID studenta: ");
    if (scanf("%d", &s->idStudenta) != 1) return;

    printf("Unesite ime: ");
    if (scanf("%s", s->ime) != 1) return;

    printf("Unesite prezime: ");
    if (scanf("%s", s->prezime) != 1) return;

    printf("Unesite grad: ");
    if (scanf("%s", s->grad) != 1) return;

    printf("Unesite prosjek ocjena: ");
    if (scanf("%f", &s->prosjekOcjena) != 1) return;

    printf("Unesite godinu studija: ");
    if (scanf("%d", &s->godina) != 1) return;

    printf("Unesite spol (0 - Muško, 1 - Žensko, 2 - Ostalo): ");
    int spol;
    if (scanf("%d", &spol) != 1 || spol < 0 || spol > 2) return;
    s->spol = (Spol)spol;
    s->aktivan = 1;
    (*broj)++;
}

void prikaziStudente(const Student *studenti, int broj) {
    for (int i = 0; i < broj; i++) {
        if (studenti[i].aktivan) {
            printf("%d | %s %s | %s | %.2f | Godina %d | %s\n",
                   studenti[i].idStudenta, studenti[i].ime, studenti[i].prezime,
                   studenti[i].grad, studenti[i].prosjekOcjena, studenti[i].godina,
                   studenti[i].spol == MUSKO ? "Muško" : studenti[i].spol == ZENSKO ? "Žensko" : "Ostalo");
        }
    }
}

void azurirajStudenta(Student *studenti, int broj) {
    int id;
    printf("Unesite ID studenta za ažuriranje: ");
    if (scanf("%d", &id) != 1) return;

    for (int i = 0; i < broj; i++) {
        if (studenti[i].idStudenta == id && studenti[i].aktivan) {
            printf("Unesite novi grad: ");
            if (scanf("%s", studenti[i].grad) != 1) return;

            printf("Unesite novi prosjek: ");
            if (scanf("%f", &studenti[i].prosjekOcjena) != 1) return;

            printf("Unesite novu godinu: ");
            if (scanf("%d", &studenti[i].godina) != 1) return;
            return;
        }
    }
    printf("Student nije pronađen.\n");
}

void obrisiStudenta(Student *studenti, int broj) {
    int id;
    printf("Unesite ID studenta za brisanje: ");
    if (scanf("%d", &id) != 1) return;

    for (int i = 0; i < broj; i++) {
        if (studenti[i].idStudenta == id && studenti[i].aktivan) {
            studenti[i].aktivan = 0;
            printf("Student obrisan.\n");
            return;
        }
    }
    printf("Student nije pronađen.\n");
}

void spremiUDatoteku(const Student *studenti, int broj) {
    FILE *dat = fopen(NAZIV_DATOTEKE, "wb");
    if (!dat) {
        perror("Pogreška prilikom otvaranja datoteke");
        return;
    }

    fwrite(&broj, sizeof(int), 1, dat);
    fwrite(studenti, sizeof(Student), broj, dat);
    fclose(dat);
    printf("Podaci spremljeni u datoteku.\n");
}

void ucitajIzDatoteke(Student **studenti, int *broj) {
    FILE *dat = fopen(NAZIV_DATOTEKE, "rb");
    if (!dat) {
        perror("Pogreška prilikom otvaranja datoteke");
        return;
    }

    int brojUcitanih;
    if (fread(&brojUcitanih, sizeof(int), 1, dat) != 1) {
        perror("Neuspješno čitanje broja zapisa");
        fclose(dat);
        return;
    }

    Student *priv = calloc(brojUcitanih, sizeof(Student));
    if (!priv) {
        perror("Neuspješna alokacija memorije");
        fclose(dat);
        return;
    }

    if (fread(priv, sizeof(Student), brojUcitanih, dat) != (size_t)brojUcitanih) {
        perror("Neuspješno čitanje studenata");
        free(priv);
        fclose(dat);
        return;
    }

    fclose(dat);
    free(*studenti);
    *studenti = priv;
    *broj = brojUcitanih;
    prikaziStudente(*studenti, *broj);
}

void sortirajStudente(Student *studenti, int broj) {
    qsort(studenti, broj, sizeof(Student),
          (int(*)(const void*, const void*))[](const Student *a, const Student *b) {
              return strcmp(a->prezime, b->prezime);
          });
    printf("Studenti sortirani po prezimenu.\n");
}

Student* pretraziStudenta(Student *studenti, int broj, int id) {
    for (int i = 0; i < broj; i++) {
        if (studenti[i].idStudenta == id && studenti[i].aktivan)
            return &studenti[i];
    }
    return NULL;
}

void oslobodiMemoriju(Student **studenti) {
    if (studenti && *studenti) {
        free(*studenti);
        *studenti = NULL;
    }
}
