#ifndef PROPRIEDADES_H
#define PROPRIEDADES_H

typedef enum {
    CASA, 
    APARTAMENTO, 
    ESCRITORIO
} TipoPropriedade;

typedef struct Propriedade {
    TipoPropriedade tipo;
    char morada[150];
    double preco;
    int id_proprietario; 
    int id;
    struct Propriedade* prev;
    struct Propriedade* next;
} Propriedade;

void inicializarPropriedades();
void criarPropriedade(TipoPropriedade tipo, const char* morada, double preco, int id_proprietario);
void listarPropriedades();
void editarPropriedade(int id, TipoPropriedade novo_tipo, const char* nova_morada, double novo_preco);
void removerPropriedade(int id);

void salvarPropriedades(const char* filename);
void carregarPropriedades(const char* filename);

#endif