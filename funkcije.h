#define _CRT_SECURE_NO_﻿WARNINGS
#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#include <stdio.h>

#define MAX_NAME_LEN 50
#define DATA_FILE "studenti.txt"

typedef struct {                     //4
	int id;
	char ime[MAX_NAME_LEN];
	char prezime[MAX_NAME_LEN];
	float prosjek;
} Student;

// Enum za izbornik                  
typedef enum {           //11, 10                  
	IZLAZ,
	DODAJ_UCENIKA,
	PRIKAZI_UCENIKE,
	AZURIRAJ_UCENIKA,
	OBRISI_UCENIKA,
	PRETRAZI_UCENIKA
} IzbornikOpcije;

// Deklaracije funkcija
void dodajUcenika();
void prikaziUcenike();
void azurirajUcenika();
void obrisiUcenika();
void pretraziUcenika();
int ucitajStudente(Student** ucenici);
int spremiStudente(Student* ucenici, int brojStudenata);

#endif