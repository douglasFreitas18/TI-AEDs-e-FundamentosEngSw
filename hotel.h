#ifndef HOTEL_H
#define HOTEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- CONSTANTES ---
#define MAX_NOME 100
#define MAX_ENDERECO 150
#define MAX_TELEFONE 20
#define MAX_CARGO 50

#define ARQ_CLIENTES "dados/clientes.bin"
#define ARQ_FUNCIONARIOS "dados/funcionarios.bin"
#define ARQ_QUARTOS "dados/quartos.bin"
#define ARQ_ESTADIAS "dados/estadias.bin"

// --- STRUCTS ---
typedef struct {
    int dia, mes, ano;
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

// --- ASSINATURAS DE FUNÇÕES (O Contrato) ---

// Utilidades
void limpar_buffer();
time_t converter_para_time(Data d);
int calcular_dias(Data entrada, Data saida);
int verifica_sobreposicao_datas(Data nova_ent, Data nova_sai, Data antiga_ent, Data antiga_sai);

// Clientes
int verificar_cliente_existe(int codigo);
void cadastrar_cliente();
void pesquisar_cliente();

// Funcionários
int verificar_funcionario_existe(int codigo);
void cadastrar_funcionario();
void pesquisar_funcionario();

// Quartos
int verificar_quarto_existe(int numero);
void cadastrar_quarto();
double buscar_valor_diaria(int num_quarto);

// Estadias
int encontrar_quarto_disponivel(int qtd_hospedes, Data ent, Data sai);
void cadastrar_estadia();
void pesquisar_estadias_cliente();
void dar_baixa_estadia();
void calcular_pontos_fidelidade();

#endif