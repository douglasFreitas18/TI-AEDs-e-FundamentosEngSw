#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "biblioteca.c"

void mostrar_menu() {
    printf("\n========================================\n");
    printf("      HOTEL DESCANSO GARANTIDO\n");
    printf("========================================\n");
    printf("--- GESTAO DE PESSOAS ---\n");
    printf("1. Cadastrar Cliente\n");
    printf("2. Pesquisar Cliente\n");
    printf("3. Cadastrar Funcionario\n");
    printf("4. Pesquisar Funcionario\n");
    printf("\n--- GESTAO DE QUARTOS E ESTADIAS ---\n");
    printf("5. Cadastrar Quarto\n");
    printf("6. Cadastrar Estadia\n");
    printf("7. Pesquisar Estadias do Cliente\n");
    printf("8. Dar Baixa em Estadia\n");
    printf("9. Calcular Pontos de Fidelidade\n");
    printf("----------------------------------------\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {
        mostrar_menu();
        scanf("%d", &opcao);
        limpar_buffer();

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