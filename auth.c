#include "auth.h"

User signIn() {
    User user;
    printf("\nSign In\n");
    printf("Username: ");
    scanf("%s", user.username);
    printf("Password: ");
    scanf("%s", user.password);
    return user;
}

void registerUser() {
    User newUser;
    FILE *fp;
    
    printf("\nRegister New User\n");
    printf("Username: ");
    scanf("%s", newUser.username);
    printf("Password: ");
    scanf("%s", newUser.password);
    
    fp = fopen("users.csv", "a");
    if (fp != NULL) {
        fprintf(fp, "%s,%s\n", newUser.username, newUser.password);
        fclose(fp);
        printf("Registration successful!\n");
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