#include "utils.h"

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
    printf("4. Exit\n");
    printf("Choose an option: ");
}