#include "hotel.h"

int verificar_funcionario_existe(int codigo) {
    FILE *f = fopen(ARQ_FUNCIONARIOS, "rb");
    if (f == NULL) return 0;

    Funcionario fun;
    while (fread(&fun, sizeof(Funcionario), 1, f)) {
        if (fun.codigo == codigo) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void cadastrar_funcionario() {
    Funcionario f;
    printf("\n--- CADASTRO DE FUNCIONARIO ---\n");
    
    printf("Codigo: ");
    scanf("%d", &f.codigo);
    limpar_buffer();

    if (verificar_funcionario_existe(f.codigo)) {
        printf("ERRO: Codigo ja utilizado.\n");
        return;
    }

    printf("Nome: ");
    fgets(f.nome, MAX_NOME, stdin);
    f.nome[strcspn(f.nome, "\n")] = 0;

    printf("Telefone: ");
    fgets(f.telefone, MAX_TELEFONE, stdin);
    f.telefone[strcspn(f.telefone, "\n")] = 0;

    printf("Cargo: ");
    fgets(f.cargo, MAX_CARGO, stdin);
    f.cargo[strcspn(f.cargo, "\n")] = 0;

    printf("Salario: ");
    scanf("%lf", &f.salario);
    limpar_buffer();

    FILE *file = fopen(ARQ_FUNCIONARIOS, "ab");
    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    fwrite(&f, sizeof(Funcionario), 1, file);
    fclose(file);
    printf("Funcionario cadastrado!\n");
}

void pesquisar_funcionario() {
    int codigo;
    printf("Pesquisar Codigo funcionario: ");
    scanf("%d", &codigo);
    limpar_buffer();

    FILE *file = fopen(ARQ_FUNCIONARIOS, "rb");
    if (!file) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    Funcionario f;
    int achou = 0;
    while(fread(&f, sizeof(Funcionario), 1, file)) {
        if (f.codigo == codigo) {
            printf("Funcionario: %s | Cargo: %s | Salario: %.2f\n", f.nome, f.cargo, f.salario);
            achou = 1;
            break;
        }
    }
    fclose(file);
    if (!achou) printf("Funcionario nao encontrado.\n");
}