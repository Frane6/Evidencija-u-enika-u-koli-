#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

void showMenu(void) {
    printf("\n=== STUDENT MENU ===\n"); // [KONCEPT 10]
    printf("1 - Create student\n");
    printf("2 - Read all students\n");
    printf("3 - Update student\n");
    printf("4 - Delete student\n");
    printf("5 - Save to file\n");
    printf("6 - Load from file\n");
    printf("7 - Sort students\n");
    printf("8 - Search by ID\n");
    printf("9 - Exit\n");
    printf("Choice: ");
}

void createStudent(Student **students, int *size) {
    Student *temp = realloc(*students, (*size + 1) * sizeof(Student)); // [KONCEPT 17]
    if (!temp) {
        perror("Memory allocation failed"); // [KONCEPT 22]
        return;
    }
    *students = temp;

    Student *s = &(*students)[*size];

    printf("Enter Student ID: ");
    if (scanf("%d", &s->studentId) != 1) return;

    printf("Enter First Name: ");
    if (scanf("%s", s->firstName) != 1) return;

    printf("Enter Last Name: ");
    if (scanf("%s", s->lastName) != 1) return;

    printf("Enter City: ");
    if (scanf("%s", s->city) != 1) return;

    printf("Enter Average Grade: ");
    if (scanf("%f", &s->averageGrade) != 1) return;

    printf("Enter Current Year: ");
    if (scanf("%d", &s->currentYear) != 1) return;

    printf("Enter Gender (0-Male, 1-Female, 2-Other): ");
    int g;
    if (scanf("%d", &g) != 1 || g < 0 || g > 2) return;

    s->gender = (Gender)g;
    s->isActive = 1;
    (*size)++;
}

void readStudents(const Student *students, int size) {
    for (int i = 0; i < size; i++) {
        if (students[i].isActive) {
            printf("%d | %s %s | %s | %.2f | Year %d | %s\n",
                   students[i].studentId, students[i].firstName, students[i].lastName,
                   students[i].city, students[i].averageGrade, students[i].currentYear,
                   students[i].gender == MALE ? "Male" : students[i].gender == FEMALE ? "Female" : "Other");
        }
    }
}

void updateStudent(Student *students, int size) {
    int id;
    printf("Enter ID to update: ");
    if (scanf("%d", &id) != 1) return;

    for (int i = 0; i < size; i++) {
        if (students[i].studentId == id && students[i].isActive) {
            printf("Enter New City: ");
            if (scanf("%s", students[i].city) != 1) return;

            printf("Enter New Average Grade: ");
            if (scanf("%f", &students[i].averageGrade) != 1) return;

            printf("Enter New Year: ");
            if (scanf("%d", &students[i].currentYear) != 1) return;
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteStudent(Student *students, int size) {
    int id;
    printf("Enter ID to delete: ");
    if (scanf("%d", &id) != 1) return;

    for (int i = 0; i < size; i++) {
        if (students[i].studentId == id && students[i].isActive) {
            students[i].isActive = 0;
            printf("Student deleted.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void saveToFile(const Student *students, int size) {
    FILE *f = fopen(FILE_NAME, "wb"); // [KONCEPT 19]
    if (!f) {
        perror("File open error");     // [KONCEPT 22]
        return;
    }

    fwrite(&size, sizeof(int), 1, f);
    fwrite(students, sizeof(Student), size, f);
    fclose(f);
    printf("Saved %d students.\n", size);
}

void loadFromFile(Student **students, int *size) {
    FILE *f = fopen(FILE_NAME, "rb"); // [KONCEPT 19]
    if (!f) {
        perror("File open error");    // [KONCEPT 22]
        return;
    }

    int count;
    if (fread(&count, sizeof(int), 1, f) != 1) {
        perror("Failed to read student count");
        fclose(f);
        return;
    }

    Student *temp = calloc(count, sizeof(Student)); // [KONCEPT 17]
    if (!temp) {
        perror("Memory allocation error");
        fclose(f);
        return;
    }

    if (fread(temp, sizeof(Student), count, f) != (size_t)count) {
        perror("Failed to read student data");
        free(temp);
        fclose(f);
        return;
    }

    fclose(f);
    free(*students);
    *students = temp;
    *size = count;
    readStudents(*students, *size); // automatski ispis
}

void sortStudents(Student *students, int size) {
    qsort(students, size, sizeof(Student),
        (int(*)(const void*, const void*))[](const Student *a, const Student *b) {
            return strcmp(a->lastName, b->lastName);
        }); // [KONCEPT 23] qsort + funkcijski pokazivač (26)
    printf("Students sorted by last name.\n");
}

Student* searchStudent(Student *students, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (students[i].studentId == id && students[i].isActive)
            return &students[i];
    }
    return NULL;
}

void freeMemory(Student **students) {
    if (students && *students) {
        free(*students);       // [KONCEPT 17, 18]
        *students = NULL;      // [KONCEPT 18] anuliranje pokazivača
    }
}
