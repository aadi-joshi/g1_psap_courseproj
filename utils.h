#ifndef UTILS_H
#define UTILS_H

#include "colors.h"
#include "main.h"

// Function declarations
void clearScreen();
void displayMenu();
void clearInputBuffer();
void displayWelcomeBanner();
void printColored(const char* text, const char* color);
const char* getValidCategories();

#endif