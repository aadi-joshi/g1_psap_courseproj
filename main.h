#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 100
#define MAX_TRANSACTIONS 1000

typedef struct {
    char username[MAX_STRING];
    char password[MAX_STRING];
} User;

typedef struct {
    char date[MAX_STRING];
    char category[MAX_STRING];
    float amount;
    char description[MAX_STRING];
    char username[MAX_STRING];
} Transaction;

// Function declarations
void clearScreen();
void displayMenu();

#endif
