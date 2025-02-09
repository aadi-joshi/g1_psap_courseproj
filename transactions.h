#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "main.h"

// for basic operations
void addTransaction(char *username);
void viewTransactions(char *username);
void generateReport(char *username);
void deleteTransaction(char *username);

// for advanced operations
void searchTransactions(char *username);
void displayTransactionMatrix(char *username);
void analyzeTrends(char *username);
void calculateStatistics(char *username);

// these functions are used by us for sorting
void sortTransactions(Transaction *trans, int n);
void sortTransactionsByDate(Transaction *trans, int n);
float calculateRecursiveTotal(Transaction *trans, int n);

#endif