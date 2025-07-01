#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> // [KONCEPT 22] errno, perror()

#define MAX_NAME_LEN 50
#define MAX_CITY_LEN 50
#define FILE_NAME "students.dat" // [KONCEPT 19] rad s datotekama

// [KONCEPT 4] typedef s enum tipom
typedef enum {
    MALE = 0,
    FEMALE,
    OTHER
} Gender;

// [KONCEPT 3] Složeni tip podatka – struktura
// [KONCEPT 4] typedef s struct
typedef struct {
    int studentId;                        // [KONCEPT 2] konkretan cjelobrojni tip
    char firstName[MAX_NAME_LEN];        // [KONCEPT 15] statički zauzeta polja
    char lastName[MAX_NAME_LEN];
    char city[MAX_CITY_LEN];
    float averageGrade;                  // [KONCEPT 2] konkretan realni tip
    int currentYear;
    Gender gender;                       // [KONCEPT 4] enum
    int isActive;
} Student;

// [KONCEPT 8] extern globalna varijabla
extern int totalStudents;

// [KONCEPT 5] Imenovanje (camelCase)
void showMenu(void);
void createStudent(Student **students, int *size);
void readStudents(const Student *students, int size);
void updateStudent(Student *students, int size);
void deleteStudent(Student *students, int size);
void saveToFile(const Student *students, int size);
void loadFromFile(Student **students, int *size);
void sortStudents(Student *students, int size);
Student* searchStudent(Student *students, int size, int id);
void freeMemory(Student **students);

#endif
