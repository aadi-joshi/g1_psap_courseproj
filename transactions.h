#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "main.h"

#define NUM_CATEGORIES 4  // Define as a macro

// Basic operations
void addTransaction(char *username);
void viewTransactions(char *username);
void generateReport(char *username);
void deleteTransaction(char *username);  // New function

// Simple sorting
void sortTransactions(Transaction *trans, int n);  // Basic bubble sort

#endif