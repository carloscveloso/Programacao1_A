#ifndef PROPRIEDADES_H
#define PROPRIEDADES_H

typedef enum {
    CASA, 
    APARTAMENTO, 
    ESCRITORIO
} TipoPropriedade;

typedef struct {
    TipoPropriedade tipo;
    char morada[150];
    double preco;
    char username_proprietario[20]; // username de um agente
    int id;
    
} Propriedade;

// CRUD FICHEIRO

void lerFicheiroPropriedades();
void gravarFicheiroPropriedades();

// CRUD STRUCTS

void CriarPropriedade(Propriedade novaPropriedade);
void EditarPropriedade(Propriedade propriedadeEditada);
void RemoverPropriedade(int propriedadeRemovida);
void ListarPropriedade(int numPropriedadeEscolhida, char proprietariosIndisponiveis[20][15]);
void ListarPropriedadeDeProprietario(char *username);
bool VerificarIDPropriedade(int ID, char proprietariosIndisponiveis[20][15]);
bool VerificarIDPropriedadeDeProprietario(int ID, char *username);
Propriedade ReturnPropriedade(int ID);

// ORDENAÇÕES

void ListarPropriedadePorPreco(int numPropriedadeEscolhida, char proprietariosIndisponiveis[20][15]);


#endif