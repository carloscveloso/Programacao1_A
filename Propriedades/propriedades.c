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