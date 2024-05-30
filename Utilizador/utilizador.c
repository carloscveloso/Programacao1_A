#include "utilizador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TIPOS_PROPRIEDADES 50
#define MAX_TAM_TIPO 50
#define MAX_UTILIZADORES 100

// Structs e variaveis
struct TipoPropriedade {
    char tipo[MAX_TAM_TIPO];
    double preco;
};

Utilizador utilizadores[MAX_UTILIZADORES];

struct TipoPropriedade tiposPropriedades[MAX_TIPOS_PROPRIEDADES];
int numTiposPropriedades = 0;

int numAgentes = 0;
int numUtilizadores = 0;


/*
void lerTiposPropriedadesDoFicheiro() {
    FILE *file = fopen("Propriedades.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %lf", tiposPropriedades[numTiposPropriedades].tipo, &tiposPropriedades[numTiposPropriedades].preco) == 2) {
            numTiposPropriedades++;
        }
        fclose(file);
    }
}

void escreverTiposPropriedadesNoFicheiro() {
    FILE *file = fopen("Propriedades.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < numTiposPropriedades; i++) {
            fprintf(file, "%s %.2lf\n", tiposPropriedades[i].tipo, tiposPropriedades[i].preco);
        }
        fclose(file);
    }
}

void criarTipoPropriedade(const char *tipo, double preco) {
    if (numTiposPropriedades < MAX_TIPOS_PROPRIEDADES) {
        strcpy(tiposPropriedades[numTiposPropriedades].tipo, tipo);
        tiposPropriedades[numTiposPropriedades].preco = preco;
        numTiposPropriedades++;
        escreverTiposPropriedadesNoFicheiro();
    } else {
        printf("Limite máximo de tipos de propriedades atingido.\n");
    }
}

void editarTipoPropriedade(const char *tipo, double novoPreco) {
    for (int i = 0; i < numTiposPropriedades; i++) {
        if (strcmp(tiposPropriedades[i].tipo, tipo) == 0) {
            tiposPropriedades[i].preco = novoPreco;
            escreverTiposPropriedadesNoFicheiro();
            return;
        }
    }
    printf("Tipo de propriedade não encontrado.\n");
}

void removerTipoPropriedade(const char *tipo) {
    for (int i = 0; i < numTiposPropriedades; i++) {
        if (strcmp(tiposPropriedades[i].tipo, tipo) == 0) {
            for (int j = i; j < numTiposPropriedades - 1; j++) {
                strcpy(tiposPropriedades[j].tipo, tiposPropriedades[j + 1].tipo);
                tiposPropriedades[j].preco = tiposPropriedades[j + 1].preco;
            }
            numTiposPropriedades--;
            escreverTiposPropriedadesNoFicheiro();
            return;
        }
    }
    printf("Tipo de propriedade não encontrado.\n");
}

void listarTiposPropriedades() {
    printf("Tipos de Propriedades:\n");
    for (int i = 0; i < numTiposPropriedades; i++) {
        printf("%s - %.2lf\n", tiposPropriedades[i].tipo, tiposPropriedades[i].preco);
    }
}

*/


// REGISTRO

bool efetuarLogin(char *username, char *password) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0 && strcmp(utilizadores[i].password, password) == 0) {
            printf("Login bem-sucedido.\n");
            return;
        }
    }
    printf("Login inválido.\n");
}

bool verificarUsername(char *username) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0) {
            return true;
        }
    }
    return false;
}

TipoUtilizador tipoRegisto(char *username) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0) {
            return utilizadores[i].tipo;
        }
    }
}

void ListarConta(char* username) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0) {
            printf("--------- %d -------", utilizadores[i].nome);
            printf("\nUsername: ", utilizadores[i].username);
            printf("\nContacto: ", utilizadores[i].contactoTelefonico);
            printf("\nMorada: ", utilizadores[i].morada);
            printf("\nNIF: ", utilizadores[i].NIF);
            printf("\nData de Nascimento: ", utilizadores[i].dataNascimento);
            printf("\nDisponibilidade: ", utilizadores[i].disponivel);
            printf("\nPassword: ", utilizadores[i].password);
            return;
        }
    }
    printf("Utilizador não encontrado.\n");
}


// CRUD FICHEIRO

void lerFicheiroUtilizadores() {
    FILE *file = fopen("Utilizadores.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %d %s %s %s %d %s %s %d", 
                      utilizadores[numUtilizadores].nome, &utilizadores[numUtilizadores].NIF,
                      utilizadores[numUtilizadores].morada, utilizadores[numUtilizadores].contactoTelefonico,
                      utilizadores[numUtilizadores].dataNascimento, &utilizadores[numUtilizadores].disponivel,
                      utilizadores[numUtilizadores].username, utilizadores[numUtilizadores].password,
                      (int *)&utilizadores[numUtilizadores].tipo) != EOF) {
            (numUtilizadores)++;
            if (utilizadores[numUtilizadores - 1].tipo == AGENTE) {
                (numAgentes)++;
            }
        }
        fclose(file);
    }
}

void gravarFicheiroUtilizadores() {
    FILE *file = fopen("utilizadores.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < numUtilizadores; i++) {
            fprintf(file, "%s %d %s %s %s %d %s %s %d\n", 
                    utilizadores[i].nome, utilizadores[i].NIF,
                    utilizadores[i].morada, utilizadores[i].contactoTelefonico,
                    utilizadores[i].dataNascimento, utilizadores[i].disponivel,
                    utilizadores[i].username, utilizadores[i].password,
                    utilizadores[i].tipo);
        }
        fclose(file);
    }
}


// CRUD STRUCTS

void CriarUtilizador(Utilizador novoUtilizador) {
    if (numUtilizadores < MAX_UTILIZADORES) {
        utilizadores[numUtilizadores++] = novoUtilizador;
        // Caso seja um agente, irá adicionar +1 aos agentes
        if (novoUtilizador.tipo == AGENTE) {
            if (numAgentes <= MAX_AGENTES) {
                numAgentes++;
            } else {
                printf("Erro: Limite de agentes atingido.\n");
            }
        }
        printf("Utilizador criado com sucesso.\n");
    } else {
        printf("Erro: Limite de utilizadores atingido.\n");
    }
}

void EditarUtilizador(char* username, Utilizador utilizadorEditado) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0) {
            utilizadores[i] = utilizadorEditado;
            printf("Utilizador editado com sucesso.\n");
            return;
        }
    }
    printf("Erro: Utilizador não encontrado.\n");
}

void RemoverUtilizador(char* username) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0) {
            // Remover nos agentes caso se verifique
            if (utilizadores[i].tipo == AGENTE) {
                numAgentes--;
            }
            for (int j = i; j < numUtilizadores - 1; j++) {
                utilizadores[j] = utilizadores[j + 1];
            }
            numUtilizadores--;
            printf("Utilizador removido com sucesso.\n");
            return;
        }
    }
    printf("Erro: Utilizador não encontrado.\n");
}

void ListarUtilizador(char* username, TipoUtilizador *tipoUtilizador, int *tipoNum) {
    TipoUtilizador tipoPretendido;
    switch (*tipoNum)
    {
    case 1:
        tipoPretendido = CLIENTE;
        break;
    case 2:
        tipoPretendido = AGENTE;
        break;
    case 3:
        tipoPretendido = ADMINISTRADOR;
        break;
    }
    
    for (int i = 0; i < numUtilizadores; i++) {
        // Verifica se o utilizador tem o tipo pretendido
        // Caso tenha um dos 3 tipos, ou caso se peça todos, e caso tenha o mesmo username, irá listar essa conta
        if ((utilizadores[i].tipo == tipoPretendido || tipoNum == 0) && strcmp(utilizadores[i].username, username) == 0) {
            printf("--------- %s -------", utilizadores[i].nome);
            printf("\nUsername: %s", utilizadores[i].username);
            printf("\nContacto: %s", utilizadores[i].contactoTelefonico);
            printf("\nMorada: %s", utilizadores[i].morada);
            if(*tipoUtilizador == ADMINISTRADOR){
                printf("\nNIF: %s", utilizadores[i].NIF);
                printf("\nData de Nascimento: %s", utilizadores[i].dataNascimento);
                printf("\nDisponibilidade: %d", utilizadores[i].disponivel);
                printf("\nPassword: %s", utilizadores[i].password);
            }
            printf("\n");
            return;
        }
    }
    printf("Utilizador não encontrado ou tipo de utilizador não corresponde ao tipo pretendido.\n");
}


// ORDENAÇÕES

void trocar(Utilizador *a, Utilizador *b) {
    Utilizador temp = *a;
    *a = *b;
    *b = temp;
}

void ordenarPorNome(char *tipoOrdenar) {
    // Variaveis
    bool trocado;
    Utilizador utilizadorOrdenado[MAX_UTILIZADORES];
    int numOrdenados = 0;
    
    // Separar os agentes e os clientes
    for (int i = 0; i < numUtilizadores; i++) {
        if ((strcmp(tipoOrdenar, "ADMINISTRADOR") == 0 && utilizadores[i].tipo == ADMINISTRADOR) ||
            (strcmp(tipoOrdenar, "AGENTE") == 0 && utilizadores[i].tipo == AGENTE) ||
            (strcmp(tipoOrdenar, "CLIENTE") == 0 && utilizadores[i].tipo == CLIENTE) ||
            (strcmp(tipoOrdenar, "AMBOS") == 0)) {
            utilizadorOrdenado[numOrdenados] = utilizadores[i];
            numOrdenados++;
        }
    }

    // Aplicar o Bubble Sort
    for (int i = 0; i < numOrdenados - 1; i++) {
        trocado = false;
        for (int j = 0; j < numOrdenados - i - 1; j++) {
            if (strcmp(utilizadorOrdenado[j].nome, utilizadorOrdenado[j + 1].nome) > 0) {
                trocar(&utilizadorOrdenado[j], &utilizadorOrdenado[j + 1]);
                trocado = true;
            }
        }
        if (!trocado)
            break;
    }

    // Imprimir os utilizadores ordenados
}

void ordenarPorIdade(char *tipoOrdenar) {
    // Variaveis
    bool trocado;
    Utilizador utilizadorOrdenado[MAX_UTILIZADORES];
    int numOrdenados = 0;
    
    // Separar os agentes e os clientes
    for (int i = 0; i < numUtilizadores; i++) {
        if ((strcmp(tipoOrdenar, "ADMINISTRADOR") == 0 && utilizadores[i].tipo == ADMINISTRADOR) ||
            (strcmp(tipoOrdenar, "AGENTE") == 0 && utilizadores[i].tipo == AGENTE) ||
            (strcmp(tipoOrdenar, "CLIENTE") == 0 && utilizadores[i].tipo == CLIENTE) ||
            (strcmp(tipoOrdenar, "AMBOS") == 0)) {
            utilizadorOrdenado[numOrdenados] = utilizadores[i];
            numOrdenados++;
        }
    }

    // Aplicar o Bubble Sort
    for (int i = 0; i < numOrdenados - 1; i++) {
        trocado = false;
        for (int j = 0; j < numOrdenados - i - 1; j++) {
            int idadeA = calcularIdade(utilizadores[j].dataNascimento);
            int idadeB = calcularIdade(utilizadores[j + 1].dataNascimento);
            if (idadeA > idadeB) {
                trocar(&utilizadorOrdenado[j], &utilizadorOrdenado[j + 1]);
                trocado = true;
            }
        }
        if (!trocado)
            break;
    }

    // Imprimir os agentes ordenados
}

int calcularIdade(const char *dataNascimento) {
    int anoNascimento, mesNascimento, diaNascimento;
    sscanf(dataNascimento, "%d-%d-%d", &anoNascimento, &mesNascimento, &diaNascimento);

    // Supondo que a data atual é 2024-05-30
    int anoAtual = 2024;
    int mesAtual = 6;
    int diaAtual = 2;

    int idade = anoAtual - anoNascimento;
    if (mesNascimento > mesAtual || (mesNascimento == mesAtual && diaNascimento > diaAtual)) {
        idade--;
    }
    return idade;
}
