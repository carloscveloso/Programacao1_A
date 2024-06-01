#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Utilizador/utilizador.h"
#include "Propriedades/propriedades.h"

// Variaveis Globais
char usernameRegistado[20] = "";    // Guarda o username da conta registada no sistema
TipoUtilizador *tipoRegistado;       // Guarda o tipo de utilizador registado no sistema

// Funções auxiliares

bool Permissao(TipoUtilizador necessario){
    if (necessario == tipoRegistado) {
        return true;
    }
    return false;
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
        system("cls");
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

                // Menu
                printf("-----------------\n");
                printf("Login\n");
                printf("-----------------\n");

                printf("\nUsuário: ");
                fgets(usuario, 20, stdin);
                printf("\nSenha: ");
                fgets(password, 20, stdin);

                // Validações
                if (efetuarLogin(usuario, password)) {
                    printf("Login bem-sucedido!\n");

                    //Guardar o usuario registado
                    strcpy(usernameRegistado , usuario);
                    tipoRegistado = tipoRegisto(usuario);
                    loginSucesso = true;

                    system("cls");
                    // Se o login for bem-sucedido, sair do menu de login e ir para o menu principal
                    break;
                } else {
                    printf("Credenciais inválidas. Tente novamente.\n");
                    break;
                }
            }
            case 2: {
                // #TOTEST Registrar
                system("cls");
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
                    fgets(novoUtilizador.username, 20, stdin);
                } while (verificarUsername(novoUtilizador.username));

                // Password
                do {
                    printf("\nPassword: ");
                    fgets(novoUtilizador.password, 20, stdin);
                } while (strlen(novoUtilizador.password) < 6);

                // Nome
                printf("\nNome: ");
                fgets(novoUtilizador.nome, 100, stdin);

                // Número de Telefone
                printf("\nNúmero de Telefone: ");
                fgets(novoUtilizador.contactoTelefonico, 15, stdin);

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
                fgets(novoUtilizador.morada, 100, stdin);

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
    } while (loginSucesso == true); // Repetir o menu até que o usuário faça login

    MenuPrincipal();

    return 0;
}

void MenuPrincipal(){
    int escolha = 0;

    // Menu Principal
    do {
        system("cls");
        printf("-----------------\n");
        printf("Menu Principal\n");
        printf("-----------------\n\n");
        if(Permissao(CLIENTE)){printf("1. Visualizar Propriedades\n");} else {printf("1. Gerir Propriedades\n");}
        if(Permissao(CLIENTE)){printf("2. Visualizar a Sua Conta\n");} else {printf("2. Gerir Contas\n");}
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                GerirPropriedades();
                break;
            case 2:
                if(Permissao(CLIENTE)){
                    ListarConta(usernameRegistado);
                    MenuEditarRemoverContas(true);
                    break;
                }
                if(Permissao(AGENTE)){
                    ListarContas();
                }
                GerirContas();
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

// #TODO - Gerir Propriedades
void GerirPropriedades(){
    int escolha = 0;

    // Menu Gerir Propriedades
    do {
        system("cls");
        printf("-----------------\n");
        printf("Gerir Propriedades\n");
        printf("-----------------\n\n");
        printf("1. Criar Propriedade\n");
        printf("2. Listar Propriedades\n");
        printf("3. Editar Propriedades\n");
        printf("4. Remover Propriedade\n");
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                criarPropriedade(TipoPropriedade tipo, const char* morada, double preco, int id_proprietario);
                break;
            case 2:
                listarPropriedades();
                break;
            case 3:
                editarPropriedade();
                break;
            case 4:
                removerPropriedade();
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
        system("cls");
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
                system("cls");
                ListarContas();
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

// #TOTEST - Menu para escolher qual o tipo de conta a Listar (GESTOR | ADMINISTRADOR)
void ListarContas(){
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
                EscolherOrdenação(1);
                break;
            case 3:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                EscolherOrdenação(2);
                break;
            case 4:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                EscolherOrdenação(3);
                break;
            case 5:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                EscolherOrdenação(0);
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
void EscolherOrdenação(int tipoUtilizadorEscolhido){
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
                ListarUtilizador(tipoRegistado, tipoUtilizadorEscolhido);
                if(Permissao(ADMINISTRADOR)){MenuEditarRemoverContas(false);}
                break;
            case 2:
                ordenarPorNome(tipoRegistado, tipoUtilizadorEscolhido);
                if(Permissao(ADMINISTRADOR)){MenuEditarRemoverContas(false);}
                break;
            case 3:
                ordenarPorIdade(tipoRegistado, tipoUtilizadorEscolhido);
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

// #TOTEST - Menu que aparece após a listagem das contas (a própria ou a de outro utilizador) (TODOS)
void MenuEditarRemoverContas(bool propriaConta){
    int escolha = 0;

    // 
    // #TODO - É preciso fazer as opções das propriedades
    do {
        printf("-----------------\n");
        printf("Gerir Conta\n");
        printf("-----------------\n\n");
        printf("1. Remover Conta");
        if(propriaConta == true || Permissao(ADMINISTRADOR)){printf("2. Editar Conta");}
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

// #TOTEST - Menu para Editar a conta (a própria ou a de outro utilizador) (TODOS)
void MenuEditarConta(bool propriaConta){
    int escolha = 0;
    bool sucesso = false;
    char usernameEscolhido[50];
    
    do{
        printf("-----------------\n");
        printf("Qual utilizador pretende editar: ");
        fgets(usernameEscolhido, 20, stdin);

        if(verificarUsername(usernameEscolhido)){sucesso=true;}
    } while(sucesso == false);
    
    Utilizador utilizadorAEditar = ReturnUtilizador(usernameEscolhido);
    // 
    // #TODO - É preciso fazer as opções das propriedades
    do {
        printf("-----------------\n");
        printf("Editar Conta: %s\n", utilizadorAEditar.username);
        printf("-----------------\n\n");
        printf("1. Nome\n");
        printf("2. NIF\n");
        printf("3. Morada\n");
        printf("4. Telefone\n");
        printf("5. Data de Nascimento\n");
        if(propriaConta == true){printf("6. Password\n");}
        if(propriaConta == true){printf("7. Username\n");}
        if(tipoRegistado == ADMINISTRADOR){printf("8. Disponibilidade (0=Não | 1=Sim): %d\n", utilizadorAEditar.disponivel);}
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
                fgets(utilizadorAEditar.nome, 100, stdin);
                break;
            case 2:
                // NIF
                printf("\nNIF: ");
                scanf("%d", &utilizadorAEditar.NIF);
                break;
            case 3:
                // Morada
                printf("\nMorada: ");
                fgets(utilizadorAEditar.morada, 100, stdin);
                break;
            case 4:
                // Telefone
                printf("\nNumero de Telefone: ");
                fgets(utilizadorAEditar.contactoTelefonico, 15, stdin);
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
                    sprintf(utilizadorAEditar.dataNascimento, "%04d-%02d-%02d", ano, mes, dia);

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
                    fgets(utilizadorAEditar.password, 20, stdin);
                } while (strlen(utilizadorAEditar.password) < 6);

                break;
            case 7:
                if(propriaConta == false){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;    
                }
                // Username
                do {
                    printf("\nUsername: ");
                    fgets(utilizadorAEditar.username, 20, stdin);
                } while (verificarUsername(utilizadorAEditar.username));

                break;
            case 8:
                if(propriaConta == false){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;    
                }
                // Disponibilidade
                if(utilizadorAEditar.disponivel == false){utilizadorAEditar.disponivel = true;} else {utilizadorAEditar.disponivel = false;}
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);

    // Registar
    EditarUtilizador(utilizadorAEditar);
    gravarFicheiroUtilizadores();
}

// #TOTEST - Menu para Remover a conta (a própria ou a de outro utilizador) (TODOS)
void MenuRemoverConta(bool propriaConta){
    int escolha = 0;
    char usernameEscolhido[100];
    Utilizador utilizadorARemover;

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
            fgets(usernameEscolhido, 20, stdin);

            if(verificarUsername(usernameEscolhido)){
                utilizadorARemover = ReturnUtilizador(usernameEscolhido);

                if(!Permissao(ADMINISTRADOR)){
                    if(utilizadorARemover.tipo != CLIENTE){
                        printf("Erro: Insira um username válido");
                        continue;
                    }
                }

                RemoverUtilizador(utilizadorARemover.username);

            } else {
                printf("Erro: Insira um username válido");
            }
        } while (true);
    }
}

// #TOTEST - Menu para Adicionar uma conta (ADMINISTRADOR)
void MenuAdicionarConta(){
    system("cls");
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
        fgets(novoUtilizador.username, 20, stdin);
    } while (verificarUsername(novoUtilizador.username));

    // Password
    do {
        printf("\nPassword: ");
        fgets(novoUtilizador.password, 20, stdin);
    } while (strlen(novoUtilizador.password) < 6);

    // Nome
    printf("\nNome: ");
    fgets(novoUtilizador.nome, 100, stdin);

    // Número de Telefone
    printf("\nNúmero de Telefone: ");
    fgets(novoUtilizador.contactoTelefonico, 15, stdin);

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
    fgets(novoUtilizador.morada, 100, stdin);

    // Tipo de utilizador
    int tipo = 0;
    printf("\n1 (CLIENTE)");
    printf("\n2 (AGENTE)");
    printf("\n3 (ADMINISTRADOR)");
    
    do{
        printf("\nTipo de Utilizador: ");
        scanf("%d", &tipo);

        switch (tipo){
        case 1:
            novoUtilizador.tipo = CLIENTE;
            break;
        case 2:
            novoUtilizador.tipo = AGENTE;
            break;
        case 3:
            novoUtilizador.tipo = ADMINISTRADOR;
            break;
        default:
            printf("Tipo de utilizador inválido. Por favor, escolha uma opção válida.\n");
            break;
        }
    }while(tipo == 1 || tipo == 2 || tipo == 3);

    // Disponibilidade
    novoUtilizador.disponivel = true;

    // Registar
    CriarUtilizador(novoUtilizador);
    gravarFicheiroUtilizadores();
}