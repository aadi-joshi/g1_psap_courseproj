#include "auth.h"
#include <stdio.h>
#include <conio.h> // For getch()

void getPassword(char *password); // Function prototype

User signIn() {
    User user;
    printf("\nSign In\n(press 'Tab' to toggle visibility)\n");
    
    do {
        printf("Username (max %d chars): ", MAX_STRING-1);
        if (scanf("%99s", user.username) != 1) {
            printf("Invalid username. Please enter again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (strlen(user.username) == 0);
    
    printf("Password (max %d chars): ", MAX_STRING-1);
    getPassword(user.password);
    
    return user;
}

void getPassword(char *password) {
    int index = 0;
    char ch;
    int showPassword = 0;

    // printf("Enter password (press 'Tab' to toggle visibility): ");
    while (1) {
        ch = getch();
        if (ch == 13) { // Enter key
            password[index] = '\0';
            printf("\n");
            break;
        } else if (ch == 8) { // backspace key is pressed 
            if (index > 0) {
                index--;
                printf("\b \b");
            }
        } else if (ch == 9) { // tab key is pressed
            showPassword = !showPassword;
            printf("\rPassword (max %d chars): ", MAX_STRING-1);
            for (int i = 0; i < index; i++) {
                if (showPassword) {
                    printf("%c", password[i]);
                } else {
                    printf("*");
                }
            }
        } else {
            password[index++] = ch;
            if (showPassword) {
                printf("%c", ch);
            } else {
                printf("*");
            }
        }
    }
}

void registerUser() {
    User newUser, tempUser;
    FILE *fp;
    
    printf("\nRegister New User\n(press 'Tab' to toggle password visibility)\n");
    do {
        printf("Username (max %d chars): ", MAX_STRING-1);
        if (scanf("%99s", newUser.username) != 1) {
            printf("Invalid username. Please enter again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (strlen(newUser.username) == 0);
    
    strcpy(tempUser.username, newUser.username);
    strcpy(tempUser.password, "");  // Empty password for checking username only
    if (authenticateUser(tempUser)) {
        printf("Username already exists.\n");
        return;
    }
    
    printf("Password (max %d chars): ", MAX_STRING-1);
    getPassword(newUser.password);
    
    fp = fopen("users.csv", "a");
    if (fp != NULL) {
        fprintf(fp, "%s,%s\n", newUser.username, newUser.password);
        fclose(fp);
        printf("Registration successful!\n");
    } else {
        printf("Error: Could not open file for writing.\n");
    }
}

int authenticateUser(User user) {
    FILE *fp;
    char line[MAX_STRING];
    char storedUsername[MAX_STRING];
    char storedPassword[MAX_STRING];
    
    fp = fopen("users.csv", "r");
    if (fp == NULL) return 0;
    
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^,],%s", storedUsername, storedPassword);
        if (strcmp(user.username, storedUsername) == 0 && 
            strcmp(user.password, storedPassword) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}