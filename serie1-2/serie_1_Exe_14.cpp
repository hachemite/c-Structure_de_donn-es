#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

// Structure to represent a book
struct Book {
    char title[100];
    char author[100];
    int publication_year;
};

// Function prototypes
void addBook(struct Book library[], int *num_books);
void displayBooks(struct Book library[], int num_books);
void searchBook(struct Book library[], int num_books, char *title);

int main() {
    struct Book library[MAX_BOOKS];
    int num_books = 0;
    int choice;
    char title[100];

    do {
        // Display menu
        printf("\nLibrary Management System\n");
        printf("1. Add a book\n");
        printf("2. Display available books\n");
        printf("3. Search for a book by title\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addBook(library, &num_books);
                break;
            case 2:
                displayBooks(library, num_books);
                break;
            case 3:
                printf("Enter the title of the book to search: ");
                scanf("%s", title);
                searchBook(library, num_books, title);
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

// Function to add a book to the library
void addBook(struct Book library[], int *num_books) {
    if (*num_books < MAX_BOOKS) {
        printf("Enter the title of the book: ");
        scanf("%s", library[*num_books].title);
        printf("Enter the author of the book: ");
        scanf("%s", library[*num_books].author);
        printf("Enter the publication year of the book: ");
        scanf("%d", &library[*num_books].publication_year);
        (*num_books)++;
        printf("Book added successfully.\n");
    } else {
        printf("Cannot add more books. Library is full.\n");
    }
}

// Function to display available books in the library
void displayBooks(struct Book library[], int num_books) {
    if (num_books == 0) {
        printf("No books available in the library.\n");
    } else {
        printf("Available books in the library:\n");
        for (int i = 0; i < num_books; i++) {
            printf("%d. Title: %s, Author: %s, Publication Year: %d\n", 
                   i+1, library[i].title, library[i].author, library[i].publication_year);
        }
    }
}

// Function to search for a book by title
void searchBook(struct Book library[], int num_books, char *title) {
    int found = 0;
    for (int i = 0; i < num_books; i++) {
        if (strcmp(library[i].title, title) == 0) {
            printf("Book found:\n");
            printf("Title: %s, Author: %s, Publication Year: %d\n", 
                   library[i].title, library[i].author, library[i].publication_year);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book with title \"%s\" not found.\n", title);
    }
}

