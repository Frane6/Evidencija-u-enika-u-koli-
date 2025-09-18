#ifndef Header_H
#define Header_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaksIme 50
#define MaksGrad 50
#define NazivDatoteke "studenti.dat"
// 11
typedef enum { Musko = 0, Zensko, Ostalo } Spol;    //4 

typedef struct {
    int IdStudenta;            //3
    char Ime[MaksIme];
    char Prezime[MaksIme];      // Statički zauzeto polje
    char Grad[MaksGrad];
    float ProsjekOcjena;
    int Godina;
    Spol Spol;
    int Aktivan;
} Student;

extern int BrojStudenata;     //8

// CRUD
void PrikaziIzbornik(void);
void UnesiStudenta(Student** Studenti, int* Broj);
void PrikaziStudente(const Student* Studenti, int Broj);
void AzurirajStudenta(Student* Studenti, int Broj);
void ObrisiStudenta(Student* Studenti, int Broj);

// Datoteka
void SpremiUDatoteku(const Student* Studenti, int Broj);
void UcitajIzDatoteke(Student** Studenti, int* Broj);
  
void PreimenujDatoteku(const char* Stara, const char* Nova);

// Sortiranje / Pretraga
void SortirajStudente(Student* Studenti, int Broj);
Student* PretraziStudenta(Student* Studenti, int Broj, int Id);

// Memorija
void OslobodiMemoriju(Student** Studenti);

// QuickSort
void QuickSort(Student* Studenti, int Low, int High);
int Partition(Student* Studenti, int Low, int High);
void Swap(Student* a, Student* b);

#endif
