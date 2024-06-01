#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "propriedades.h"

static Propriedade* propriedades_head = NULL;
static int num_propriedades = 0;

void inicializarPropriedades() {
    propriedades_head = NULL;
    num_propriedades = 0;
}

void criarPropriedade(TipoPropriedade tipo, const char* morada, double preco, int id_proprietario) {
    Propriedade* nova_propriedade = (Propriedade*)malloc(sizeof(Propriedade));
    if (!nova_propriedade) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    nova_propriedade->tipo = tipo;
    strncpy(nova_propriedade->morada, morada, sizeof(nova_propriedade->morada) - 1);
    nova_propriedade->morada[sizeof(nova_propriedade->morada) - 1] = '\0';
    nova_propriedade->preco = preco;
    nova_propriedade->id_proprietario = id_proprietario;
    nova_propriedade->id = ++num_propriedades;

    nova_propriedade->prev = NULL;
    nova_propriedade->next = propriedades_head;
    if (propriedades_head) {
        propriedades_head->prev = nova_propriedade;
    }
    propriedades_head = nova_propriedade;
}

void listarPropriedades() {
    Propriedade* atual = propriedades_head;
    while (atual != NULL) {
        printf("Propriedade ID: %d\nTipo: %d\nMorada: %s\nPreço: %.2f\nID Proprietário: %d\n\n",
               atual->id, atual->tipo, atual->morada, atual->preco, atual->id_proprietario);
        atual = atual->next;
    }
}

void editarPropriedade(int id, TipoPropriedade novo_tipo, const char* nova_morada, double novo_preco) {
    Propriedade* propriedade = propriedades_head;
    while (propriedade != NULL && propriedade->id != id) {
        propriedade = propriedade->next;
    }
    if (propriedade == NULL) {
        printf("Propriedade não encontrada.\n");
        return;
    }

    propriedade->tipo = novo_tipo;
    strncpy(propriedade->morada, nova_morada, sizeof(propriedade->morada) - 1);
    propriedade->morada[sizeof(propriedade->morada) - 1] = '\0';
    propriedade->preco = novo_preco;
}

void removerPropriedade(int id) {
    Propriedade* propriedade = propriedades_head;
    while (propriedade != NULL && propriedade->id != id) {
        propriedade = propriedade->next;
    }
    if (propriedade == NULL) {
        printf("Propriedade não encontrada.\n");
        return;
    }

    if (propriedade->prev != NULL) {
        propriedade->prev->next = propriedade->next;
    } else {
        propriedades_head = propriedade->next;
    }
    if (propriedade->next != NULL) {
        propriedade->next->prev = propriedade->prev;
    }
    free(propriedade);
    num_propriedades--;
}

void salvarPropriedades(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }

    Propriedade* atual = propriedades_head;
    while (atual != NULL) {
        fwrite(atual, sizeof(Propriedade), 1, file);
        atual = atual->next;
    }

    fclose(file);
}

void carregarPropriedades(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo para leitura.\n");
        return;
    }

    inicializarPropriedades();
    Propriedade temp;
    while (fread(&temp, sizeof(Propriedade), 1, file)) {
        criarPropriedade(temp.tipo, temp.morada, temp.preco, temp.id_proprietario);
    }

    fclose(file);
}