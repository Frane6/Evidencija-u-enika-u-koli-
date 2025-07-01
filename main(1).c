#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

int totalStudents = 0; // [KONCEPT 6] globalna varijabla

// [KONCEPT 11] enum za izbornik
typedef enum {
    MENU_CREATE = 1,
    MENU_READ,
    MENU_UPDATE,
    MENU_DELETE,
    MENU_SAVE,
    MENU_LOAD,
    MENU_SORT,
    MENU_SEARCH,
    MENU_EXIT
} MenuOption;

int main(void) {
    Student *students = NULL; // [KONCEPT 12] pokazivač, početno NULL
    int choice;

    do {
        showMenu(); // [KONCEPT 10] izbornik
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case MENU_CREATE:
                createStudent(&students, &totalStudents); // [KONCEPT 1] C(R)UID - Create
                break;
            case MENU_READ:
                readStudents(students, totalStudents);    // [KONCEPT 1] C(R)UID - Read
                break;
            case MENU_UPDATE:
                updateStudent(students, totalStudents);   // [KONCEPT 1] CR(U)ID - Update
                break;
            case MENU_DELETE:
                deleteStudent(students, totalStudents);   // [KONCEPT 1] CRU(I)D - Delete
                break;
            case MENU_SAVE:
                saveToFile(students, totalStudents);      // [KONCEPT 19] datoteke
                break;
            case MENU_LOAD:
                loadFromFile(&students, &totalStudents);  // [KONCEPT 19, 20, 22]
                break;
            case MENU_SORT:
                sortStudents(students, totalStudents);    // [KONCEPT 23]
                break;
            case MENU_SEARCH: {
                int id;
                printf("Enter ID to search: ");
                if (scanf("%d", &id) != 1) break;
                Student *s = searchStudent(students, totalStudents, id); // [KONCEPT 24]
                if (s && s->isActive) {
                    printf("%d | %s %s | %s | %.2f | Year %d | %s\n",
                        s->studentId, s->firstName, s->lastName, s->city,
                        s->averageGrade, s->currentYear,
                        s->gender == MALE ? "Male" : s->gender == FEMALE ? "Female" : "Other");
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case MENU_EXIT:
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != MENU_EXIT);

    freeMemory(&students); // [KONCEPT 18] dealokacija memorije
    return 0;
}
