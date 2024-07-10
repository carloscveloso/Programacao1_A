#ifndef UTILIZADOR_H
#define UTILIZADOR_H

#include <stdbool.h>

#define MAX_AGENTES 15

// Definição dos tipos de utilizadores
typedef enum {
    ADMINISTRADOR,
    AGENTE,
    CLIENTE
} TipoUtilizador;

// Estrutura para armazenar informação sobre um utilizador
typedef struct {
    char nome[100];
    int NIF;
    char morada[100];
    char contactoTelefonico[15];
    char dataNascimento[20]; // Formato: YYYY-MM-DD
    bool disponivel;
    char username[20]; // Identificador
    char password[20];
    TipoUtilizador tipo;
} Utilizador;

// ADD ADMIN
void adicionarAdministrador();

// REGISTAR
bool efetuarLogin(char *username, char *password);
bool verificarUsername(char *username);
TipoUtilizador* tipoRegisto(char *username);
void ListarConta(char* username);
bool verificarTipo(TipoUtilizador pretendido, char *username);

// CRUD FICHEIRO
void lerFicheiroUtilizadores();
void gravarFicheiroUtilizadores();

// CRUD STRUCTS
void CriarUtilizador(Utilizador novoUtilizador);
void EditarUtilizador(Utilizador utilizadorEditado);
void RemoverUtilizador(char* username);
void ListarUtilizador(TipoUtilizador tipoUtilizador, int tipoNum);
Utilizador* ReturnUtilizador(char* username);
char** AgentesIndisponiveis();

// ORDENAÇÕES
void ordenarPorNome(TipoUtilizador tipoUtilizador, int tipoOrdenar);
void ordenarPorIdade(TipoUtilizador tipoUtilizador, int tipoOrdenar);

#endif 