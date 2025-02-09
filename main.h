#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "colors.h"

#define MAX_STRING 100
#define MAX_TRANSACTIONS 1000
#define NUM_CATEGORIES 4

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

void clearScreen();
void displayMenu();
void clearInputBuffer();
const char* getValidCategories();

#endif
