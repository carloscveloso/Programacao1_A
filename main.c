#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Utilizador/utilizador.h"
#include "Propriedades/propriedades.h"
#include "Agendamentos/agendamentos.h"

// Variaveis Globais
char usernameRegistado[20] = "";    // Guarda o username da conta registada no sistema
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
                break;
            case 2:
                ListarPropriedadePorPreco(numTipoPropriedadeEscolhida, proprietarioIndisponivel);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}

// #TOTEST - Menu para agendar uma visita (CLIENTE)
void MenuClienteProrpiedades(){
    int escolha = 0;
    int idPropriedadeEscolhida;

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
                    scanf("%d", idPropriedadeEscolhida);
                } while (VerificarIDPropriedade(idPropriedadeEscolhida, proprietarioIndisponivel));
                
                // #TODO - Adicionar Agendamento

                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}

// #TOTEST - Menu para Editar Propriedade
void MenuEditarPropriedade(){
    int escolha = 0;
    int idPropriedadeEscolhida;
    bool sucesso = false;
    do
    {
        printf("-----------------\n\n");
        printf("Insira o ID : ");
        scanf("%d", idPropriedadeEscolhida);

        if(Permissao(AGENTE)){
            if(VerificarIDPropriedadeDeProprietario(idPropriedadeEscolhida, usernameRegistado)){sucesso = true;}
        } else {
            if(VerificarIDPropriedade(idPropriedadeEscolhida, proprietarioIndisponivel)){sucesso = true;}
        }
    } while (!sucesso);
    
    Propriedade PropriedadeAEditar = ReturnPropriedade(idPropriedadeEscolhida);
    
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
                scanf(" %S", PropriedadeAEditar.morada);
                break;
            case 2:
                // Preço
                printf("\nPreço: ");
                scanf("%d", &PropriedadeAEditar.preco);
                break;
            case 3:
                // Tipo de Propriedade
                int tipo = 0;
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

                break;
            case 0:
                printf("Encerrando o programa...\n");
                EditarPropriedade(PropriedadeAEditar);
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}

// #TOTEST - Menu para Remover Propriedade
void MenuRemoverPropriedade(){
    int escolha = 0;
    int idPropriedadeEscolhida;
    bool sucesso = false;
    do
    {
        printf("-----------------\n\n");
        printf("Insira o ID : ");
        scanf("%d", idPropriedadeEscolhida);

        if(Permissao(AGENTE)){
            if(VerificarIDPropriedadeDeProprietario(idPropriedadeEscolhida, usernameRegistado)){sucesso = true;}
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
            break;
        case 1:
            RemoverPropriedade(idPropriedadeEscolhida);
            break;
        default:
            break;
        }
    }while(true);
}

// #TOTEST - Menu para Adicionar uma Propriedade (AGENTE | ADMINISTRADOR)
void MenuAdicionarPropriedade(){
    
    // Variaveis
    Propriedade novaPropriedade;
    char username[20];
    bool success = false;

    strcpy(novaPropriedade.username_proprietario, usernameRegistado);

    // Menu
    printf("-----------------\n");
    printf("Adicionar Propriedade\n");
    printf("-----------------\n");

    printf("Morada: ");
    scanf(" %s", novaPropriedade.morada);

    printf("Preço: ");
    scanf("%d", &novaPropriedade.preco);

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
    }while(!sucesso);
    
    if(Permissao(AGENTE)){
        strcpy(novaPropriedade.username_proprietario, usernameRegistado);
    } else {
        ListarUtilizador(*tipoRegistado, 2);

        do {
            printf("\nIndique o proprietário da propriedade: ");
            scanf(" %s", username);

            if(verificarTipo(AGENTE, username)){success=true;}
        } while (!success);
    }
    
    CriarPropriedade(novaPropriedade);
}

// #TOTEST - Menu para escolher que tipo de Propriedade Listar (TODOS)
void ListarTipoPropriedades(){
    int escolha = 0;

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
                break;
            case 2:
                EscolherOrdenacaoPropriedades(2);
                break;
            case 3:
                EscolherOrdenacaoPropriedades(3);
                break;
            case 4:
                EscolherOrdenacaoPropriedades(0);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}

// #TOTEST - Menu para Editar ou Remover Propriedades (AGENTE | ADMINISTRADOR)
void MenuEditarRemoverPropriedades(){
    int escolha = 0;

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
                break;
            case 2:
                MenuRemoverPropriedade();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}

// #TOTEST - Gerir Propriedades (AGENTE | ADMINISTRADOR)
void GerirPropriedades(){
    int escolha = 0;

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
                break;
            case 2:
                if(Permissao(AGENTE)){
                    ListarPropriedadeDeProprietario(usernameRegistado);
                } else {
                    ListarTipoPropriedades();
                }
                
                MenuRemoverPropriedade();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}


// Agendamentos

// #TODO - Gerir Agendamentos
void GerirAgendamentos(){
    int escolha = 0;

    // Menu Gerir Agendamentos
    do {
        
        printf("-----------------\n");
        printf("Gerir Agendamentos\n");
        printf("-----------------\n\n");
        printf("1. Listar Agendamentos\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
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
                break;
            case 2:
                // NIF
                printf("\nNIF: ");
                scanf("%d", &utilizadorAEditar->NIF);
                break;
            case 3:
                // Morada
                printf("\nMorada: ");
                scanf(" %s", utilizadorAEditar->morada);
                break;
            case 4:
                // Telefone
                printf("\nNumero de Telefone: ");
                scanf(" %s", utilizadorAEditar->contactoTelefonico);
                break;
            case 5:
                // Data de Nascimento
                bool dataValida = false;
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

                break;
            case 8:
                if(propriaConta == false){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;    
                }
                // Disponibilidade
                if(utilizadorAEditar->disponivel == false){utilizadorAEditar->disponivel = true;} else {utilizadorAEditar->disponivel = false;}
                break;
            case 0:
                printf("Encerrando o programa...\n");
                EditarUtilizador(*utilizadorAEditar);
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);

    // Registar
    EditarUtilizador(*utilizadorAEditar);
    gravarFicheiroUtilizadores();
}

// #TOTEST - Menu para Remover a conta (a própria ou a de outro utilizador) (TODOS)
void MenuRemoverConta(bool propriaConta){
    int escolha = 0;
    char usernameEscolhido[100];
    Utilizador* utilizadorARemover;

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
                break;
            case 1:
                RemoverUtilizador(usernameRegistado);
                exit(0);
                break;
            default:
                break;
            }
        }while(true);
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

            } else {
                printf("Erro: Insira um username válido");
            }
        } while (true);
    }
}

// #TOTEST - Menu que aparece após a listagem das contas (a própria ou a de outro utilizador) (TODOS)
void MenuEditarRemoverContas(bool propriaConta){
    int escolha = 0;

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
                
                break;
            case 2:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                MenuEditarConta(propriaConta);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}

// #TOTEST - Menu para escolher qual o tipo de ordenação na listagem (GESTOR | ADMINISTRADOR)
void EscolherOrdenacao(int tipoUtilizadorEscolhido){
    int escolha = 0;

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
                break;
            case 2:
                ordenarPorNome(*tipoRegistado, tipoUtilizadorEscolhido);
                if(Permissao(ADMINISTRADOR)){MenuEditarRemoverContas(false);}
                break;
            case 3:
                ordenarPorIdade(*tipoRegistado, tipoUtilizadorEscolhido);
                if(Permissao(ADMINISTRADOR)){MenuEditarRemoverContas(false);}
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
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
    }while(!sucesso);

    // Disponibilidade
    novoUtilizador.disponivel = true;

    // Registar
    CriarUtilizador(novoUtilizador);
    gravarFicheiroUtilizadores();
}

// #TOTEST - Menu para escolher qual o tipo de conta a Listar (GESTOR | ADMINISTRADOR)
void MenuListarContas(){
    int escolha = 0;

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
                ListarConta(usernameRegistado);
                MenuEditarRemoverContas(true);
                break;
            case 2:
                EscolherOrdenacao(1);
                break;
            case 3:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                EscolherOrdenacao(2);
                break;
            case 4:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                EscolherOrdenacao(3);
                break;
            case 5:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                EscolherOrdenacao(0);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}

// #TOTEST - Menu para escolher entre Listar ou Criar uma conta (ADMINISTRADOR)
void GerirContas(){
    int escolha = 0;

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
                break;
            case 2:
                MenuAdicionarConta();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}


// Menu Principal
void MenuPrincipal(){
    int escolha = 0;

    // Menu Principal
    do {
        
        printf("-----------------\n");
        printf("Menu Principal\n");
        printf("-----------------\n\n");
        if(Permissao(CLIENTE)){printf("1. Visualizar Propriedades\n");} else {printf("1. Gerir Propriedades\n");}
        if(Permissao(CLIENTE)){printf("2. Visualizar a Sua Conta\n");} else {printf("2. Gerir Contas\n");}
        if(Permissao(CLIENTE)){printf("3. Gerir Agendamentos\n");} else {printf("3. Gerir Agendamentos\n");}
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
                    MenuClienteProrpiedades();
                } else {
                    GerirPropriedades();
                }
                
                break;
            case 2:
                // Contas
                if(Permissao(CLIENTE)){
                    ListarConta(usernameRegistado);
                    MenuEditarRemoverContas(true);
                    break;
                } else {
                    GerirContas();
                }
                
                break;
            case 3:
                // Agendamentos
                GerirAgendamentos();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}

// Função Principal
int main() {
    //Reaver dados no ficheiro
    lerFicheiroUtilizadores();
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
                    strcpy(usernameRegistado , usuario);
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
                scanf(" %s", &novoUtilizador.morada);

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