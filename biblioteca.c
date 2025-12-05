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
    
    q.status = 0;

    FILE *file = fopen(ARQ_QUARTOS, "ab");
    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    fwrite(&q, sizeof(Quarto), 1, file);
    fclose(file);
    printf("Quarto cadastrado com sucesso!\n");
}


#include <time.h>


time_t converter_para_time(Data d) {
    struct tm t = {0};
    t.tm_year = d.ano - 1900; 
    t.tm_mon = d.mes - 1;     
    t.tm_mday = d.dia;
    t.tm_isdst = -1;          
    return mktime(&t);
}


int calcular_dias(Data entrada, Data saida) {
    time_t t_ent = converter_para_time(entrada);
    time_t t_sai = converter_para_time(saida);
    
    double segundos = difftime(t_sai, t_ent);
    return (int)(segundos / (60 * 60 * 24)); 
}

int verifica_sobreposicao_datas(Data nova_ent, Data nova_sai, Data antiga_ent, Data antiga_sai) {
    time_t ne = converter_para_time(nova_ent);
    time_t ns = converter_para_time(nova_sai);
    time_t ae = converter_para_time(antiga_ent);
    time_t as = converter_para_time(antiga_sai);

    if (ne < as && ns > ae) {
        return 1; 
    }
    return 0; 
}

// =============================================================
// MÓDULO DE BAIXA E PESQUISA (Responsável: Douglas)
// =============================================================

void pesquisar_estadias_cliente() {
    int cod_cli;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &cod_cli);
    
    FILE *f = fopen(ARQ_ESTADIAS, "rb");
    if (!f) { printf("Nenhuma estadia cadastrada.\n"); return; }
    
    Estadia e;
    int achou = 0;
    printf("\n--- HISTORICO DE ESTADIAS ---\n");
    while(fread(&e, sizeof(Estadia), 1, f)) {
        if (e.codigo_cliente == cod_cli) {
            printf("Estadia #%d | Quarto: %d | Dias: %d | Status: %s\n", 
                   e.codigo_estadia, e.numero_quarto, e.quantidade_diarias,
                   (e.status_estadia == 1 ? "ATIVA" : "FINALIZADA"));
            achou = 1;
        }
    }
    fclose(f);
    if(!achou) printf("Cliente nunca se hospedou aqui.\n");
}

double buscar_valor_diaria(int num_quarto) {
    FILE *f = fopen(ARQ_QUARTOS, "rb");
    Quarto q;
    while(fread(&q, sizeof(Quarto), 1, f)) {
        if (q.numero == num_quarto) {
            fclose(f);
            return q.valor_diaria;
        }
    }
    fclose(f);
    return 0.0;
}

void dar_baixa_estadia() {
    int cod_estadia;
    printf("Digite o codigo da estadia para dar baixa: ");
    scanf("%d", &cod_estadia);

    FILE *f = fopen(ARQ_ESTADIAS, "rb+");
    if (!f) { printf("Erro no arquivo.\n"); return; }

    Estadia e;
    int achou = 0;
    while(fread(&e, sizeof(Estadia), 1, f)) {
        if (e.codigo_estadia == cod_estadia) {
            if (e.status_estadia == 0) {
                printf("Essa estadia ja foi finalizada!\n");
                fclose(f);
                return;
            }

            double valor_dia = buscar_valor_diaria(e.numero_quarto);
            double total = valor_dia * e.quantidade_diarias;
            
            e.status_estadia = 0;
            
            fseek(f, -sizeof(Estadia), SEEK_CUR);
            fwrite(&e, sizeof(Estadia), 1, f);
            achou = 1;

            printf("\n--- CHECK-OUT REALIZADO ---\n");
            printf("Total a pagar: R$ %.2f\n", total);
            printf("Pontos de fidelidade ganhos: %d\n", e.quantidade_diarias * 10);
            break;
        }
    }
    fclose(f);
    if (!achou) printf("Estadia nao encontrada.\n");
}

void calcular_pontos_fidelidade() {
    int cod_cli;
    printf("Codigo do Cliente: ");
    scanf("%d", &cod_cli);
    
    FILE *f = fopen(ARQ_ESTADIAS, "rb");
    if(!f) return;
    
    Estadia e;
    int pontos = 0;
    while(fread(&e, sizeof(Estadia), 1, f)) {
        if (e.codigo_cliente == cod_cli) {
            pontos += (e.quantidade_diarias * 10);
        }
    }
    fclose(f);
    printf("O cliente tem um total de %d pontos de fidelidade.\n", pontos);
}