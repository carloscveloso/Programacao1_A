#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Utilizador/utilizador.h"
#include "Propriedades/propriedades.h"
#include "Agendamentos/agendamentos.h"

// Variaveis Globais
char username_cliente[50] = "";    // Guarda o username da conta registada no sistema
TipoUtilizador *tipoRegistado;       // Guarda o tipo de utilizador registado no sistema
char proprietarioIndisponivel[20][15];

// Funções auxiliares

bool Permissao(TipoUtilizador necessario){
    if (*tipoRegistado == necessario) {
        return true;
    }
    return false;
}


// Propriedades

// #TOTEST - Menu para escolher que tipo de Ordenação (TODOS)
void EscolherOrdenacaoPropriedades(int numTipoPropriedadeEscolhida){
    int escolha = 0;
    bool verificar = false;

    do {
        printf("-----------------\n");
        printf("Tipo de Listagem\n");
        printf("-----------------\n\n");
        printf("1. Nenhuma Ordem\n");
        printf("2. Preço\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                ListarPropriedade(numTipoPropriedadeEscolhida, proprietarioIndisponivel);
                verificar = true;
                break;
            case 2:
                ListarPropriedadePorPreco(numTipoPropriedadeEscolhida, proprietarioIndisponivel);
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// #TOTEST - Menu para agendar uma visita (CLIENTE)
void MenuClientePropriedades(){
    int escolha = 0;
    int idPropriedadeEscolhida;
    bool verificar = false;

    // Menu Gerir Propriedades
    do {
        printf("-----------------\n");
        printf("Deseja Agendar Uma Visita a Uma Propriedade?\n");
        printf("-----------------\n\n");
        printf("1. Sim\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                do
                {
                    printf("-----------------\n\n");
                    printf("Insira o ID : ");
                    scanf("%d", &idPropriedadeEscolhida);
                } while (VerificarIDPropriedade(idPropriedadeEscolhida, proprietarioIndisponivel));

                int data_dia, data_mes, data_hora;


                printf("-----------------\n\n");
                printf("A que dia é a visita agendada? :");
                scanf("%d", &data_dia);

                printf("-----------------\n\n");
                printf("A que mes é a visita agendada? :");
                scanf("%d", &data_mes);

                printf("-----------------\n\n");
                printf("A que horas será a visita agendada?(Ex: 13) :");
                scanf("%d", &data_hora);

                Propriedade propriedade = ReturnPropriedade(idPropriedadeEscolhida);
                // DOING - Adicionar Agendamento
                agendar_visita(username_cliente, propriedade.username_proprietario, data_dia, data_mes, data_hora, idPropriedadeEscolhida, propriedade.tipo);
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// #TOTEST - Menu para Editar Propriedade
void MenuEditarPropriedade(){
    int escolha = 0;
    int idPropriedadeEscolhida;
    bool sucesso = false;
    bool verificar = false;

    do {
        printf("-----------------\n\n");
        printf("Insira o ID : ");
        scanf("%d", &idPropriedadeEscolhida);

        if(Permissao(AGENTE)){
            if(VerificarIDPropriedadeDeProprietario(idPropriedadeEscolhida, username_cliente)){sucesso = true;}
        } else {
            if(VerificarIDPropriedade(idPropriedadeEscolhida, proprietarioIndisponivel)){sucesso = true;}
        }
    } while (!sucesso);
    
    Propriedade PropriedadeAEditar = ReturnPropriedade(idPropriedadeEscolhida);
    int tipo = 0;

    do {
        printf("-----------------\n");
        printf("Editar Propriedade: %d\n", PropriedadeAEditar.id);
        printf("-----------------\n\n");
        printf("1. Morada\n");
        printf("2. Preço\n");
        printf("3. Tipo\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                // Morada
                printf("\nMorada: ");
                scanf(" %s", PropriedadeAEditar.morada);
                verificar = true;
                break;
            case 2:
                // Preço
                printf("\nPreço: ");
                scanf("%lf", &PropriedadeAEditar.preco);
                verificar = true;
                break;
            case 3:
                // Tipo de Propriedade
                printf("\n1 (CASA)");
                printf("\n2 (APARTAMENTO)");
                printf("\n3 (ESCRITÓRIO)");
                
                do{
                    printf("\nTipo de Propriedade: ");
                    scanf("%d", &tipo);

                    switch (tipo){
                    case 1:
                        PropriedadeAEditar.tipo = CASA;
                        break;
                    case 2:
                        PropriedadeAEditar.tipo = APARTAMENTO;
                        break;
                    case 3:
                        PropriedadeAEditar.tipo = ESCRITORIO;
                        break;
                    default:
                        printf("Tipo de Propriedade inválido. Por favor, escolha uma opção válida.\n");
                        break;
                    }
                }while(tipo == 1 || tipo == 2 || tipo == 3);
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                EditarPropriedade(PropriedadeAEditar);
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// #TOTEST - Menu para Remover Propriedade
void MenuRemoverPropriedade(){
    int escolha = 0;
    int idPropriedadeEscolhida;
    bool sucesso = false;
    bool verificar = false;
    do
    {
        printf("-----------------\n\n");
        printf("Insira o ID : ");
        scanf("%d", &idPropriedadeEscolhida);

        if(Permissao(AGENTE)){
            if(VerificarIDPropriedadeDeProprietario(idPropriedadeEscolhida, username_cliente)){sucesso = true;}
        } else {
            if(VerificarIDPropriedade(idPropriedadeEscolhida, proprietarioIndisponivel)){sucesso = true;}
        }
    } while (!sucesso);

    printf("-----------------\n");
    printf("Tem a Certeza que deseja Remover esta Propriedade?\n");
    printf("Esta decisão é irreversivel");
    printf("-----------------\n\n");
    
    do{
        printf("0 (Não) | 1 (Sim) : ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 0:
            return;
        case 1:
            RemoverPropriedade(idPropriedadeEscolhida);
            verificar = true;
            break;
        default:
            break;
        }
    }while(verificar == false);
}

// #TOTEST - Menu para Adicionar uma Propriedade (AGENTE | ADMINISTRADOR)
void MenuAdicionarPropriedade(){
    
    // Variaveis
    Propriedade novaPropriedade;
    char username[20];
    bool success = false;

    strcpy(novaPropriedade.username_proprietario, username_cliente);

    // Menu
    printf("-----------------\n");
    printf("Adicionar Propriedade\n");
    printf("-----------------\n");

    printf("Morada: ");
    scanf(" %s", novaPropriedade.morada);

    printf("Preço: ");
    scanf("%lf", &novaPropriedade.preco);

    // Tipo de Propriedade
    int tipo = 0;
    bool sucesso = false;
    printf("\n1 (CASA)");
    printf("\n2 (APARTAMENTO)");
    printf("\n3 (ESCRITÓRIO)");
    
    do{
        printf("\nTipo de Propriedade: ");
        scanf("%d", &tipo);

        switch (tipo){
        case 1:
            novaPropriedade.tipo = CASA;
            sucesso = true;
            break;
        case 2:
            novaPropriedade.tipo = APARTAMENTO;
            sucesso = true;
            break;
        case 3:
            novaPropriedade.tipo = ESCRITORIO;
            sucesso = true;
            break;
        default:
            printf("Tipo de Propriedade inválido. Por favor, escolha uma opção válida.\n");
            break;
        }
    }while(sucesso == false);
    
    if(Permissao(AGENTE)){
        strcpy(novaPropriedade.username_proprietario, username_cliente);
    } else {
        ListarUtilizador(*tipoRegistado, 2);

        do {
            printf("\nIndique o proprietário da propriedade: ");
            scanf(" %s", username);

            if(verificarTipo(AGENTE, username)){success=true;}
        } while (success == false);
    }
    
    CriarPropriedade(novaPropriedade);
}

// #TOTEST - Menu para escolher que tipo de Propriedade Listar (TODOS)
void ListarTipoPropriedades(){
    int escolha = 0;
    bool verificar = false;

    // #TOTEST - É preciso fazer as opções das propriedades
    do {
        printf("-----------------\n");
        printf("Tipo de Listagem\n");
        printf("-----------------\n\n");
        printf("1. Casa\n");
        printf("2. Apartamento\n");
        printf("3. Escritório\n");
        printf("4. Todos\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                EscolherOrdenacaoPropriedades(1);
                verificar = true;
                break;
            case 2:
                EscolherOrdenacaoPropriedades(2);
                verificar = true;
                break;
            case 3:
                EscolherOrdenacaoPropriedades(3);
                verificar = true;
                break;
            case 4:
                EscolherOrdenacaoPropriedades(0);
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// #TOTEST - Menu para Editar ou Remover Propriedades (AGENTE | ADMINISTRADOR)
void MenuEditarRemoverPropriedades(){
    int escolha = 0;
    bool verificar = false;

    // Menu Gerir Propriedades
    do {
        printf("-----------------\n");
        printf("Gerir Propriedades\n");
        printf("-----------------\n\n");
        printf("1. Editar Propriedade\n");
        printf("2. Remover Propriedade\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                MenuEditarPropriedade();
                verificar = true;
                break;
            case 2:
                MenuRemoverPropriedade();
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// #TOTEST - Gerir Propriedades (AGENTE | ADMINISTRADOR)
void GerirPropriedades(){
    int escolha = 0;
    bool verificar = false;

    // Menu Gerir Propriedades
    do {
        
        printf("-----------------\n");
        printf("Gerir Propriedades\n");
        printf("-----------------\n\n");
        printf("1. Criar Propriedade\n");
        printf("2. Listar Propriedades\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                MenuAdicionarPropriedade();
                verificar = true;
                break;
            case 2:
                if(Permissao(AGENTE)){
                    ListarPropriedadeDeProprietario(username_cliente);
                } else {
                    ListarTipoPropriedades();
                }
                
                MenuRemoverPropriedade();
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}


void MenuAgendamentoListas(){
    int escolha = 0;
    int verificar = false;

    do{
        printf("-----------------\n");
        printf("Listagem de Agendamentos\n");
        printf("-----------------\n\n");
        printf("1. Listar Visitas por Dia\n");
        printf("2. Listar Visitas por agente\n");
        printf("3. Listar Visitas do Tipo de Propriedade\n");
        printf("4. Listar Visitas Não Comparecidas\n");
        printf("5. Listar Cliente Fila de Espera\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                listar_visitas_por_dia();
                verificar = true;
                break;
            case 2:
                listar_visitas_por_agente();
                verificar = true;
                break;
            case 3:
                listar_visitas_por_tipo_propriedade();
                verificar = true;
                break;
            case 4:
                listar_visitas_nao_compareceu();
                verificar = true;
                break;
            case 5:
                listar_clientes_fila_espera();
                verificar = true;
                break;
            case 0:
                printf("Voltar ao Menu Gerir Agendamentos.\n");
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// Agendamentos

// TODO - Gerir Agendamentos
void GerirAgendamentos(){
    int escolha = 0;
    int verificar = false;

    // Menu Gerir Agendamentos
    do {
        
        printf("-----------------\n");
        printf("Gerir Agendamentos\n");
        printf("-----------------\n\n");
        printf("1. Listar Agendamentos\n");
        printf("2. Histórico de visitas\n");
        printf("3. Gerar Relatório\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                MenuAgendamentoListas();
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// Contas

// #TOTEST - Menu para Editar a conta (a própria ou a de outro utilizador) (TODOS)
void MenuEditarConta(bool propriaConta){
    int escolha = 0;
    bool sucesso = false;
    char usernameEscolhido[50];
    
    do{
        printf("-----------------\n");
        printf("Qual utilizador pretende editar: ");
        scanf(" %s", usernameEscolhido);

        if(verificarUsername(usernameEscolhido)){sucesso=true;}
    } while(sucesso == false);
    
    Utilizador* utilizadorAEditar = ReturnUtilizador(usernameEscolhido);
    bool dataValida = false;
    bool verificar = false;

    do {
        printf("-----------------\n");
        printf("Editar Conta: %s\n", utilizadorAEditar->username);
        printf("-----------------\n\n");
        printf("1. Nome\n");
        printf("2. NIF\n");
        printf("3. Morada\n");
        printf("4. Telefone\n");
        printf("5. Data de Nascimento\n");
        if(propriaConta == true){printf("6. Password\n");}
        if(propriaConta == true){printf("7. Username\n");}
        if(tipoRegistado == ADMINISTRADOR){printf("8. Disponibilidade (0=Não | 1=Sim): %d\n", utilizadorAEditar->disponivel);}
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                // Nome
                printf("\nNome: ");
                scanf(" %s", utilizadorAEditar->nome);
                verificar = true;
                break;
            case 2:
                // NIF
                printf("\nNIF: ");
                scanf("%d", &utilizadorAEditar->NIF);
                verificar = true;
                break;
            case 3:
                // Morada
                printf("\nMorada: ");
                scanf(" %s", utilizadorAEditar->morada);
                verificar = true;
                break;
            case 4:
                // Telefone
                printf("\nNumero de Telefone: ");
                scanf(" %s", utilizadorAEditar->contactoTelefonico);
                verificar = true;
                break;
            case 5:
                // Data de Nascimento
                do{
                    int ano, mes, dia;

                    printf("\nData de Nascimento (Formato: YYYY-MM-DD): ");
                    if (scanf("%4d-%2d-%2d", &ano, &mes, &dia) != 3) {
                        printf("Formato inválido. Certifique-se de usar o formato YYYY-MM-DD.\n\n");
                        continue;
                    }
                    // Formatar em string
                    sprintf(utilizadorAEditar->dataNascimento, "%04d-%02d-%02d", ano, mes, dia);

                    // Validações
                    if (ano >= 0 && ano <= 9999 && mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31){
                        dataValida = true;
                    }           
                } while (dataValida == false);
                verificar = true;
                break;   
            case 6:
                if(propriaConta == false){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;    
                }
                // Password
                do {
                    printf("\nPassword: ");
                    scanf(" %s", utilizadorAEditar->password);
                } while (strlen(utilizadorAEditar->password) < 6);
                verificar = true;
                break;
            case 7:
                if(propriaConta == false){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");

                    break;    
                }
                // Username
                do {
                    printf("\nUsername: ");
                    scanf(" %s", utilizadorAEditar->username);
                } while (verificarUsername(utilizadorAEditar->username));
                verificar = true;
                break;
            case 8:
                if(propriaConta == false){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;    
                }
                // Disponibilidade
                if(utilizadorAEditar->disponivel == false){utilizadorAEditar->disponivel = true;} else {utilizadorAEditar->disponivel = false;}
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                EditarUtilizador(*utilizadorAEditar);
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);

    // Registar
    EditarUtilizador(*utilizadorAEditar);
    gravarFicheiroUtilizadores();
}

// #TOTEST - Menu para Remover a conta (a própria ou a de outro utilizador) (TODOS)
void MenuRemoverConta(bool propriaConta){
    int escolha = 0;
    char usernameEscolhido[100];
    Utilizador* utilizadorARemover;
    bool verificar = false;

    if(propriaConta){
        printf("-----------------\n");
        printf("Tem a Certeza que deseja Remover a Sua Conta?\n");
        printf("Esta decisão é irreversivel");
        printf("-----------------\n\n");
        
        do{
            printf("0 (Não) | 1 (Sim) : ");
            scanf("%d", &escolha);

            switch (escolha)
            {
            case 0:
                return;
            case 1:
                RemoverUtilizador(username_cliente);
                verificar = true;
                break;
            default:
                break;
            }
        }while(verificar == false);
    } else {
        do {
            printf("-----------------\n");
            printf("Qual utilizador pretende editar: ");
            scanf(" %s", usernameEscolhido);

            if(verificarUsername(usernameEscolhido)){
                utilizadorARemover = ReturnUtilizador(usernameEscolhido);

                if(!Permissao(ADMINISTRADOR)){
                    if(utilizadorARemover->tipo != CLIENTE){
                        printf("Erro: Insira um username válido");
                        continue;
                    }
                }

                RemoverUtilizador(utilizadorARemover->username);
                verificar = true;

            } else {
                printf("Erro: Insira um username válido");
            }
        } while (verificar == false);
    }
}

// #TOTEST - Menu que aparece após a listagem das contas (a própria ou a de outro utilizador) (TODOS)
void MenuEditarRemoverContas(bool propriaConta){
    int escolha = 0;
    bool verificar = false;

    // 
    // #TODO - É preciso fazer as opções das propriedades
    do {
        printf("-----------------\n");
        printf("Gerir Conta\n");
        printf("-----------------\n\n");
        printf("1. Remover Conta\n");
        if(propriaConta == true || Permissao(ADMINISTRADOR)){printf("2. Editar Conta\n");}
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                verificar = true;
                break;
            case 2:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                MenuEditarConta(propriaConta);
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// #TOTEST - Menu para escolher qual o tipo de ordenação na listagem (GESTOR | ADMINISTRADOR)
void EscolherOrdenacao(int tipoUtilizadorEscolhido){
    int escolha = 0;
    bool verificar = false;

    // #TOTEST - É preciso fazer as opções das propriedades
    do {
        printf("-----------------\n");
        printf("Tipo de Listagem\n");
        printf("-----------------\n\n");
        printf("1. Nenhuma Ordem\n");
        printf("2. Alfabética\n");
        printf("3. Idade\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                ListarUtilizador(*tipoRegistado, tipoUtilizadorEscolhido);
                if(Permissao(ADMINISTRADOR)){MenuEditarRemoverContas(false);}
                verificar = true;
                break;
            case 2:
                ordenarPorNome(*tipoRegistado, tipoUtilizadorEscolhido);
                if(Permissao(ADMINISTRADOR)){MenuEditarRemoverContas(false);}
                verificar = true;
                break;
            case 3:
                ordenarPorIdade(*tipoRegistado, tipoUtilizadorEscolhido);
                if(Permissao(ADMINISTRADOR)){MenuEditarRemoverContas(false);}
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// #TOTEST - Menu para Adicionar uma conta (ADMINISTRADOR)
void MenuAdicionarConta(){
    
    // Variaveis
    Utilizador novoUtilizador;
    bool dataValida = false;

    // Menu
    printf("-----------------\n");
    printf("Adicionar Utilizador\n");
    printf("-----------------\n");

    // Username
    do {
        printf("\nUsername: ");
        scanf(" %s", novoUtilizador.username);
    } while (verificarUsername(novoUtilizador.username));

    // Password
    do {
        printf("\nPassword: ");
        scanf(" %s", novoUtilizador.password);
    } while (strlen(novoUtilizador.password) < 6);

    // Nome
    printf("\nNome: ");
    scanf(" %s", novoUtilizador.nome);

    // Número de Telefone
    printf("\nNúmero de Telefone: ");
    scanf(" %s", novoUtilizador.contactoTelefonico);

    // Data de Nascimento
    do{
        int ano, mes, dia;

        printf("\nData de Nascimento (Formato: YYYY-MM-DD): ");
        if (scanf("%4d-%2d-%2d", &ano, &mes, &dia) != 3) {
            printf("Formato inválido. Certifique-se de usar o formato YYYY-MM-DD.\n\n");
            continue;
        }
        // Formatar em string
        sprintf(novoUtilizador.dataNascimento, "%04d-%02d-%02d", ano, mes, dia);

        // Validações
        if (ano >= 0 && ano <= 9999 && mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31){
            dataValida = true;
        }           
    } while (dataValida == false);
    
    // NIF
    printf("\nNIF: ");
    scanf("%d", &novoUtilizador.NIF);

    // Morada
    printf("\nMorada: ");
    scanf(" %s", novoUtilizador.morada);

    // Tipo de Utilizador
    int tipo = 0;
    bool sucesso = false;
    printf("\n1 (CLIENTE)");
    printf("\n2 (AGENTE)");
    printf("\n3 (ADMINISTRADOR)");
    
    do{
        printf("\nTipo de Utilizador: ");
        scanf("%d", &tipo);

        switch (tipo){
        case 1:
            novoUtilizador.tipo = CLIENTE;
            sucesso = true;
            break;
        case 2:
            novoUtilizador.tipo = AGENTE;
            sucesso = true;
            break;
        case 3:
            novoUtilizador.tipo = ADMINISTRADOR;
            sucesso = true;
            break;
        default:
            printf("Tipo de utilizador inválido. Por favor, escolha uma opção válida.\n");
            break;
        }
    }while(sucesso == false);

    // Disponibilidade
    novoUtilizador.disponivel = true;

    // Registar
    CriarUtilizador(novoUtilizador);
    gravarFicheiroUtilizadores();
}

// #TOTEST - Menu para escolher qual o tipo de conta a Listar (GESTOR | ADMINISTRADOR)
void MenuListarContas(){
    int escolha = 0;
    bool verificar = false;

    // Menu Listar Contas
    do {
        printf("-----------------\n");
        printf("Listar Contas\n");
        printf("-----------------\n\n");
        printf("1. Sua Conta\n");
        printf("2. Clientes\n");
        if(Permissao(ADMINISTRADOR)){
            printf("3. Agentes\n");
            printf("4. Administrador\n");
            printf("5. Todos\n");
        }
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                ListarConta(username_cliente);
                MenuEditarRemoverContas(true);
                verificar = true;
                break;
            case 2:
                EscolherOrdenacao(1);
                verificar = true;
                break;
            case 3:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                EscolherOrdenacao(2);
                verificar = true;
                break;
            case 4:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                EscolherOrdenacao(3);
                verificar = true;
                break;
            case 5:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                EscolherOrdenacao(0);
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// #TOTEST - Menu para escolher entre Listar ou Criar uma conta (ADMINISTRADOR)
void GerirContas(){
    int escolha = 0;
    bool verificar = false;

    // Menu Gerir Contas
    do {
        
        printf("-----------------\n");
        printf("Gerir Contas\n");
        printf("-----------------\n\n");
        printf("1. Listar Contas\n");
        printf("2. Adicionar Conta\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                MenuListarContas();
                verificar = true;
                break;
            case 2:
                MenuAdicionarConta();
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}


// Menu Principal
void MenuPrincipal(){
    int escolha = 0;
    bool verificar = false;

    // Menu Principal
    do {
        
        printf("-----------------\n");
        printf("Menu Principal\n");
        printf("-----------------\n\n");
        if(Permissao(CLIENTE)){printf("1. Visualizar Propriedades\n");} else {printf("1. Gerir Propriedades\n");}
        if(Permissao(CLIENTE)){printf("2. Visualizar a Sua Conta\n");} else {printf("2. Gerir Contas\n");}
        if(Permissao(CLIENTE)){printf("3. Listar Agendamentos\n");} else {printf("3. Gerir Agendamentos\n");}
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                // Propriedades
                // Não irá guardar para posteriormente ser possivel listar todas as propriedades, mesmo as de agentes indisponiveis
                if(!Permissao(ADMINISTRADOR)){
                    char** agentesIndisponiveis = AgentesIndisponiveis();
                    for (int i = 0; i < 15; i++) {
                        strcpy(proprietarioIndisponivel[i], agentesIndisponiveis[i]);
                    }
                }

                // O Cliente irá diretamente ver as propriedades
                if(Permissao(CLIENTE)){
                    ListarTipoPropriedades();
                    MenuClientePropriedades();
                } else {
                    GerirPropriedades();
                }
                verificar = true;
                break;
            case 2:
                // Contas
                if(Permissao(CLIENTE)){
                    ListarConta(username_cliente);
                    MenuEditarRemoverContas(true);
                    break;
                } else {
                    GerirContas();
                }
                verificar = true;
                break;
            case 3:
                // Agendamentos
                GerirAgendamentos();
                verificar = true;
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (verificar == false);
}

// Função Principal
int main() {
    //Reaver dados no ficheiro
    lerFicheiroUtilizadores();
    lerFicheiroPropriedades();
    adicionarAdministrador();

    // Variaveis
    int escolha;
    bool loginSucesso = false;

    // #TOTEST Menu de Registro
    do {
        
        printf("-----------------\n");
        printf("Bem-vindo!\n");
        printf("-----------------\n\n");
        printf("1. Login\n");
        printf("2. Registrar\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1: {
                // #TOTEST Login

                // Variaveis
                char usuario[20], password[20];
                getchar();

                // Menu
                printf("-----------------\n");
                printf("Login\n");
                printf("-----------------\n");

                printf("\nUsuário: ");
                scanf(" %s", usuario);
                printf("\nSenha: ");
                scanf(" %s", password);

                // Validações
                if (efetuarLogin(usuario, password)) {
                    printf("Login bem-sucedido!\n");

                    //Guardar o usuario registado
                    strcpy(username_cliente , usuario);
                    tipoRegistado = tipoRegisto(usuario);
                    loginSucesso = true;

                    
                    // Se o login for bem-sucedido, sair do menu de login e ir para o menu principal
                    MenuPrincipal();
                    break;
                } else {
                    printf("Credenciais inválidas. Tente novamente.\n");
                    break;
                }
            }
            case 2: {
                // #TOTEST Registrar
                
                // Variaveis
                Utilizador novoUtilizador;
                bool dataValida = false;

                // Menu
                printf("-----------------\n");
                printf("Registrar\n");
                printf("-----------------\n");

                // Username
                do {
                    printf("\nUsername: ");
                    scanf(" %s", novoUtilizador.username);
                } while (verificarUsername(novoUtilizador.username));

                // Password
                do {
                    printf("\nPassword: ");
                    scanf(" %s", novoUtilizador.password);
                } while (strlen(novoUtilizador.password) < 6);

                // Nome
                printf("\nNome: ");
                scanf(" %s", novoUtilizador.nome);

                // Número de Telefone
                printf("\nNúmero de Telefone: ");
                scanf(" %s", novoUtilizador.contactoTelefonico);

                // Data de Nascimento
                do{
                    int ano, mes, dia;

                    printf("\nData de Nascimento (Formato: YYYY-MM-DD): ");
                    if (scanf("%4d-%2d-%2d", &ano, &mes, &dia) != 3) {
                        printf("Formato inválido. Certifique-se de usar o formato YYYY-MM-DD.\n\n");
                        continue;
                    }
                    // Formatar em string
                    sprintf(novoUtilizador.dataNascimento, "%04d-%02d-%02d", ano, mes, dia);

                    // Validações
                    if (ano >= 0 && ano <= 9999 && mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31){
                        dataValida = true;
                    }           
                } while (dataValida == false);
                
                // NIF
                printf("\nNIF: ");
                scanf("%d", &novoUtilizador.NIF);

                // Morada
                printf("\nMorada: ");
                scanf(" %s", &novoUtilizador.morada[100]);

                // Tipo de utilizador
                novoUtilizador.tipo = CLIENTE;
                novoUtilizador.disponivel = true;

                // Registar
                CriarUtilizador(novoUtilizador);


                // Após o registro, retornar ao menu de login e registro
                break;
            }
            case 0:
                printf("Encerrando o programa...\n");
                gravarFicheiroUtilizadores();
                return 0;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (!loginSucesso); // Repetir o menu até que o usuário faça login

    return 0;
}