#include "utilizador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIPOS_PROPRIEDADES 50
#define MAX_TAM_TIPO 50
#define MAX_CLIENTES 100

struct TipoPropriedade {
    char tipo[MAX_TAM_TIPO];
    double preco;
};

struct Agente {
    char nome[100];
    int NIF;
    char contactoTelefonico[15];
    char dataNascimento[11]; // Formato: YYYY-MM-DD
};

struct Cliente {
    char nome[100];
    int NIF;
    char contactoTelefonico[15];
};


struct TipoPropriedade tiposPropriedades[MAX_TIPOS_PROPRIEDADES];
int numTiposPropriedades = 0;

struct Agente agentes[MAX_AGENTES];
int numAgentes = 0;

struct Cliente clientes[MAX_CLIENTES];
int numClientes = 0;



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

void lerAgentesDoFicheiro() {
    FILE *file = fopen("Agentes.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %d %s %s", agentes[numAgentes].nome, &agentes[numAgentes].NIF,
               agentes[numAgentes].contactoTelefonico, agentes[numAgentes].dataNascimento) == 4) {
            numAgentes++;
        }
        fclose(file);
    }
}

void escreverAgentesNoFicheiro() {
    FILE *file = fopen("Agentes.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < numAgentes; i++) {
            fprintf(file, "%s %d %s %s\n", agentes[i].nome, agentes[i].NIF,
                    agentes[i].contactoTelefonico, agentes[i].dataNascimento);
        }
        fclose(file);
    }
}

void criarAgente(const char *nome, int NIF, const char *contacto, const char *dataNascimento) {
    if (numAgentes < MAX_AGENTES) {
        strcpy(agentes[numAgentes].nome, nome);
        agentes[numAgentes].NIF = NIF;
        strcpy(agentes[numAgentes].contactoTelefonico, contacto);
        strcpy(agentes[numAgentes].dataNascimento, dataNascimento);
        numAgentes++;
        escreverAgentesNoFicheiro();
    } else {
        printf("Limite máximo de agentes atingido.\n");
    }
}

void editarAgente(int identificador, const char *nome, const char *contacto) {
    for (int i = 0; i < numAgentes; i++) {
        if (i + 1 == identificador) {
            strcpy(agentes[i].nome, nome);
            strcpy(agentes[i].contactoTelefonico, contacto);
            escreverAgentesNoFicheiro();
            return;
        }
    }
    printf("Agente não encontrado.\n");
}

void removerAgente(int identificador) {
    for (int i = 0; i < numAgentes; i++) {
        if (i + 1 == identificador) {
            for (int j = i; j < numAgentes - 1; j++) {
                strcpy(agentes[j].nome, agentes[j + 1].nome);
                agentes[j].NIF = agentes[j + 1].NIF;
                strcpy(agentes[j].contactoTelefonico, agentes[j + 1].contactoTelefonico);
                strcpy(agentes[j].dataNascimento, agentes[j + 1].dataNascimento);
            }
            numAgentes--;
            escreverAgentesNoFicheiro();
            return;
        }
    }
    printf("Agente não encontrado.\n");
}

int compararPorNome(const void *a, const void *b) {
    const struct Agente *agenteA = (const struct Agente *)a;
    const struct Agente *agenteB = (const struct Agente *)b;
    return strcmp(agenteA->nome, agenteB->nome);
}

int compararPorIdade(const void *a, const void *b) {
    const struct Agente *agenteA = (const struct Agente *)a;
    const struct Agente *agenteB = (const struct Agente *)b;
    int anoA = atoi(strtok(agenteA->dataNascimento, "-"));
    int anoB = atoi(strtok(agenteB->dataNascimento, "-"));
    return anoA - anoB;
}

void listarAgentesAlfabeticamente() {
    qsort(agentes, numAgentes, sizeof(struct Agente), compararPorNome);
    printf("Agentes (ordenados alfabeticamente):\n");
    for (int i = 0; i < numAgentes; i++) {
        printf("%d. Nome: %s, NIF: %d, Contacto: %s, Data de Nascimento: %s\n", i + 1, agentes[i].nome,
               agentes[i].NIF, agentes[i].contactoTelefonico, agentes[i].dataNascimento);
    }
}

void listarAgentesPorIdade() {
    qsort(agentes, numAgentes, sizeof(struct Agente), compararPorIdade);
    printf("Agentes (ordenados por idade):\n");
    for (int i = 0; i < numAgentes; i++) {
        printf("%d. Nome: %s, NIF: %d, Contacto: %s, Data de Nascimento: %s\n", i + 1, agentes[i].nome,
               agentes[i].NIF, agentes[i].contactoTelefonico, agentes[i].dataNascimento);
    }
}

void gerarRelatorioAgentes(const char *nomeFicheiro) {
    FILE *file = fopen(nomeFicheiro, "w");
    if (file != NULL) {
        fprintf(file, "Relatório de Agentes:\n");
        for (int i = 0; i < numAgentes; i++) {
            fprintf(file, "Nome: %s, NIF: %d, Contacto: %s, Data de Nascimento: %s\n", agentes[i].nome,
                    agentes[i].NIF, agentes[i].contactoTelefonico, agentes[i].dataNascimento);
        }
        fclose(file);
        printf("Relatório de agentes gerado com sucesso.\n");
    } else {
        printf("Erro ao abrir o ficheiro para escrita.\n");
    }
}


void lerClientesDoFicheiro() {
    FILE *file = fopen("Clientes.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %d %s", clientes[numClientes].nome, &clientes[numClientes].NIF,
                      clientes[numClientes].contactoTelefonico) == 3) {
            numClientes++;
        }
        fclose(file);
    }
}

void escreverClientesNoFicheiro() {
    FILE *file = fopen("Clientes.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < numClientes; i++) {
            fprintf(file, "%s %d %s\n", clientes[i].nome, clientes[i].NIF, clientes[i].contactoTelefonico);
        }
        fclose(file);
    }
}

void criarCliente(const char *nome, int NIF, const char *contacto) {
    if (numClientes < MAX_CLIENTES) {
        strcpy(clientes[numClientes].nome, nome);
        clientes[numClientes].NIF = NIF;
        strcpy(clientes[numClientes].contactoTelefonico, contacto);
        numClientes++;
        escreverClientesNoFicheiro();
    } else {
        printf("Limite máximo de clientes atingido.\n");
    }
}

void atualizarCliente(int NIF, const char *novoNome, const char *novoContacto) {
    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].NIF == NIF) {
            strcpy(clientes[i].nome, novoNome);
            strcpy(clientes[i].contactoTelefonico, novoContacto);
            escreverClientesNoFicheiro();
            return;
        }
    }
    printf("Cliente não encontrado.\n");
}

void removerCliente(int NIF) {
    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].NIF == NIF) {
            for (int j = i; j < numClientes - 1; j++) {
                strcpy(clientes[j].nome, clientes[j + 1].nome);
                clientes[j].NIF = clientes[j + 1].NIF;
                strcpy(clientes[j].contactoTelefonico, clientes[j + 1].contactoTelefonico);
            }
            numClientes--;
            escreverClientesNoFicheiro();
            return;
        }
    }
    printf("Cliente não encontrado.\n");
}

void listarClientesAlfabeticamente() {
    qsort(clientes, numClientes, sizeof(struct Cliente), compararPorNome);
    printf("Clientes (ordenados alfabeticamente):\n");
    for (int i = 0; i < numClientes; i++) {
        printf("Nome: %s, NIF: %d, Contacto: %s\n", clientes[i].nome, clientes[i].NIF, clientes[i].contactoTelefonico);
    }
}

void apresentarInformacoesCliente(int NIF) {
    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].NIF == NIF) {
            printf("Nome: %s, NIF: %d, Contacto: %s\n", clientes[i].nome, clientes[i].NIF, clientes[i].contactoTelefonico);
            return;
        }
    }
    printf("Cliente não encontrado.\n");
}