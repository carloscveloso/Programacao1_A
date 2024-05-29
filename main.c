#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    // Menu de login e registro
    int escolhaLoginRegistro;
    do {
        printf("\nBem-vindo!\n");
        printf("1. Login\n");
        printf("2. Registrar\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolhaLoginRegistro);

        switch (escolhaLoginRegistro) {
            case 1: {
                char usuario[20], senha[20];
                printf("\nLogin\n");
                printf("Usuário: ");
                scanf("%s", usuario);
                printf("Senha: ");
                scanf("%s", senha);

                if (fazerLogin(usuario, senha)) {
                    printf("Login bem-sucedido!\n");
                    // Se o login for bem-sucedido, sair do menu de login e ir para o menu principal
                    break;
                } else {
                    printf("Credenciais inválidas. Tente novamente.\n");
                    break;
                }
            }
            case 2: {
                char usuario[20], senha[20];
                printf("\nRegistrar\n");
                printf("Digite um novo nome de usuário: ");
                scanf("%s", usuario);
                printf("Digite uma nova senha: ");
                scanf("%s", senha);
                registrar(usuario, senha);
                // Após o registro, retornar ao menu de login e registro
                break;
            }
            case 3:
                printf("Encerrando o programa...\n");
                return 0;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (escolhaLoginRegistro != 1); // Repetir o menu até que o usuário faça login

    // Após o login, continuar para o menu principal
    int escolha;
    do {
        printf("\nOpções disponíveis:\n");
        printf("1. Gerir tipos de propriedades\n");
        printf("2. Gerir agentes\n");
        printf("3. Gerar relatório de agentes\n");
        printf("4. Gerir clientes\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                // Operações para gerir tipos de propriedades
                // Implemente as chamadas apropriadas para as funções aqui
                break;
            case 2:
                // Operações para gerir agentes
                // Implemente as chamadas apropriadas para as funções aqui
                break;
            case 3:
                // Gerar relatório de agentes
                // Implemente a chamada apropriada para a função aqui
                break;
            case 4:
                // Operações para gerir clientes
                // Implemente as chamadas apropriadas para as funções aqui
                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (escolha != 5);

    return 0;
}