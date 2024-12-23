#include "main.h"
#include "auth.h"
#include "transactions.h"
#include "utils.h"

int main() {
    int choice;
    User currentUser;
    int isLoggedIn = 0;
    
    while (!isLoggedIn) {
        printf("\nWelcome to Personal Finance Tracker\n");
        printf("1. Sign In\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
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
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addTransaction(currentUser.username);
                break;
            case 2:
                viewTransactions(currentUser.username);
                break;
            case 3:
                generateReport(currentUser.username);
                break;
            case 4:
                printf("\nGoodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice!\n");
        }
    }
    
    return 0;
}