#include "utils.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayMenu() {
    printf("\nPersonal Finance Tracker\n");
    printf("1. Add Transaction\n");
    printf("2. View Transactions\n");
    printf("3. Generate Report\n");
    printf("4. Delete Transaction\n");  // New option
    printf("5. Exit\n");
    printf("Choose an option: ");
}

const char* getValidCategories() {
    return "Food/Rent/Utilities/Others";
}