#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure to represent a student
struct Student {
    char name[50];
    char surname[50];
    char date_of_birth[20];
};

// Function prototypes
void addStudent(struct Student students[], int *num_students);
void displayStudents(struct Student students[], int num_students);
void searchStudent(struct Student students[], int num_students, char *name);

int main() {
    struct Student students[MAX_STUDENTS];
    int num_students = 0;
    int choice;
    char name[50];

    do {
        // Display menu
        printf("\nStudent Enrollment Management System\n");
        printf("1. Add a student\n");
        printf("2. Display enrolled students\n");
        printf("3. Search for a student by name\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent(students, &num_students);
                break;
            case 2:
                displayStudents(students, num_students);
                break;
            case 3:
                printf("Enter the name of the student to search: ");
                scanf("%s", name);
                searchStudent(students, num_students, name);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to add a student
void addStudent(struct Student students[], int *num_students) {
    if (*num_students < MAX_STUDENTS) {
        printf("Enter the name of the student: ");
        scanf("%s", students[*num_students].name);
        printf("Enter the surname of the student: ");
        scanf("%s", students[*num_students].surname);
        printf("Enter the date of birth of the student (DD/MM/YYYY): ");
        scanf("%s", students[*num_students].date_of_birth);
        (*num_students)++;
        printf("Student added successfully.\n");
    } else {
        printf("Cannot add more students. Maximum limit reached.\n");
    }
}

// Function to display enrolled students
void displayStudents(struct Student students[], int num_students) {
    if (num_students == 0) {
        printf("No students enrolled.\n");
    } else {
        printf("Enrolled students:\n");
        for (int i = 0; i < num_students; i++) {
            printf("%d. Name: %s, Surname: %s, Date of Birth: %s\n", 
                   i+1, students[i].name, students[i].surname, students[i].date_of_birth);
        }
    }
}

// Function to search for a student by name
void searchStudent(struct Student students[], int num_students, char *name) {
    int found = 0;
    for (int i = 0; i < num_students; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Student found:\n");
            printf("Name: %s, Surname: %s, Date of Birth: %s\n", 
                   students[i].name, students[i].surname, students[i].date_of_birth);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with name \"%s\" not found.\n", name);
    }
}

