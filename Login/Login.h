#ifndef LOGIN_H
#define LOGIN_H
#include <stdbool.h>

#define MAX_USERS 100

int numUsers = 0;

bool fazerLogin(const char *usuario, const char *senha);
void registrarUsuario(const char *usuario, const char *senha)

#endif 