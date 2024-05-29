#include "login.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void registrarUsuario(const char *usuario, const char *senha) {
    if (numUsers < MAX_USERS) {
        strcpy(registeredUsers[numUsers].username, usuario);
        strcpy(registeredUsers[numUsers].password, senha);
        numUsers++;
        printf("Usuário registrado com sucesso:\n");
        printf("Usuário: %s\n", usuario);
        printf("Senha: %s\n", senha);
    } else {
        printf("Limite máximo de usuários atingido. Não é possível registrar mais usuários.\n");
    }
}

bool fazerLogin(const char *usuario, const char *senha) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(usuario, registeredUsers[i].username) == 0 && strcmp(senha, registeredUsers[i].password) == 0) {
            return true;
        }
    }
    return false;
}