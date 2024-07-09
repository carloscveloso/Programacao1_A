#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <time.h>
#include "../Propriedades/propriedades.h"

#define MAX_CLIENTES_FILA_ESPERA 10

// Definição da enumeração para os estados das visitas
typedef enum {
    ESTADO_AGENDADA,
    ESTADO_REALIZADA,
    ESTADO_NAO_COMPARECEU
} EstadoVisita;

// Definição das estruturas
typedef struct {
    char username_agente[50];
    char username_cliente[50];
    int id_propriedade;
    TipoPropriedade tipo_Propriedade;
    int mes;
    int dia;
    int data_hora;
    EstadoVisita estado;
    char relatorio[256];
    float preco;
} Visita;

typedef struct {
    char username_cliente[50];
    int duracao_estimada;
} ClienteFilaEspera;

ClienteFilaEspera fila_espera[MAX_CLIENTES_FILA_ESPERA];
int num_clientes_fila_espera = 0;

// Função para agendar uma visita
void agendar_visita(char username_cliente[50], char username_agente[50], int mes, int dia, int data_hora, int id_propriedade, TipoPropriedade tipo_propriedade);

// Inicializa o sistema de agendamentos
void inicializar_agendamentos();

// Libera a memória alocada para os agendamentos
void libertar_agendamentos();

// Função para listar todas as visitas de hoje e de um determinado dia ordenadas por hora ascendente
void listar_visitas_por_dia(int dia, int mes);

// Função para listar todas as visitas de hoje e de um determinado dia para um determinado agente
void listar_visitas_por_agente(char username_agente[50], int dia);

// Função para listar todas as visitas de hoje e de um determinado dia por tipo de propriedade
void listar_visitas_por_tipo_propriedade(int id_propriedade, int dia);

// Função para obter o histórico de visitas a uma determinada propriedade
void historico_visitas_propriedade(char* id_propriedade);

// Função para simular a realização de uma visita
void realizar_visita(char username_agente[50], int data_hora);

// Função para listar as visitas em que o cliente não compareceu para um determinado dia
void listar_visitas_nao_compareceu(int dia);

// Função para saber quanto foi faturado hoje e este mês por cada tipo de propriedade
void faturamento_por_tipo_propriedade(int dia);

// Função para saber quantas visitas cada agente realizou este mês
void visitas_realizadas_por_agente(char username_agente[50], int mes);

// Função para gerar um relatório por dia e por mês de contas, organizando por tipo de propriedade
void gerar_relatorio(int dia, int mes);

// Funções para a fila de espera
void adicionar_cliente_fila_espera(char username_cliente[50], int duracao_estimada);
void remover_proximo_cliente_fila_espera();
void listar_clientes_fila_espera();
void apresentar_proximo_cliente();
void calcular_tempo_espera_estimado();

#endif