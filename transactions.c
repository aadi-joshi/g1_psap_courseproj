#include "transactions.h"

void addTransaction(char *username) {
    Transaction trans;
    FILE *fp;
    
    printf("\nAdd Transaction\n");
    printf("Date (DD/MM/YYYY): ");
    scanf("%s", trans.date);
    printf("Category (Food/Rent/Utilities/Others): ");
    scanf("%s", trans.category);
    printf("Amount: ");
    scanf("%f", &trans.amount);
    printf("Description: ");
    scanf(" %[^\n]s", trans.description);
    strcpy(trans.username, username);
    
    fp = fopen("transactions.csv", "a");
    if (fp != NULL) {
        fprintf(fp, "%s,%s,%s,%.2f,%s\n", 
                trans.username, trans.date, trans.category, 
                trans.amount, trans.description);
        fclose(fp);
        printf("Transaction added successfully!\n");
    }
}

void viewTransactions(char *username) {
    FILE *fp;
    char line[MAX_STRING * 2];
    Transaction trans;
    
    printf("\n%-12s%-15s%-12s%-30s\n", "Date", "Category", "Amount", "Description");
    printf("------------------------------------------------------------\n");
    
    fp = fopen("transactions.csv", "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            sscanf(line, "%[^,],%[^,],%[^,],%f,%[^\n]", 
                   trans.username, trans.date, trans.category, 
                   &trans.amount, trans.description);
            if (strcmp(username, trans.username) == 0) {
                printf("%-12s%-15s%-12.2f%-30s\n", 
                       trans.date, trans.category, trans.amount, trans.description);
            }
        }
        fclose(fp);
    }
}

void generateReport(char *username) {
    FILE *fp;
    char line[MAX_STRING * 2];
    Transaction trans;
    float totalByCategory[4] = {0}; // Food, Rent, Utilities, Others
    
    fp = fopen("transactions.csv", "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            sscanf(line, "%[^,],%[^,],%[^,],%f,%[^\n]", 
                   trans.username, trans.date, trans.category, 
                   &trans.amount, trans.description);
            if (strcmp(username, trans.username) == 0) {
                if (strcmp(trans.category, "Food") == 0) totalByCategory[0] += trans.amount;
                else if (strcmp(trans.category, "Rent") == 0) totalByCategory[1] += trans.amount;
                else if (strcmp(trans.category, "Utilities") == 0) totalByCategory[2] += trans.amount;
                else totalByCategory[3] += trans.amount;
            }
        }
        fclose(fp);
        
        printf("\nExpense Report\n");
        printf("--------------------\n");
        printf("Food:      $%.2f\n", totalByCategory[0]);
        printf("Rent:      $%.2f\n", totalByCategory[1]);
        printf("Utilities: $%.2f\n", totalByCategory[2]);
        printf("Others:    $%.2f\n", totalByCategory[3]);
        printf("--------------------\n");
        printf("Total:     $%.2f\n", 
               totalByCategory[0] + totalByCategory[1] + 
               totalByCategory[2] + totalByCategory[3]);
    }
}