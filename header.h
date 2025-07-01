#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAKS_IME 50
#define MAKS_GRAD 50
#define NAZIV_DATOTEKE "studenti.dat"

typedef enum {
    MUSKO = 0,
    ZENSKO,
    OSTALO
} Spol;

typedef struct {
    int idStudenta;
    char ime[MAKS_IME];
    char prezime[MAKS_IME];
    char grad[MAKS_GRAD];
    float prosjekOcjena;
    int godina;
    Spol spol;
    int aktivan;
} Student;

extern int brojStudenata;

void prikaziIzbornik(void);
void unesiStudenta(Student **studenti, int *broj);
void prikaziStudente(const Student *studenti, int broj);
void azurirajStudenta(Student *studenti, int broj);
void obrisiStudenta(Student *studenti, int broj);
void spremiUDatoteku(const Student *studenti, int broj);
void ucitajIzDatoteke(Student **studenti, int *broj);
void sortirajStudente(Student *studenti, int broj);
Student* pretraziStudenta(Student *studenti, int broj, int id);
void oslobodiMemoriju(Student **studenti);

#endif
