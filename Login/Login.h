#ifndef LOGIN_H
#define LOGIN_H

#define MAX_USERS 100

struct User {
    char username[20];
    char password[20];
};

struct User registeredUsers[MAX_USERS];
int numUsers = 0;

bool fazerLogin(const char *usuario, const char *senha);

#endif 