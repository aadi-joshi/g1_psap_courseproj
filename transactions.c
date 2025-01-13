#include "transactions.h"
#include <ctype.h>

const char* VALID_CATEGORIES[] = {"Food", "Rent", "Utilities", "Others"};

int isValidDate(const char* dateStr) {
    int day, month, year;
    if (sscanf(dateStr, "%d/%d/%d", &day, &month, &year) != 3)
        return 0;
    
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    if (year < 2000 || year > 2100) return 0;
    
    // Check days in month
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (year % 4 == 0) daysInMonth[1] = 29; // Leap year
    
    return day <= daysInMonth[month-1];
}

int isValidCategory(const char* category) {
    for(int i = 0; i < NUM_CATEGORIES; i++) {
        if(strcmp(category, VALID_CATEGORIES[i]) == 0)
            return 1;
    }
    return 0;
}

int isValidAmount(float amount) {
    return amount > 0 && amount <= 1000000;
}

void addTransaction(char *username) {
    Transaction trans;
    FILE *fp;
    char dateStr[MAX_STRING];
    
    printf("\nAdd Transaction\n");
    do {
        printf("Date (DD/MM/YYYY): ");
        if (scanf("%s", dateStr) != 1 || !isValidDate(dateStr)) {
            printf("Invalid date. Please enter again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (!isValidDate(dateStr));
    strcpy(trans.date, dateStr);
    
    do {
        printf("Category (Food/Rent/Utilities/Others): ");
        if (scanf("%s", trans.category) != 1 || !isValidCategory(trans.category)) {
            printf("Invalid category. Please enter again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (!isValidCategory(trans.category));
    
    do {
        printf("Amount: $");
        if (scanf("%f", &trans.amount) != 1 || !isValidAmount(trans.amount)) {
            printf("Invalid amount. Please enter again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (!isValidAmount(trans.amount));
    
    printf("Description: ");
    scanf("%s", trans.description);
    clearInputBuffer();
    
    strcpy(trans.username, username);
    
    fp = fopen("transactions.dat", "ab");
    if (fp != NULL) {
        fwrite(&trans, sizeof(Transaction), 1, fp);
        fclose(fp);
        printf("Transaction added successfully!\n");
    } else {
        printf("Error: Could not open file for writing.\n");
    }
}

void deleteTransaction(char *username) {
    FILE *fp, *tempFp;
    Transaction trans;
    char dateStr[MAX_STRING], description[MAX_STRING];
    int found = 0;
    
    printf("\nDelete Transaction\n");
    do {
        printf("Date (DD/MM/YYYY): ");
        if (scanf("%s", dateStr) != 1 || !isValidDate(dateStr)) {
            printf("Invalid date. Please enter again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (!isValidDate(dateStr));
    
    printf("Description: ");
    scanf("%s", description);
    clearInputBuffer();
    
    fp = fopen("transactions.dat", "rb");
    tempFp = fopen("temp.dat", "wb");
    
    if (fp != NULL && tempFp != NULL) {
        while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
            if (strcmp(username, trans.username) == 0 && 
                strcmp(trans.date, dateStr) == 0 && 
                strcmp(trans.description, description) == 0) {
                found = 1;
            } else {
                fwrite(&trans, sizeof(Transaction), 1, tempFp);
            }
        }
        fclose(fp);
        fclose(tempFp);
        
        remove("transactions.dat");
        rename("temp.dat", "transactions.dat");
        
        if (found) {
            printf("Transaction deleted successfully!\n");
        } else {
            printf("Transaction not found.\n");
        }
    } else {
        printf("Error: Could not open file.\n");
    }
}

void sortTransactions(Transaction *trans, int n) {
    int i, j;
    Transaction temp;
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(trans[j].amount > trans[j+1].amount) {
                temp = trans[j];
                trans[j] = trans[j+1];
                trans[j+1] = temp;
            }
        }
    }
}

void sortTransactionsByDate(Transaction *trans, int n) {
    int i, j, min_idx;
    Transaction temp;
    
    for(i = 0; i < n-1; i++) {
        min_idx = i;
        for(j = i+1; j < n; j++) {
            if(strcmp(trans[j].date, trans[min_idx].date) < 0)
                min_idx = j;
        }
        if(min_idx != i) {
            temp = trans[min_idx];
            trans[min_idx] = trans[i];
            trans[i] = temp;
        }
    }
}

void displayTransactionMatrix(char *username) {
    float matrix[12][31] = {0};
    FILE *fp;
    Transaction trans;
    int day, month, year;
    
    fp = fopen("transactions.dat", "rb");
    if(fp != NULL) {
        while(fread(&trans, sizeof(Transaction), 1, fp)) {
            if(strcmp(username, trans.username) == 0) {
                sscanf(trans.date, "%d/%d/%d", &day, &month, &year);
                matrix[month-1][day-1] += trans.amount;
            }
        }
        fclose(fp);
        
        printf("\nMonthly Transaction Matrix (Day vs Month):\n");
        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 31; j++) {
                if(matrix[i][j] != 0)
                    printf("Month %2d, Day %2d: $%.2f\n", i+1, j+1, matrix[i][j]);
            }
        }
    }
}

float calculateRecursiveTotal(Transaction *trans, int n) {
    if(n == 0) return 0;
    return trans[n-1].amount + calculateRecursiveTotal(trans, n-1);
}

void viewTransactions(char *username) {
    FILE *fp;
    Transaction trans;
    Transaction allTrans[MAX_TRANSACTIONS];
    int count = 0;
    
    printf("\n%-12s%-15s%-12s%-20s\n", "Date", "Category", "Amount", "Description");
    printf("---------------------------------------------------\n");
    
    fp = fopen("transactions.dat", "rb");
    if (fp != NULL) {
        while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
            if (strcmp(username, trans.username) == 0) {
                allTrans[count++] = trans;
            }
        }
        fclose(fp);
        
        sortTransactions(allTrans, count);
        
        for(int i = 0; i < count; i++) {
            printf("%-12s%-15s$%-11.2f%-20s\n", 
                   allTrans[i].date, 
                   allTrans[i].category, 
                   allTrans[i].amount, 
                   allTrans[i].description);
        }
    }
}

void generateReport(char *username) {
    FILE *fp;
    Transaction trans;
    float total = 0;
    float totalByCategory[NUM_CATEGORIES] = {0};
    int count = 0;
    float highest = 0;
    float lowest = 1000000;
    
    fp = fopen("transactions.dat", "rb");
    if (fp != NULL) {
        printf("\nExpense Report\n");
        printf("--------------------\n");
        
        while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
            if (strcmp(username, trans.username) == 0) {
                total += trans.amount;
                count++;
                
                // Update highest and lowest expenses
                if (trans.amount > highest) highest = trans.amount;
                if (trans.amount < lowest) lowest = trans.amount;
                
                // Update total by category
                for (int i = 0; i < NUM_CATEGORIES; i++) {
                    if (strcmp(trans.category, VALID_CATEGORIES[i]) == 0) {
                        totalByCategory[i] += trans.amount;
                        break;
                    }
                }
            }
        }
        fclose(fp);
        
        // Calculate average expense
        float average = (count > 0) ? total / count : 0;
        
        // Print the report
        printf("Total Expenses: $%.2f\n", total);
        printf("Average Expense per Transaction: $%.2f\n", average);
        printf("Highest Expense: $%.2f\n", highest);
        printf("Lowest Expense: $%.2f\n", lowest);
        printf("\nExpenses by Category:\n");
        for (int i = 0; i < NUM_CATEGORIES; i++) {
            printf("%s: $%.2f\n", VALID_CATEGORIES[i], totalByCategory[i]);
        }
    } else {
        printf("Error: Could not open file for reading.\n");
    }
}