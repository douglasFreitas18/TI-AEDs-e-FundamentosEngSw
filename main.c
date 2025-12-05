#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Truque para iniciantes: Incluir o arquivo .c diretamente
// Isso faz o compilador juntar tudo num arquivo só automaticamente
#include "biblioteca.c"

void mostrar_menu() {
    printf("\n========================================\n");
    printf("      HOTEL DESCANSO GARANTIDO\n");
    printf("========================================\n");
    printf("1. Cadastrar Cliente\n");
    printf("2. Pesquisar Cliente\n");
    printf("3. Cadastrar Funcionario\n");
    printf("4. Pesquisar Funcionario\n");
    printf("5. Cadastrar Quarto\n");
    printf("----------------------------------------\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    // Configura para aceitar acentos (pode variar conforme o sistema, mas ajuda)
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {
        mostrar_menu();
        scanf("%d", &opcao);
        limpar_buffer(); // Função que criamos lá no biblioteca.c

        switch (opcao) {
            case 1:
                cadastrar_cliente();
                break;
            case 2:
                pesquisar_cliente();
                break;
            case 3:
                cadastrar_funcionario();
                break;
            case 4:
                pesquisar_funcionario();
                break;
            case 5:
                cadastrar_quarto();
                break;
            case 6:
                cadastrar_estadia(); 
                break;
            case 7: 
                pesquisar_estadias_cliente(); 
                break;
            case 8: 
                dar_baixa_estadia(); 
                break;
            case 9:
                calcular_pontos_fidelidade(); 
                break;
            case 0:
                printf("Saindo do sistema... Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}