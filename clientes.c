#include "hotel.h"

int verificar_cliente_existe(int codigo) {
    FILE *f = fopen(ARQ_CLIENTES, "rb");
    if (f == NULL) return 0; 

    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (c.codigo == codigo) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void cadastrar_cliente() {
    Cliente c;
    printf("\n--- CADASTRO DE CLIENTE ---\n");
    
    printf("Digite o codigo do cliente: ");
    scanf("%d", &c.codigo);
    limpar_buffer();

    if (verificar_cliente_existe(c.codigo)) {
        printf("ERRO: Ja existe um cliente com o codigo %d.\n", c.codigo);
        return;
    }

    printf("Nome completo: ");
    fgets(c.nome, MAX_NOME, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0; 

    printf("Endereco: ");
    fgets(c.endereco, MAX_ENDERECO, stdin);
    c.endereco[strcspn(c.endereco, "\n")] = 0;

    printf("Telefone: ");
    fgets(c.telefone, MAX_TELEFONE, stdin);
    c.telefone[strcspn(c.telefone, "\n")] = 0;

    FILE *f = fopen(ARQ_CLIENTES, "ab");
    if (f == NULL) {
        printf("ERRO CRITICO: Nao foi possivel abrir o arquivo de clientes.\n");
        printf("Verifique se a pasta 'dados' existe.\n");
        return;
    }

    fwrite(&c, sizeof(Cliente), 1, f);
    fclose(f);

    printf("SUCESSO: Cliente cadastrado com sucesso!\n");
}

void pesquisar_cliente() {
    int codigo;
    printf("\n--- PESQUISA DE CLIENTE ---\n");
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);
    limpar_buffer();

    FILE *f = fopen(ARQ_CLIENTES, "rb");
    if (f == NULL) {
        printf("Nenhum cliente cadastrado ainda.\n");
        return;
    }

    Cliente c;
    int encontrou = 0;
    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (c.codigo == codigo) {
            printf("\n--- CLIENTE ENCONTRADO ---\n");
            printf("Codigo: %d\n", c.codigo);
            printf("Nome: %s\n", c.nome);
            printf("Endereco: %s\n", c.endereco);
            printf("Telefone: %s\n", c.telefone);
            encontrou = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrou) {
        printf("Cliente com codigo %d nao encontrado.\n", codigo);
    }
}