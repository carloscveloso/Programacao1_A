#include "utilizador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_UTILIZADORES 100

Utilizador utilizadores[MAX_UTILIZADORES];

int numAgentes = 0;
int numUtilizadores = 0;

// ADD ADMIN - Adicionar o admin predefinido caso não exista um

void adicionarAdministrador() {
    if (!verificarUsername("admin") && numUtilizadores < MAX_UTILIZADORES) {
        strcpy(utilizadores[numUtilizadores].username, "admin");
        strcpy(utilizadores[numUtilizadores].password, "admin");
        utilizadores[numUtilizadores].tipo = ADMINISTRADOR;
        numUtilizadores++;
    } else {
        printf("Limite máximo de utilizadores atingido.\n");
    }
}


// REGISTRO

bool efetuarLogin(char *username, char *password) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0 && strcmp(utilizadores[i].password, password) == 0) {
            printf("Login bem-sucedido.\n");
            return true;
        }
    }
    printf("Login inválido.\n");
    return false;
}

bool verificarUsername(char *username) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0) {
            return true;
        }
    }
    return false;
}

TipoUtilizador* tipoRegisto(char *username) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0) {
            return &utilizadores[i].tipo;
        }
    }
    return NULL;
}

void ListarConta(char* username) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0) {
            printf("--------- %s -------\n", utilizadores[i].nome);
            printf("\nUsername: %s\n ", utilizadores[i].username);
            printf("\nContacto: %s\n ", utilizadores[i].contactoTelefonico);
            printf("\nMorada: %s\n", utilizadores[i].morada);
            printf("\nNIF: %d\n", utilizadores[i].NIF);
            printf("\nData de Nascimento: %s\n", utilizadores[i].dataNascimento);
            printf("\nDisponibilidade: %d\n", utilizadores[i].disponivel);
            printf("\nPassword: %s\n", utilizadores[i].password);
            return;
        }
    }
    printf("Utilizador não encontrado.\n");
}

bool verificarTipo(TipoUtilizador pretendido, char *username) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0 && utilizadores[i].tipo == pretendido) {
            return true;
        }
    }
    return false;
}

// CRUD FICHEIRO

void lerFicheiroUtilizadores() {
    FILE *file = fopen("utilizadores.txt", "r");
    if (file != NULL) {
        char linha[300]; // Tamanho suficiente para armazenar uma linha do ficheiro
        while (fgets(linha, sizeof(linha), file)) {
            int tipo;
            if (sscanf(linha, "%s %d %s %s %s %d %s %s %d",
                       utilizadores[numUtilizadores].nome,
                       &utilizadores[numUtilizadores].NIF,
                       utilizadores[numUtilizadores].morada,
                       utilizadores[numUtilizadores].contactoTelefonico,
                       utilizadores[numUtilizadores].dataNascimento,
                       (int*)&utilizadores[numUtilizadores].disponivel,
                       utilizadores[numUtilizadores].username,
                       utilizadores[numUtilizadores].password,
                       &tipo) == 9) {

                switch (tipo) {
                    case 0:
                        utilizadores[numUtilizadores].tipo = ADMINISTRADOR;
                        break;
                    case 1:
                        utilizadores[numUtilizadores].tipo = AGENTE;
                        numAgentes++;
                        break;
                    case 2:
                        utilizadores[numUtilizadores].tipo = CLIENTE;
                        break;
                    default:
                        printf("Tipo de utilizador desconhecido: %d\n", tipo);
                        continue; // Skip this entry
                }
                numUtilizadores++;
            } else {
                printf("Erro ao ler dados do utilizador.\n");
            }
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o ficheiro de utilizadores.\n");
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
        gravarFicheiroUtilizadores();
    } else {
        printf("Erro: Limite de utilizadores atingido.\n");
    }
}

void EditarUtilizador(Utilizador utilizadorEditado) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, utilizadorEditado.username) == 0) {
            utilizadores[i] = utilizadorEditado;
            printf("Utilizador editado com sucesso.\n");
            gravarFicheiroUtilizadores();
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
            if (strcmp(utilizadores[i].username, "admin") == 0) {
                printf("Erro: Não é possivel remover o administrador principal");
            } 
            for (int j = i; j < numUtilizadores - 1; j++) {
                utilizadores[j] = utilizadores[j + 1];
            }
            numUtilizadores--;
            printf("Utilizador removido com sucesso.\n");
            gravarFicheiroUtilizadores();
            return;
        }
    }
    printf("Erro: Utilizador não encontrado.\n");
}

void ListarUtilizador(TipoUtilizador tipoUtilizador, int tipoNum) {
    TipoUtilizador tipoPretendido = CLIENTE;

    switch (tipoNum){
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
        // Caso tenha um dos 3 tipos, ou caso se peça todos irá listar essa conta
        if (utilizadores[i].tipo == tipoPretendido || tipoNum == 0) {
            printf("--------- %s -------", utilizadores[i].nome);
            printf("\nUsername: %s", utilizadores[i].username);
            printf("\nContacto: %s", utilizadores[i].contactoTelefonico);
            printf("\nMorada: %s", utilizadores[i].morada);
            if(tipoUtilizador == ADMINISTRADOR){
                printf("\nNIF: %d", utilizadores[i].NIF);
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

Utilizador* ReturnUtilizador(char* username) {
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(utilizadores[i].username, username) == 0) {
            return &utilizadores[i];
        }
    }
    return NULL;
}

char** AgentesIndisponiveis() {
    char username[20][25];
    int j = 0;
    for(int i=0; i<numUtilizadores; i++){
        if(utilizadores[i].disponivel == 0 && utilizadores[i].tipo == AGENTE) {
            strcpy(username[j], utilizadores[i].username);
            j++;
        }
    }
    return username;
}



// ORDENAÇÕES

void trocar(Utilizador *a, Utilizador *b) {
    Utilizador temp = *a;
    *a = *b;
    *b = temp;
}

void ListarOrdenacao(TipoUtilizador tipoUtilizador, Utilizador *utilizadorOrdenado, int numOrdenados) {
    if(numOrdenados != 0){
        for (int i = 0; i < numOrdenados; i++) {
            printf("--------- %s -------\n", utilizadorOrdenado[i].nome);
            printf("\nUsername: %s\n", utilizadorOrdenado[i].username);
            printf("\nContacto: %s\n", utilizadorOrdenado[i].contactoTelefonico);
            printf("\nMorada: %s\n", utilizadorOrdenado[i].morada);
            if(tipoUtilizador == ADMINISTRADOR){
                printf("\nNIF: %d\n", utilizadorOrdenado[i].NIF);
                printf("\nData de Nascimento: %s\n", utilizadorOrdenado[i].dataNascimento);
                printf("\nDisponibilidade: %d\n", utilizadorOrdenado[i].disponivel);
                printf("\nPassword: %s\n", utilizadorOrdenado[i].password);
            }
            printf("\n");
        }
    } else {
        printf("Utilizador não encontrado ou tipo de utilizador não corresponde ao tipo pretendido.\n");
    }
}

void ordenarPorNome(TipoUtilizador tipoUtilizador, int tipoOrdenar) {
    // Variaveis
    bool trocado;
    Utilizador utilizadorOrdenado[MAX_UTILIZADORES];
    int numOrdenados = 0;
    
    // Separar os agentes e os clientes
    for (int i = 0; i < numUtilizadores; i++) {
        if ((tipoOrdenar == 3 && utilizadores[i].tipo == ADMINISTRADOR) ||
            (tipoOrdenar == 2 && utilizadores[i].tipo == AGENTE) ||
            (tipoOrdenar == 1 && utilizadores[i].tipo == CLIENTE) ||
            (tipoOrdenar == 0)) {
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
    ListarOrdenacao(tipoUtilizador, utilizadorOrdenado, numOrdenados);
}

int calcularIdade(const char *dataNascimento) {
    int anoNascimento, mesNascimento, diaNascimento;
    scanf(dataNascimento, "%d-%d-%d", &anoNascimento, &mesNascimento, &diaNascimento);

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

void ordenarPorIdade(TipoUtilizador tipoUtilizador, int tipoOrdenar) {
    // Variaveis
    bool trocado;
    Utilizador utilizadorOrdenado[MAX_UTILIZADORES];
    int numOrdenados = 0;
    
    // Separar os agentes e os clientes
    for (int i = 0; i < numUtilizadores; i++) {
        if ((tipoOrdenar == 3 && utilizadores[i].tipo == ADMINISTRADOR) ||
            (tipoOrdenar == 2 && utilizadores[i].tipo == AGENTE) ||
            (tipoOrdenar == 1 && utilizadores[i].tipo == CLIENTE) ||
            (tipoOrdenar == 0)) {
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
    ListarOrdenacao(tipoUtilizador, utilizadorOrdenado, numOrdenados);
}


