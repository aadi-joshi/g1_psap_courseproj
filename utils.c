#include "utils.h"
#include "colors.h"

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

void printColored(const char* text, const char* color) {
    printf("%s%s%s", color, text, RESET);
}

void displayWelcomeBanner() {
    printf("\n%s", CYAN);
    printf("┌────────────────────────────────┐\n");
    printf("│     Personal Finance Tracker   │\n");
    printf("└────────────────────────────────┘\n");
    printf("%s", RESET);
}

void displayMenu() {
    printf("\n%sPersonal Finance Tracker%s\n", YELLOW, RESET);
    printf("%s1.%s Add Transaction\n", GREEN, RESET);
    printf("%s2.%s View Transactions\n", GREEN, RESET);
    printf("%s3.%s Generate Report\n", GREEN, RESET);
    printf("%s4.%s Delete Transaction\n", GREEN, RESET);
    printf("%s5.%s Search Transactions\n", GREEN, RESET);
    printf("%s6.%s View Transaction Matrix\n", GREEN, RESET);
    printf("%s7.%s Exit\n", RED, RESET);
    printf("%sChoose an option:%s ", CYAN, RESET);
}

const char* getValidCategories() {
    return "Food/Rent/Utilities/Others";
}