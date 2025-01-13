#include "auth.h"

User signIn() {
    User user;
    printf("\nSign In\n");
    
    do {
        printf("Username (max %d chars): ", MAX_STRING-1);
        if (scanf("%99s", user.username) != 1) {
            printf("Invalid username. Please enter again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (strlen(user.username) == 0);
    
    do {
        printf("Password (max %d chars): ", MAX_STRING-1);
        if (scanf("%99s", user.password) != 1) {
            printf("Invalid password. Please enter again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (strlen(user.password) == 0);
    
    return user;
}

void registerUser() {
    User newUser, tempUser;
    FILE *fp;
    
    printf("\nRegister New User\n");
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
    
    do {
        printf("Password (max %d chars): ", MAX_STRING-1);
        if (scanf("%99s", newUser.password) != 1) {
            printf("Invalid password. Please enter again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (strlen(newUser.password) == 0);
    
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