#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "main.h"

// Basic operations
void addTransaction(char *username);
void viewTransactions(char *username);
void generateReport(char *username);
void deleteTransaction(char *username);

// Advanced operations
void searchTransactions(char *username);
void displayTransactionMatrix(char *username);
void analyzeTrends(char *username);
void calculateStatistics(char *username);

// Sorting functions
void sortTransactions(Transaction *trans, int n);
void sortTransactionsByDate(Transaction *trans, int n);
float calculateRecursiveTotal(Transaction *trans, int n);

#endif