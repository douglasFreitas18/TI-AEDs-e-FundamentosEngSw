#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQ_CLIENTES "clientes.bin"
#define ARQ_FUNCIONARIOS "funcionarios.bin"
#define ARQ_QUARTOS "quartos.bin"
#define ARQ_ESTADIAS "estadias.bin"

typedef struct {
    int codigo;
    char nome[100];
    char endereco[150];
    char telefone[20];
} Cliente;

typedef struct {
    int codigo;
    char nome[100];
    char telefone[20];
    char cargo[50];
    double salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidade_hospedes;
    double valor_diaria;
    int status;
} Quarto;

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    int codigo_estadia;
    Data data_entrada;
    Data data_saida;
    int quantidade_diarias;
    int codigo_cliente;
    int numero_quarto;
    int status_estadia;
} Estadia;
