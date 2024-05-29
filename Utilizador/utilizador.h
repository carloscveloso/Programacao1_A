#ifndef UTILIZADOR_H
#define UTILIZADOR_H

#define MAX_AGENTES 15

// Definição dos tipos de utilizadores
enum TipoUtilizador {
    ADMINISTRADOR,
    AGENTE,
    CLIENTE
};

// Estrutura para armazenar informação sobre uma propriedade
struct Propriedade {
    char tipo[50]; 
    char endereco[100]; 
    double preco; 
} Propriedade;

// Estrutura para armazenar informação sobre um utilizador
struct Utilizador {
    char nome[100];
    int NIF;
    char morada[100];
    char contactoTelefonico[15];
    int identificador;
    char dataNascimento[11]; // Formato: YYYY-MM-DD
    int disponivel;
    enum TipoUtilizador tipo;
    struct Propriedade propriedadeInteresse;
} Utilizador;

// Protótipos das funções para gerir tipos de propriedades
void criarTipoPropriedade(const char *tipo, double preco);
void editarTipoPropriedade(const char *tipo, double novoPreco);
void removerTipoPropriedade(const char *tipo);
void listarTiposPropriedades();

// Protótipos das funções para gerir agentes
void criarAgente(const char *nome, int NIF, const char *contacto, const char *dataNascimento);
void editarAgente(int identificador, const char *nome, const char *contacto);
void removerAgente(int identificador);
void listarAgentesAlfabeticamente();
void listarAgentesPorIdade();

// Protótipos das funções para gerar relatórios
void gerarRelatorioAgentes(const char *nomeFicheiro);

// Protótipos das funções para gerir clientes
void criarCliente(const char *nome, int NIF, const char *contacto);
void atualizarCliente(int NIF, const char *novoNome, const char *novoContacto);
void removerCliente(int NIF);
void listarClientesAlfabeticamente();
void apresentarInformacoesCliente(int NIF);

#endif 