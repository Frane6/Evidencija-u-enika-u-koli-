#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MaksIme 50
#define MaksGrad 50
#define NazivDatoteke "studenti.dat"

// Tip podataka za spol studenta
typedef enum {
    Musko = 0,
    Zensko,
    Ostalo
} Spol;

// Struktura za studenta
typedef struct {
    int IdStudenta;
    char Ime[MaksIme];
    char Prezime[MaksIme];
    char Grad[MaksGrad];
    float ProsjekOcjena;
    int Godina;
    Spol Spol;
    int Aktivan;  // 1 - aktivan, 0 - obrisan
} Student;

// Globalna varijabla za broj studenata
extern int BrojStudenata;

// Funkcije za izbornik
void PrikaziIzbornik(void);

// Funkcije za CRUD
void UnesiStudenta(Student** Studenti, int* Broj);
void PrikaziStudente(const Student* Studenti, int Broj);
void AzurirajStudenta(Student* Studenti, int Broj);
void ObrisiStudenta(Student* Studenti, int Broj);

// Funkcije za rad s datotekama
void SpremiUDatoteku(const Student* Studenti, int Broj);
void UcitajIzDatoteke(Student** Studenti, int* Broj);
void PreimenujDatoteku(const char* Stara, const char* Nova);
void ObrisiDatoteku(const char* Naziv);
void KopirajDatoteku(const char* Izvor, const char* Odrediste);

// Funkcija za sortiranje
void SortirajStudente(Student* Studenti, int Broj);
void QuickSort(Student* Studenti, int Low, int High);
int Partition(Student* Studenti, int Low, int High);

// Funkcija za pretraživanje
Student* PretraziStudenta(Student* Studenti, int Broj, int Id);

// Funkcija za oslobađanje memorije
void OslobodiMemoriju(Student** Studenti);

#endif
