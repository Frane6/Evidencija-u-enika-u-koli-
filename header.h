#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LEN 50
#define MAX_CITY_LEN 50
#define FILE_NAME "students.dat"

typedef enum {
    MALE = 0,
    FEMALE,
    OTHER
} Gender;

typedef struct {
    int studentId;
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    char city[MAX_CITY_LEN];
    float averageGrade;
    int currentYear;
    Gender gender;
    int isActive;
} Student;

// Global counter
extern int totalStudents;

// Funkcijske deklaracije
void showMenu(void);
void createStudent(Student** students, int* size);
void readStudents(const Student* students, int size);
void updateStudent(Student* students, int size);
void deleteStudent(Student* students, int size);
void saveToFile(const Student* students, int size);
void loadFromFile(Student** students, int* size);
void sortStudents(Student* students, int size);
Student* searchStudent(Student* students, int size, int id);
void freeMemory(Student** students);

#endif
