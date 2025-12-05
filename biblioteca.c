#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NOME 100
#define MAX_ENDERECO 150
#define MAX_TELEFONE 20
#define MAX_CARGO 50


#define ARQ_CLIENTES "dados/clientes.bin"
#define ARQ_FUNCIONARIOS "dados/funcionarios.bin"
#define ARQ_QUARTOS "dados/quartos.bin"
#define ARQ_ESTADIAS "dados/estadias.bin"


typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int codigo;
    char nome[MAX_NOME];
    char endereco[MAX_ENDERECO];
    char telefone[MAX_TELEFONE];
} Cliente;

typedef struct {
    int codigo;
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
    char cargo[MAX_CARGO];
    double salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidade_hospedes;
    double valor_diaria;
    int status; 
} Quarto;

typedef struct {
    int codigo_estadia;
    Data data_entrada;
    Data data_saida;
    int quantidade_diarias;
    int codigo_cliente;
    int numero_quarto;
    int status_estadia;
} Estadia;


void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


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

int verificar_quarto_existe(int numero) {
    FILE *f = fopen(ARQ_QUARTOS, "rb");
    if (f == NULL) return 0;

    Quarto q;
    while (fread(&q, sizeof(Quarto), 1, f)) {
        if (q.numero == numero) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void cadastrar_quarto() {
    Quarto q;
    printf("\n--- CADASTRO DE QUARTO ---\n");
    
    printf("Numero do quarto: ");
    scanf("%d", &q.numero);
    
    if (verificar_quarto_existe(q.numero)) {
        printf("ERRO: Quarto %d ja existe.\n", q.numero);
        return;
    }

    printf("Quantidade de hospedes: ");
    scanf("%d", &q.quantidade_hospedes);
    
    printf("Valor da diaria: ");
    scanf("%lf", &q.valor_diaria);
    
    q.status = 0; // ComeÃ§a sempre Desocupado

    FILE *file = fopen(ARQ_QUARTOS, "ab");
    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    fwrite(&q, sizeof(Quarto), 1, file);
    fclose(file);
    printf("Quarto cadastrado com sucesso!\n");
}
