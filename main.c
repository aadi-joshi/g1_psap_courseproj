#include "colors.h"  // Move this first
#include "main.h"
#include "auth.h"
#include "transactions.h"
#include "utils.h"

int main() {
    #ifdef _WIN32
    // Set console to use UTF-8
    system("chcp 65001");
    #endif

    int choice;
    User currentUser;
    int isLoggedIn = 0;
    
    while (!isLoggedIn) {
        printf("\nWelcome to Personal Finance Tracker\n");
        printf("1. Sign In\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                currentUser = signIn();
                if (authenticateUser(currentUser)) {
                    printf("\nLogin successful!\n");
                    isLoggedIn = 1;
                } else {
                    printf("\nInvalid credentials!\n");
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("\nGoodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice!\n");
        }
    }
    
    while (1) {
        displayWelcomeBanner();
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printColored("Invalid input. Please enter a number.\n", RED);
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                addTransaction(currentUser.username);
                break;
            case 2:
                viewTransactions(currentUser.username);
                break;
            case 3:
                generateReport(currentUser.username);
                analyzeTrends(currentUser.username);
                calculateStatistics(currentUser.username);
                break;
            case 4:
                deleteTransaction(currentUser.username);
                break;
            case 5:
                searchTransactions(currentUser.username);
                break;
            case 6:
                displayTransactionMatrix(currentUser.username);
                break;
            case 7:
                printColored("\nThank you for using Personal Finance Tracker!\n", GREEN);
                return 0;
            default:
                printColored("\nInvalid choice!\n", RED);
        }
    }
    
    return 0;
}