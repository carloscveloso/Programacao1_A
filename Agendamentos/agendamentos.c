#include "agendamentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho inicial para o array dinâmico de visitas
#define TAMANHO_INICIAL 10

// Array dinâmico para armazenar as visitas
static Visita* visitas = NULL;
static int numero_visitas = 0;
static int capacidade_visitas = 0;

void inicializar_agendamentos() {
    // Inicializa o array dinâmico de visitas
    capacidade_visitas = TAMANHO_INICIAL;
    visitas = (Visita*)malloc(capacidade_visitas * sizeof(Visita));
    if (visitas == NULL) {
        fprintf(stderr, "Erro ao alocar memória para agendamentos.\n");
        exit(EXIT_FAILURE);
    }
    numero_visitas = 0;
}

void libertar_agendamentos() {
    // Liberta a memória alocada para o array dinâmico de visitas
    free(visitas);
    visitas = NULL;
    numero_visitas = 0;
    capacidade_visitas = 0;
}

void agendar_visita(char username_cliente[50], char username_agente[50], int mes, int dia, int data_hora, int id_propriedade, TipoPropriedade tipo_propriedade) {
    // Verifica se há espaço suficiente no array dinâmico, se não, dobra o tamanho do array
    if (numero_visitas >= capacidade_visitas) {
        capacidade_visitas *= 2;
        visitas = (Visita*)realloc(visitas, capacidade_visitas * sizeof(Visita));
        if (visitas == NULL) {
            fprintf(stderr, "Erro ao realocar memória para agendamentos.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Preenche os dados da nova visita
    strcpy(visitas[numero_visitas].username_cliente, username_cliente);
    strcpy(visitas[numero_visitas].username_agente, username_agente);
    visitas[numero_visitas].mes = mes;
    visitas[numero_visitas].dia = dia;
    visitas[numero_visitas].data_hora = data_hora;
    visitas[numero_visitas].estado = ESTADO_AGENDADA;
    visitas[numero_visitas].id_propriedade = id_propriedade;
    visitas[numero_visitas].tipo_Propriedade = tipo_propriedade;

    // Incrementa o contador de visitas
    numero_visitas++;

    printf("Foi agendado uma visita na data %i/%i 'as %ih.\n", dia, mes, data_hora);
}

void listar_visitas_por_dia(int dia, int mes) {
    printf("Listando visitas para o dia %i:\n", dia);

    // Percorre o array de visitas
    for (int i = 0; i < numero_visitas; i++) {
        // Verifica se a visita ocorreu no dia especificado
        if (visitas[i].mes == mes && visitas[i].dia == dia) {
            printf("Cliente: %s, Propriedade: %u Hora: %i\n",
                   visitas[i].username_cliente, visitas[i].tipo_Propriedade, visitas[i].data_hora);
        }
    }
}

void listar_visitas_por_agente(char username_agente[50], int dia) {
    printf("Listando visitas para o agente %s no dia %i:\n", username_agente, dia);

    // Percorre o array de visitas
    for (int i = 0; i < numero_visitas; i++) {
        // Verifica se a visita ocorreu no dia especificado e foi atendida pelo agente especificado
        if (visitas[i].username_agente == username_agente && visitas[i].data_hora >= dia && visitas[i].data_hora < dia + 86400) {  // 86400 segundos em um dia
            printf("Cliente: %s, Hora: %i\n",
                   visitas[i].username_agente, visitas[i].data_hora);
        }
    }
}

void listar_visitas_por_tipo_propriedade(int id_propriedade, int dia) {
    printf("Listando visitas para o tipo de propriedade %d no dia %i:\n", id_propriedade, dia);

    // Percorre o array de visitas
    for (int i = 0; i < numero_visitas; i++) {
        // Verifica se a visita ocorreu no dia especificado e é do tipo de propriedade especificado
        if (visitas[i].id_propriedade == id_propriedade && visitas[i].data_hora >= dia && visitas[i].data_hora < dia + 86400) {  // 86400 segundos em um dia
            printf("Cliente: %s, Propriedade: %u Hora: %i\n",
                   visitas[i].username_cliente, visitas[i].tipo_Propriedade, visitas[i].data_hora);
        }
    }
}

void historico_visitas_propriedade(char* id_propriedade) {
    printf("Obtendo histórico de visitas para a propriedade do tipo %s:\n", id_propriedade);

    // Percorre o array de visitas
    for (int i = 0; i < numero_visitas; i++) {
        // Verifica se a visita é do tipo de propriedade especificado
        if (strcmp(visitas[i].id_propriedade, id_propriedade) == 0) {
            printf("Cliente: %d, Agente: %d, Data e Hora: %s, Estado: %d\n",
                   visitas[i].username_cliente, visitas[i].username_agente, ctime(&visitas[i].data_hora), visitas[i].estado);
        }
    }
}

void realizar_visita(char username_agente[50], int data_hora) {
    printf("Realizando visita para o agente %d na data %s:\n", username_agente, ctime(&data_hora));

    // Percorre o array de visitas
    for (int i = 0; i < numero_visitas; i++) {
        // Verifica se a visita corresponde ao agente e data e hora especificados
        if (visitas[i].username_agente == username_agente && visitas[i].data_hora == data_hora) {
            // Atualiza o estado da visita para "Realizada"
            visitas[i].estado = ESTADO_REALIZADA;
            printf("Visita realizada com sucesso.\n");
            return;
        }
    }

    // Se nenhum agendamento corresponder, exibimos uma mensagem de erro
    printf("Erro: Não foi possível encontrar a visita agendada para o agente %d na data %s.\n", username_agente, ctime(&data_hora));
}

void listar_visitas_nao_compareceu(int dia) {
    printf("Listando visitas não comparecidas para o dia %s:\n", ctime(&dia));

    // Percorre o array de visitas
    for (int i = 0; i < numero_visitas; i++) {
        // Verifica se a visita ocorreu no dia especificado e o estado é "Não Compareceu"
        if (visitas[i].estado == ESTADO_NAO_COMPARECEU && visitas[i].data_hora >= dia && visitas[i].data_hora < dia + 86400) {  // 86400 segundos em um dia
            printf("Cliente: %d, Agente: %d, Data e Hora: %s\n",
                   visitas[i].username_cliente[50], visitas[i].username_agente, ctime(&visitas[i].data_hora));
        }
    }
}

void faturamento_por_tipo_propriedade(int dia) {
    printf("Calculando faturamento por tipo de propriedade para o dia %s:\n", ctime(&dia));

    // Array para armazenar o faturamento por tipo de propriedade
    float faturamento_apartamento = 0.0f;
    float faturamento_casa = 0.0f;
    float faturamento_terreno = 0.0f;

    // Percorre o array de visitas
    for (int i = 0; i < numero_visitas; i++) {
        // Verifica se a visita ocorreu no dia especificado
        if (visitas[i].data_hora >= dia && visitas[i].data_hora < dia + 86400) {  // 86400 segundos em um dia
            // Atualiza o faturamento de acordo com o tipo de propriedade da visita
            if (strcmp(visitas[i].id_propriedade, "Apartamento") == 0) {
                faturamento_apartamento += visitas[i].preco;
            } else if (strcmp(visitas[i].id_propriedade, "Casa") == 0) {
                faturamento_casa += visitas[i].preco;
            } else if (strcmp(visitas[i].id_propriedade, "Terreno") == 0) {
                faturamento_terreno += visitas[i].preco;
            }
        }
    }

    // Imprime o faturamento por tipo de propriedade
    printf("Faturamento para Apartamento: %.2f\n", faturamento_apartamento);
    printf("Faturamento para Casa: %.2f\n", faturamento_casa);
    printf("Faturamento para Terreno: %.2f\n", faturamento_terreno);
}

void visitas_realizadas_por_agente(char username_agente[50], int mes) {
    printf("Calculando visitas realizadas pelo agente %d no mês %s:\n", username_agente, ctime(&mes));

    // Contador de visitas realizadas pelo agente
    int visitas_realizadas = 0;

    // Percorre o array de visitas
    for (int i = 0; i < numero_visitas; i++) {
        // Verifica se a visita foi realizada pelo agente especificado e ocorreu no mês especificado
        if (visitas[i].username_agente == username_agente &&
            localtime(&visitas[i].data_hora)->tm_mon == localtime(&mes)->tm_mon &&
            localtime(&visitas[i].data_hora)->tm_year == localtime(&mes)->tm_year) {
            visitas_realizadas++;
        }
    }

    // Imprime o número de visitas realizadas pelo agente
    printf("Número de visitas realizadas: %d\n", visitas_realizadas);
}

void gerar_relatorio(int dia, int mes) {
    printf("Gerando relatório para o dia %s e mês %s:\n", ctime(&dia), ctime(&mes));

    // Arrays para armazenar o faturamento por tipo de propriedade para o dia e o mês
    float faturamento_apartamento_dia = 0.0f;
    float faturamento_casa_dia = 0.0f;
    float faturamento_terreno_dia = 0.0f;

    float faturamento_apartamento_mes = 0.0f;
    float faturamento_casa_mes = 0.0f;
    float faturamento_terreno_mes = 0.0f;

    // Percorre o array de visitas
    for (int i = 0; i < numero_visitas; i++) {
        // Verifica se a visita ocorreu no dia especificado
        if (visitas[i].data_hora >= dia && visitas[i].data_hora < dia + 86400) {  // 86400 segundos em um dia
            // Atualiza o faturamento por tipo de propriedade para o dia
            if (strcmp(visitas[i].id_propriedade, "Apartamento") == 0) {
                faturamento_apartamento_dia += visitas[i].preco;
            } else if (strcmp(visitas[i].id_propriedade, "Casa") == 0) {
                faturamento_casa_dia += visitas[i].preco;
            } else if (strcmp(visitas[i].id_propriedade, "Terreno") == 0) {
                faturamento_terreno_dia += visitas[i].preco;
            }
        }

        // Verifica se a visita ocorreu no mês especificado
        if (localtime(&visitas[i].data_hora)->tm_mon == localtime(&mes)->tm_mon &&
            localtime(&visitas[i].data_hora)->tm_year == localtime(&mes)->tm_year) {
            // Atualiza o faturamento por tipo de propriedade para o mês
            if (strcmp(visitas[i].id_propriedade, "Apartamento") == 0) {
                faturamento_apartamento_mes += visitas[i].preco;
            } else if (strcmp(visitas[i].id_propriedade, "Casa") == 0) {
                faturamento_casa_mes += visitas[i].preco;
            } else if (strcmp(visitas[i].id_propriedade, "Terreno") == 0) {
                faturamento_terreno_mes += visitas[i].preco;
            }
        }
    }

    // Imprime o relatório para o dia
    printf("Faturamento para o dia %s:\n", ctime(&dia));
    printf("Faturamento para Apartamento: %.2f\n", faturamento_apartamento_dia);
    printf("Faturamento para Casa: %.2f\n", faturamento_casa_dia);
    printf("Faturamento para Terreno: %.2f\n", faturamento_terreno_dia);

    // Imprime o relatório para o mês
    printf("Faturamento para o mês %s:\n", ctime(&mes));
    printf("Faturamento para Apartamento: %.2f\n", faturamento_apartamento_mes);
    printf("Faturamento para Casa: %.2f\n", faturamento_casa_mes);
    printf("Faturamento para Terreno: %.2f\n", faturamento_terreno_mes);
}

void adicionar_cliente_fila_espera(char username_cliente[50], int duracao_estimada) {
    // Verifica se a fila de espera não está cheia
    if (num_clientes_fila_espera < MAX_CLIENTES_FILA_ESPERA) {
        // Adiciona o cliente à fila de espera
        fila_espera[num_clientes_fila_espera].username_cliente[50] = username_cliente[50];
        fila_espera[num_clientes_fila_espera].duracao_estimada = duracao_estimada;
        num_clientes_fila_espera++;
        printf("Cliente %d adicionado à fila de espera com duração estimada de visita %ld segundos.\n", username_cliente[50], duracao_estimada);
    } else {
        printf("Erro: A fila de espera está cheia. Não é possível adicionar mais clientes.\n");
    }
}

void remover_proximo_cliente_fila_espera() {
    // Verifica se há clientes na fila de espera
    if (num_clientes_fila_espera > 0) {
        // Move todos os clientes uma posição para frente na fila
        for (int i = 0; i < num_clientes_fila_espera - 1; i++) {
            fila_espera[i] = fila_espera[i + 1];
        }
        // Decrementa o número de clientes na fila de espera
        num_clientes_fila_espera--;
        printf("Próximo cliente removido da fila de espera.\n");
    } else {
        printf("Erro: Não há clientes na fila de espera.\n");
    }
}

void listar_clientes_fila_espera() {
    // Verifica se há clientes na fila de espera
    if (num_clientes_fila_espera > 0) {
        printf("Listando clientes na fila de espera:\n");
        // Percorre a fila de espera e imprime as informações de cada cliente
        for (int i = 0; i < num_clientes_fila_espera; i++) {
            printf("Cliente %d - Duração estimada da visita: %ld segundos\n", fila_espera[i].username_cliente[50], fila_espera[i].duracao_estimada);
        }
    } else {
        printf("Não há clientes na fila de espera.\n");
    }
}

void apresentar_proximo_cliente() {
    // Verifica se há clientes na fila de espera
    if (num_clientes_fila_espera > 0) {
        // Imprime as informações do próximo cliente a ser atendido (primeiro cliente na fila de espera)
        printf("Próximo cliente a ser atendido: Cliente %d - Duração estimada da visita: %ld segundos\n", fila_espera[0].username_cliente[50], fila_espera[0].duracao_estimada);
    } else {
        printf("Não há clientes na fila de espera.\n");
    }
}

void calcular_tempo_espera_estimado() {
    int tempo_espera_total = 0;

    // Verifica se há clientes na fila de espera
    if (num_clientes_fila_espera > 0) {
        // Calcula o tempo de espera estimado para todos os elementos da fila
        for (int i = 0; i < num_clientes_fila_espera; i++) {
            tempo_espera_total += fila_espera[i].duracao_estimada;
        }
        printf("Tempo de espera estimado para todos os elementos da fila: %ld segundos.\n", tempo_espera_total);
    } else {
        printf("Não há clientes na fila de espera.\n");
    }
}