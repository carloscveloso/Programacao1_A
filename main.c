#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <utilizador.h>

// Variaveis Globais
char usernameRegistado[20] = "";    // Guarda o username da conta registada no sistema
TipoUtilizador tipoRegistado;       // Guarda o tipo de utilizador registado no sistema

int main() {
    //Reaver dados no ficheiro
    lerFicheiroUtilizadores();

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
                // #DONE Login

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
                // #DONE Registrar
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
                gravarFicheiroUtilizadores();


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
        printf("1. Gerir Propriedades\n");
        printf("2. Gerir Contas\n");
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
                GerirContas();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                return 0;
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (true);
}

void GerirPropriedades(){
    int escolha = 0;

    // Menu Gerir Propriedades
    // #TODO - É preciso fazer as opções das propriedades
    do {
        system("cls");
        printf("-----------------\n");
        printf("Gerir Propriedades\n");
        printf("-----------------\n\n");
        printf("1. \n");
        printf("2. \n");
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

void GerirContas(){
    int escolha = 0;

    // Menu Gerir Contas
    // #TODO - É preciso fazer as opções das propriedades
    do {
        system("cls");
        printf("-----------------\n");
        printf("Gerir Contas\n");
        printf("-----------------\n\n");
        printf("1. Listar Contas\n");
        if(!Permissao(CLIENTE)){printf("2. Adicionar Contas\n");}
        printf("\n-----------------\n");
        printf("0. Sair\n");
        printf("-----------------\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Lista das opções
        switch (escolha) {
            case 1:
                if(Permissao(CLIENTE)){
                    ListarConta(usernameRegistado);
                }
                ListarContas();
                break;
            case 2:
                if(Permissao(CLIENTE)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                // #TODO
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

void ListarContas(){
    int escolha = 0;

    // Menu Listar Contas
    // #TODO - Menu para escolher a Ordenação da Listagem
    do {
        system("cls");
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
                break;
            case 2:
                ListarUtilizador(usernameRegistado, tipoRegistado, 1);
                break;
            case 3:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                ListarUtilizador(usernameRegistado, tipoRegistado, 2);
                break;
            case 4:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                ListarUtilizador(usernameRegistado, tipoRegistado, 3);
                break;
            case 5:
                if(!Permissao(ADMINISTRADOR)){
                    printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    break;
                }
                ListarUtilizador(usernameRegistado, tipoRegistado, 0);
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

bool Permissao(TipoUtilizador necessario){
    if (necessario == tipoRegistado) {
        return true;
    }
    return false;
}