#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "propriedades.h"

#define MAX_PROPRIEDADES 100

// Variaveis Globais

int num_propriedades = 0;
int ultimo_id = 0;
Propriedade propriedades[MAX_PROPRIEDADES];



void PrintTipo(int tipo) {
    switch (tipo) {
        case CASA:
            printf("Casa\n");
            break;
        case APARTAMENTO:
            printf("Apartamento\n");
            break;
        case ESCRITORIO:
            printf("Escritorio\n");
            break;
        default:
            printf("Tipo desconhecido\n");
            break;
    }
}


// CRUD FICHEIRO

void lerFicheiroPropriedades() {
    FILE *file = fopen("propriedades.txt", "r");
    if (file != NULL) {
        while (!feof(file)) {
            if (fscanf(file, "%d %s %d %d %s", 
                        &propriedades[num_propriedades].id,
                        propriedades[num_propriedades].morada,
                        &propriedades[num_propriedades].preco,
                        &propriedades[num_propriedades].tipo,
                        propriedades[num_propriedades].username_proprietario)) {
                (num_propriedades)++;
                ultimo_id = propriedades[num_propriedades].id;
            }
        }
        fclose(file);
    }
}

void gravarFicheiroPropriedades() {
    FILE *file = fopen("propriedades.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < num_propriedades; i++) {
            fprintf(file, "%d %s %d %d %s\n", 
                    propriedades[i].id, propriedades[i].morada,
                    propriedades[i].preco, propriedades[i].tipo,
                    propriedades[i].username_proprietario);
        }
        fclose(file);
    }
}


// CRUD STRUCTS

void CriarPropriedade(Propriedade propriedade) {
    propriedade.id = ultimo_id + 1;
    if (num_propriedades < MAX_PROPRIEDADES) {
        propriedades[num_propriedades] = propriedade;
        num_propriedades++;
        printf("Propriedade criada com sucesso.\n");
        gravarFicheiroPropriedades();
        return;
    } else {
        printf("Erro: Limite de propriedades atingido.\n");
    }
}

void EditarPropriedade(Propriedade propriedadeEditada) {
    for (int i = 0; i < num_propriedades; i++) {
        if (propriedades[i].id == propriedadeEditada.id) {
            propriedades[i] = propriedadeEditada;
            printf("Propriedade editada com sucesso.\n");
            gravarFicheiroPropriedades();
            return;
        }
    }
    printf("Propriedade inexistente.\n");
}

void RemoverPropriedade(int propriedadeRemovida) {
    for (int i = 0; i < num_propriedades; i++) {
        if (propriedades[i].id == propriedadeRemovida) {
            num_propriedades--;
            printf("Propriedade removida com sucesso.\n");
            gravarFicheiroPropriedades();
            return;
        }
    }
    printf("Propriedade inexistente.\n");
}

bool VerificarIDPropriedade(int ID, char proprietariosIndisponiveis[20][15]) {
    for (int i = 0; i < num_propriedades; i++) {
        if (propriedades[i].id == ID) {
            for(int j = 0; j < 15; j++){
                if(strcmp(proprietariosIndisponiveis[j], propriedades[i].username_proprietario) == 0){
                    return false;
                } else {
                    return true;
                }
            }
        }
    }
    return false;
}

bool VerificarIDPropriedadeDeProprietario(int ID, char *username) {
    for (int i = 0; i < num_propriedades; i++) {
        if (propriedades[i].id == ID) {
            if(strcmp(username, propriedades[i].username_proprietario) == 0){
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}

Propriedade ReturnPropriedade(int ID){
    for (int i = 0; i < num_propriedades; i++) {
        if (propriedades[i].id == ID) {
            return propriedades[i];
        }
    }
    return propriedades[0];
}


// ORDENAÇÕES

void OrdenarBubleSortPreco(Propriedade temp[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j].preco > temp[j + 1].preco) {
                Propriedade t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }
}

void ListarPropriedadePorPreco(int numPropriedadeEscolhida, char proprietariosIndisponiveis[20][15]) {
    Propriedade temp[MAX_PROPRIEDADES];
    int temp_count = 0;

    for (int i = 0; i < num_propriedades; i++) {
        if ((numPropriedadeEscolhida == 3 && propriedades[i].tipo == CASA) ||
            (numPropriedadeEscolhida == 2 && propriedades[i].tipo == APARTAMENTO) ||
            (numPropriedadeEscolhida == 1 && propriedades[i].tipo == ESCRITORIO) ||
            (numPropriedadeEscolhida == 0)) {
                for(int j = 0; j < 15; j++){
                    if(strcmp(proprietariosIndisponiveis[j], propriedades[i].username_proprietario) == 0){
                        temp[temp_count++] = propriedades[i];
                    }
            }
        }
    }

    // Ordenar por Preço
    OrdenarBubleSortPreco(temp, temp_count);

    // Listar
    for (int i = 0; i < temp_count; i++) {
        printf("------------\n");
        printf("ID: %d\n", temp[i].id);
        printf("Morada: %s\n", temp[i].morada);
        printf("Proprietário: %s\n", temp[i].username_proprietario);
        printf("Preço: %d\n", temp[i].preco);
    }
}

void ListarPropriedade(int numPropriedadeEscolhida, char proprietariosIndisponiveis[20][15]) {
    for (int i = 0; i < num_propriedades; i++) {
        if ((numPropriedadeEscolhida == 3 && propriedades[i].tipo == CASA) ||
            (numPropriedadeEscolhida == 2 && propriedades[i].tipo == APARTAMENTO) ||
            (numPropriedadeEscolhida == 1 && propriedades[i].tipo == ESCRITORIO) ||
            (numPropriedadeEscolhida == 0)) {
                for(int j = 0; j < 15; j++){
                    if(strcmp(proprietariosIndisponiveis[j], propriedades[i].username_proprietario) == 0){
                        printf("------------\n");
                        printf("Morada: %s\n", propriedades[i].morada);
                        printf("Tipo: ");
                        PrintTipo(propriedades[i].tipo);
                        printf("\nPreço: %d\n", propriedades[i].preco);
                    }
                }
        }
    }
}

void ListarPropriedadeDeProprietario(char *username) {
    for (int i = 0; i < num_propriedades; i++) {
        if (strcmp(propriedades[i].username_proprietario, username) == 0) {
            printf("------------\n");
            printf("ID: %d\n", propriedades[i].id);
            printf("Morada: %s\n", propriedades[i].morada);
            printf("Tipo: ");
            PrintTipo(propriedades[i].tipo);
            printf("\nPreço: %d\n", propriedades[i].preco);
        }
    }
}
