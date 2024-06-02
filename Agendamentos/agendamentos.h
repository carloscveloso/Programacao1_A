/*
#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <time.h>

#define MAX_CLIENTES_FILA_ESPERA 10

// Definição da enumeração para os estados das visitas
typedef enum {
    ESTADO_AGENDADA,
    ESTADO_REALIZADA,
    ESTADO_NAO_COMPARECEU
} EstadoVisita;

// Definição das estruturas
typedef struct {
    int id_cliente;
    int id_agente;
    time_t data_hora;
    EstadoVisita estado;
    char relatorio[256];
    float preco;
    char tipo_propriedade[50];
} Visita;

typedef struct {
    int id_cliente;
    time_t duracao_estimada;
} ClienteFilaEspera;

ClienteFilaEspera fila_espera[MAX_CLIENTES_FILA_ESPERA];
int num_clientes_fila_espera = 0;

// Função para agendar uma visita
void agendar_visita(int id_cliente, int id_agente, time_t data_hora, const char* tipo_propriedade, float preco);

// Inicializa o sistema de agendamentos
void inicializar_agendamentos();

// Libera a memória alocada para os agendamentos
void libertar_agendamentos();

// Função para listar todas as visitas de hoje e de um determinado dia ordenadas por hora ascendente
void listar_visitas_por_dia(time_t dia);

// Função para listar todas as visitas de hoje e de um determinado dia para um determinado agente
void listar_visitas_por_agente(int id_agente, time_t dia);

// Função para listar todas as visitas de hoje e de um determinado dia por tipo de propriedade
void listar_visitas_por_tipo_propriedade(const char* tipo_propriedade, time_t dia);

// Função para obter o histórico de visitas a uma determinada propriedade
void historico_visitas_propriedade(const char* tipo_propriedade);

// Função para simular a realização de uma visita
void realizar_visita(int id_agente, time_t data_hora);

// Função para listar as visitas em que o cliente não compareceu para um determinado dia
void listar_visitas_nao_compareceu(time_t dia);

// Função para saber quanto foi faturado hoje e este mês por cada tipo de propriedade
void faturamento_por_tipo_propriedade(time_t dia);

// Função para saber quantas visitas cada agente realizou este mês
void visitas_realizadas_por_agente(int id_agente, time_t mes);

// Função para gerar um relatório por dia e por mês de contas, organizando por tipo de propriedade
void gerar_relatorio(time_t dia, time_t mes);

// Funções para a fila de espera
void adicionar_cliente_fila_espera(int id_cliente, time_t duracao_estimada);
void remover_proximo_cliente_fila_espera();
void listar_clientes_fila_espera();
void apresentar_proximo_cliente();
void calcular_tempo_espera_estimado();

#endif
*/