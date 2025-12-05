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