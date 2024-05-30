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
/*
// Estrutura para armazenar informação sobre uma propriedade
struct Propriedade {
    char tipo[50]; 
    char endereco[100]; 
    double preco; 
} Propriedade;
*/
// Estrutura para armazenar informação sobre um utilizador
typedef struct {
    char nome[100];
    int NIF;
    char morada[100];
    char contactoTelefonico[15];
    char dataNascimento[11]; // Formato: YYYY-MM-DD
    bool disponivel;
    char username[20]; // Identificador
    char password[20];
    enum TipoUtilizador tipo;
} Utilizador;


// REGISTAR
bool efetuarLogin(char *username, char *password);
bool verificarUsername(char *username);
TipoUtilizador tipoRegisto(char *username);
void ListarConta(char* username);

// CRUD FICHEIRO
void lerFicheiroUtilizadores();
void gravarFicheiroUtilizadores();

// CRUD STRUCTS
void CriarUtilizador(Utilizador novoUtilizador);
void EditarUtilizador(char* username, Utilizador utilizadorEditado);
void RemoverUtilizador(char* username);
void ListarUtilizador(char* username, TipoUtilizador *tipoUtilizador, int *tipoNum);


// ORDENAÇÕES
void ordenarPorNome(char *tipoOrdenar);
void ordenarPorIdade(char *tipoOrdenar);

#endif 