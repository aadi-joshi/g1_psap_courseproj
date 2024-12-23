#ifndef AUTH_H
#define AUTH_H

#include "main.h"

User signIn();
void registerUser();
int authenticateUser(User user);

#endif