#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

// Static varijable za praćenje poziva funkcija
static int BrojPoziva = 0;
static int BrojPrikaza = 0;

// Inline funkcije
inline void Swap(Student* a, Student* b) {
    if (!a || !b) return;
    Student Temp = *a;
    *a = *b;
    *b = Temp;
}
// Izbornik
void PrikaziIzbornik(void) {
    printf("\n=== IZBORNIK STUDENATA ===\n");
    printf("1 - Unesi novog studenta\n");
    printf("2 - Prikazi sve studente\n");
    printf("3 - Azuriraj podatke studenta\n");
    printf("4 - Obrisi studenta\n");
    printf("5 - Spremi u datoteku\n");
    printf("6 - Ucitaj iz datoteke\n");
    printf("7 - Sortiraj studente\n");
    printf("8 - Pretrazi po ID-u\n");
    printf("9 - Izlaz\n");
    printf("Odabir: ");
}

// CRUD
void UnesiStudenta(Student** Studenti, int* Broj) {
    if (!Studenti || !Broj) return;
    BrojPoziva++;
    Student* Privremeno = realloc(*Studenti, (*Broj + 1) * sizeof(Student));   //12 //16 //17
    if (!Privremeno) { perror("Greška pri alokaciji"); return; }
    *Studenti = Privremeno;

    Student* NoviStudent = &(*Studenti)[*Broj];

    printf("Unesite ID studenta: "); if (scanf("%d", &NoviStudent->IdStudenta) != 1) return;
    printf("Unesite ime: "); if (scanf("%s", NoviStudent->Ime) != 1) return;
    printf("Unesite prezime: "); if (scanf("%s", NoviStudent->Prezime) != 1) return;
    printf("Unesite grad: "); if (scanf("%s", NoviStudent->Grad) != 1) return;
    printf("Unesite prosjek ocjena: "); if (scanf("%f", &NoviStudent->ProsjekOcjena) != 1) return;
    printf("Unesite godinu studija: "); if (scanf("%d", &NoviStudent->Godina) != 1) return;

    int SpolInt;
    printf("Unesite spol (0 - Musko, 1 - Zensko, 2 - Ostalo): ");
    if (scanf("%d", &SpolInt) != 1 || SpolInt < 0 || SpolInt > 2) return;
    NoviStudent->Spol = (Spol)SpolInt;
    NoviStudent->Aktivan = 1;
    (*Broj)++;
}

void PrikaziStudente(const Student* Studenti, int Broj) {
    if (!Studenti || Broj <= 0) return;
    BrojPrikaza++;
    for (int i = 0; i < Broj; i++) {
        if (Studenti[i].Aktivan) {
            printf("%d | %s %s | %s | %.2f | Godina %d | %s\n",
                Studenti[i].IdStudenta, Studenti[i].Ime, Studenti[i].Prezime,
                Studenti[i].Grad, Studenti[i].ProsjekOcjena, Studenti[i].Godina,
                Studenti[i].Spol == Musko ? "Muško" : Studenti[i].Spol == Zensko ? "Žensko" : "Ostalo");
        }
    }
}

void AzurirajStudenta(Student* Studenti, int Broj) {
    if (!Studenti || Broj <= 0) return;
    int Id;
    printf("Unesite ID studenta za azuriranje: ");
    if (scanf("%d", &Id) != 1) return;
    for (int i = 0; i < Broj; i++) {
        if (Studenti[i].IdStudenta == Id && Studenti[i].Aktivan) {
            printf("Unesite novi grad: "); if (scanf("%s", Studenti[i].Grad) != 1) return;
            printf("Unesite novi prosjek: "); if (scanf("%f", &Studenti[i].ProsjekOcjena) != 1) return;
            printf("Unesite novu godinu: "); if (scanf("%d", &Studenti[i].Godina) != 1) return;
            return;
        }
    }
    printf("Student nije pronaden.\n");
}

void ObrisiStudenta(Student* Studenti, int Broj) {
    if (!Studenti || Broj <= 0) return;
    int Id;
    printf("Unesite ID studenta za brisanje: "); if (scanf("%d", &Id) != 1) return;
    for (int i = 0; i < Broj; i++) {
        if (Studenti[i].IdStudenta == Id && Studenti[i].Aktivan) {
            Studenti[i].Aktivan = 0;
            printf("Student obrisan.\n");
            return;
        }
    }
    printf("Student nije pronaden.\n");
}

// Datoteka
void SpremiUDatoteku(const Student* Studenti, int Broj) {
    if (!Studenti || Broj <= 0) return;

    FILE* Dat = fopen(NazivDatoteke, "rb+");
    if (!Dat) Dat = fopen(NazivDatoteke, "wb");
    if (!Dat) { perror("Pogreška prilikom otvaranja datoteke"); return; }

    // 20
    rewind(Dat);
    fwrite(&Broj, sizeof(int), 1, Dat);
    fseek(Dat, sizeof(int), SEEK_SET);
    fwrite(Studenti, sizeof(Student), Broj, Dat);

    fclose(Dat);
    printf("Podaci spremljeni u datoteku.\n");
}
// 21 // 22
void PreimenujDatoteku(const char* Stara, const char* Nova) {
    if (!Stara || !Nova) return;

    if (rename(Stara, Nova) == 0) 
        printf("Datoteka %s je preimenovana u %s.\n", Stara, Nova);
    else
        perror("Greška prilikom preimenovanja datoteke");
}

void UcitajIzDatoteke(Student** Studenti, int* Broj) {
    if (!Studenti || !Broj) return;

    FILE* Dat = fopen(NazivDatoteke, "rb");
    if (!Dat) { perror("Pogreška prilikom otvaranja datoteke"); return; }

    int BrojUcitanih = 0;
    if (fread(&BrojUcitanih, sizeof(int), 1, Dat) != 1) {
        perror("Neuspješno čitanje broja studenata");
        fclose(Dat);
        return;
    }

    Student* Priv = calloc(BrojUcitanih, sizeof(Student));
    if (!Priv) { perror("Neuspješna alokacija memorije"); fclose(Dat); return; }

    fseek(Dat, sizeof(int), SEEK_SET);
    if (fread(Priv, sizeof(Student), BrojUcitanih, Dat) != (size_t)BrojUcitanih) {
        perror("Neuspješno čitanje studenata");
        free(Priv);
        fclose(Dat);
        return;
    }

    fclose(Dat);
    free(*Studenti);
    *Studenti = Priv;
    *Broj = BrojUcitanih;

    PrikaziStudente(*Studenti, *Broj);
}

// Pretraga
Student* PretraziStudenta(Student* Studenti, int Broj, int Id) {
    if (!Studenti || Broj <= 0) return NULL;
    for (int i = 0; i < Broj; i++) {
        if (Studenti[i].IdStudenta == Id && Studenti[i].Aktivan)
            return &Studenti[i];
    }
    return NULL;
}

// Memorija
void OslobodiMemoriju(Student** Studenti) {    //18
    if (Studenti && *Studenti) {
        free(*Studenti);
        *Studenti = NULL;
    }
}

// QuickSort
int Partition(Student* Studenti, int Low, int High) {
    if (!Studenti || Low > High) return Low;
    char* Pivot = Studenti[High].Prezime;
    int i = Low - 1;
    for (int j = Low; j < High; j++) {
        if (strcmp(Studenti[j].Prezime, Pivot) <= 0) {
            i++;
            Swap(&Studenti[i], &Studenti[j]);
        }
    }
    Swap(&Studenti[i + 1], &Studenti[High]);
    return i + 1;
}

void QuickSort(Student* Studenti, int Low, int High) {
    if (!Studenti || Low >= High) return;
    int Pi = Partition(Studenti, Low, High);
    QuickSort(Studenti, Low, Pi - 1);
    QuickSort(Studenti, Pi + 1, High);
}

// 23 24
void SortirajStudente(Student* Studenti, int Broj) {
    if (Broj > 0) {
        QuickSort(Studenti, 0, Broj - 1);
        printf("Studenti sortirani po prezimenu.\n");
        PrikaziStudente(Studenti, Broj);
    }
    else {
        printf("Nema studenata za sortiranje.\n");
    }
}
