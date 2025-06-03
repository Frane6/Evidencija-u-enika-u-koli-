#pragma once

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 32      // 9. Makro konstanta
#define MAX_PREZIME 32  // 9. Makro konstanta
#define MAX_GRAD 32     // 9. Makro konstanta

// 4. typedef, enum za spol ucenika
typedef enum {
    MUSKO,
    ZENSKO,
    NEODREDJENO
} Spol;

// 3. Slozeni tipovi, 4. typedef, 16. Dinamicka memorija (povezani popis)
typedef struct ucenik {
    int id;                      // 2. int
    char ime[MAX_IME];           // 2. char[], 15. Staticki zauzeto polje
    char prezime[MAX_PREZIME];   // 2. char[], 15. Staticki zauzeto polje
    char grad[MAX_GRAD];         // 2. char[], 15. Staticki zauzeto polje
    float prosjek;               // 2. float
    int razred;                  // 2. int
    Spol spol;                   // 4. enum
    int aktivan;                 // 2. int (1=aktivan, 0=neaktivan)
    struct ucenik* next;         // 12. Pokazivac, 16. Dinamicka memorija
} Ucenik;                        // 3. Slozeni tip, 4. typedef

// 8. extern globalna varijabla
extern int ukupnoUcenika;

void dodajUcenika(Ucenik** glava);
void ispisiUcenike(const Ucenik* glava);
void azurirajUcenika(Ucenik* glava);
void deaktivirajUcenika(Ucenik* glava); // umjesto brisanja
void spremiUcenike(const Ucenik* glava, const char* filename);
void ucitajUcenike(Ucenik** glava, const char* filename);
void oslobodiMemoriju(Ucenik** glava);
const char* spolToString(Spol spol);
void sortirajPrezimeQsort(const Ucenik* glava); // 23, 25, 26
