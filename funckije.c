#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

int ukupnoUcenika = 0; // 8. Definicija globalne varijable

const char* spolToString(Spol spol) { // 4. enum, 9. jednostavna funkcija
    switch (spol) {
    case MUSKO: return "Musko";
    case ZENSKO: return "Zensko";
    case NEODREDJENO: return "Neodredjeno";
    default: return "Nepoznato";
    }
}

// 1. Create
void dodajUcenika(Ucenik** glava) {
    Ucenik* novi = (Ucenik*)malloc(sizeof(Ucenik)); // 16. malloc()
    if (!novi) {                                    // 14. Zastita parametara
        perror("Greska pri alokaciji memorije");    // 22. perror()
        return;
    }
    printf("Unesi ID ucenika: ");
    scanf("%d", &novi->id);
    printf("Unesi ime: ");
    scanf("%31s", novi->ime);
    printf("Unesi prezime: ");
    scanf("%31s", novi->prezime);
    printf("Unesi grad: ");
    scanf("%31s", novi->grad);
    printf("Unesi prosjek ocjena: ");
    scanf("%f", &novi->prosjek);
    printf("Unesi razred (1-8): ");
    scanf("%d", &novi->razred);
    printf("Spol (0-Musko, 1-Zensko, 2-Neodredjeno): ");
    int s; scanf("%d", &s);
    novi->spol = (Spol)s;
    novi->aktivan = 1;
    novi->next = *glava;
    *glava = novi;
    ukupnoUcenika++; // 8. Globalni brojac
    printf("Ucenik dodan.\n");
}

// 1. Read
void ispisiUcenike(const Ucenik* glava) {
    static int pozivi = 0; // 6. static lokalna varijabla
    pozivi++;
    printf("Poziv funkcije: %d\n", pozivi);
    printf("Ukupno ucenika: %d\n", ukupnoUcenika); // 8. globalna varijabla

    const Ucenik* u = glava;
    while (u) {
        if (u->aktivan)
            printf("ID: %d | %s %s | Grad: %s | Prosjek: %.2f | Razred: %d | Spol: %s\n",
                u->id, u->ime, u->prezime, u->grad, u->prosjek, u->razred, spolToString(u->spol));
        u = u->next;
    }
}

// 1. Update
void azurirajUcenika(Ucenik* glava) {
    int id;
    printf("Unesi ID ucenika za izmjenu: ");
    scanf("%d", &id);
    for (Ucenik* u = glava; u; u = u->next) {
        if (u->id == id && u->aktivan) {
            printf("Novo ime: "); scanf("%31s", u->ime);
            printf("Novo prezime: "); scanf("%31s", u->prezime);
            printf("Novi grad: "); scanf("%31s", u->grad);
            printf("Novi prosjek: "); scanf("%f", &u->prosjek);
            printf("Novi razred: "); scanf("%d", &u->razred);
            printf("Novi spol (0-Musko, 1-Zensko, 2-Neodredjeno): ");
            int s; scanf("%d", &s);
            u->spol = (Spol)s;
            printf("Ucenik azuriran.\n");
            return;
        }
    }
    printf("Ucenik nije pronaden.\n");
}

// 1. Delete (soft delete - deaktivacija)
void deaktivirajUcenika(Ucenik* glava) {
    int id;
    printf("Unesi ID ucenika za deaktivaciju: ");
    scanf("%d", &id);
    for (Ucenik* u = glava; u; u = u->next) {
        if (u->id == id && u->aktivan) {
            u->aktivan = 0;
            ukupnoUcenika--;
            printf("Ucenik deaktiviran.\n");
            return;
        }
    }
    printf("Ucenik nije pronaden ili vec nije aktivan.\n");
}

// 19. Datoteke, 20. fseek/ftell/rewind, 22. perror
void spremiUcenike(const Ucenik* glava, const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) { perror("Greska pri otvaranju datoteke"); return; }
    int broj = 0;
    for (const Ucenik* u = glava; u; u = u->next) broj++;
    fwrite(&broj, sizeof(int), 1, fp);
    for (const Ucenik* u = glava; u; u = u->next)
        fwrite(u, sizeof(Ucenik) - sizeof(Ucenik*), 1, fp);
    fclose(fp);
    printf("Podaci spremljeni.\n");
}

void ucitajUcenike(Ucenik** glava, const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) { perror("Greska pri otvaranju datoteke"); return; }
    fseek(fp, 0, SEEK_END); long vel = ftell(fp); rewind(fp); // 20.
    printf("Velicina datoteke: %ld bajtova\n", vel);
    oslobodiMemoriju(glava);
    int broj = 0;
    fread(&broj, sizeof(int), 1, fp);
    ukupnoUcenika = broj; // 8.
    for (int i = 0; i < broj; ++i) {
        Ucenik* novi = (Ucenik*)malloc(sizeof(Ucenik));
        if (!novi) { perror("Greska pri alokaciji memorije"); fclose(fp); return; }
        fread(novi, sizeof(Ucenik) - sizeof(Ucenik*), 1, fp);
        novi->next = *glava;
        *glava = novi;
    }
    fclose(fp);
    printf("Podaci ucitani.\n");
}

// 18. Sigurno brisanje memorije
void oslobodiMemoriju(Ucenik** glava) {
    while (*glava) {
        Ucenik* tmp = *glava;
        *glava = (*glava)->next;
        free(tmp);
    }
}

// 23, 25, 26. Demonstracija qsort (rekurzija + pokazivac na funkciju)
int usporediPrezime(const void* a, const void* b) {
    const Ucenik* ua = (const Ucenik*)a;
    const Ucenik* ub = (const Ucenik*)b;
    return strcmp(ua->prezime, ub->prezime);
}
void sortirajPrezimeQsort(const Ucenik* glava) {
    Ucenik polje[1000];
    int n = 0;
    const Ucenik* u = glava;
    while (u && n < 1000) {
        polje[n++] = *u;
        u = u->next;
    }
    qsort(polje, n, sizeof(Ucenik), usporediPrezime); // 25, 26
    printf("Sortirani ucenici po prezimenu:\n");
    for (int i = 0; i < n; ++i)
        if (polje[i].aktivan)
            printf("%s %s | Grad: %s | Prosjek: %.2f\n", polje[i].ime, polje[i].prezime, polje[i].grad, polje[i].prosjek);
}
