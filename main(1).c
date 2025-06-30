#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

int totalStudents = 0;

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
    Student* students = NULL;
    int choice;

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case MENU_CREATE:
            createStudent(&students, &totalStudents);
            break;
        case MENU_READ:
            readStudents(students, totalStudents);
            break;
        case MENU_UPDATE:
            updateStudent(students, totalStudents);
            break;
        case MENU_DELETE:
            deleteStudent(students, totalStudents);
            break;
        case MENU_SAVE:
            saveToFile(students, totalStudents);
            break;
        case MENU_LOAD:
            loadFromFile(&students, &totalStudents);
            break;
        case MENU_SORT:
            sortStudents(students, totalStudents);
            break;
        case MENU_SEARCH: {
            int id;
            printf("Enter ID to search: ");
            if (scanf("%d", &id) != 1) break;
            Student* s = searchStudent(students, totalStudents, id);
            if (s && s->isActive) {
                printf("%d | %s %s | %s | %.2f | Year %d | %s\n",
                    s->studentId, s->firstName, s->lastName, s->city,
                    s->averageGrade, s->currentYear,
                    s->gender == MALE ? "Male" : s->gender == FEMALE ? "Female" : "Other");
            }
            else {
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

    freeMemory(&students);
    return 0;
}
