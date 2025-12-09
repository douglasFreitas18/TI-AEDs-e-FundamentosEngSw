#include "hotel.h"

int encontrar_quarto_disponivel(int qtd_hospedes, Data ent, Data sai) {
    FILE *f_quartos = fopen(ARQ_QUARTOS, "rb");
    if (!f_quartos) return -1;

    Quarto q;
    while (fread(&q, sizeof(Quarto), 1, f_quartos)) {
        if (q.quantidade_hospedes >= qtd_hospedes) {
            
            FILE *f_estadias = fopen(ARQ_ESTADIAS, "rb");
            int ocupado = 0;
            
            if (f_estadias) {
                Estadia e;
                while (fread(&e, sizeof(Estadia), 1, f_estadias)) {
                    if (e.numero_quarto == q.numero && e.status_estadia == 1) {
                        if (verifica_sobreposicao_datas(ent, sai, e.data_entrada, e.data_saida)) {
                            ocupado = 1;
                            break;
                        }
                    }
                }
                fclose(f_estadias);
            }
            
            if (!ocupado) {
                fclose(f_quartos);
                return q.numero;
            }
        }
    }
    fclose(f_quartos);
    return -1;
}

void cadastrar_estadia() {
    Estadia e;
    printf("\n--- NOVA ESTADIA ---\n");
    
    FILE *f = fopen(ARQ_ESTADIAS, "rb");
    if (f == NULL) e.codigo_estadia = 1;
    else {
        fseek(f, 0, SEEK_END);
        e.codigo_estadia = (ftell(f) / sizeof(Estadia)) + 1;
        fclose(f);
    }

    printf("Codigo do Cliente: ");
    scanf("%d", &e.codigo_cliente);
    if (!verificar_cliente_existe(e.codigo_cliente)) {
        printf("Erro: Cliente nao existe.\n");
        return;
    }

    printf("Quantidade de Hospedes: ");
    int qtd;
    scanf("%d", &qtd);

    printf("Data Entrada (dia mes ano): ");
    scanf("%d %d %d", &e.data_entrada.dia, &e.data_entrada.mes, &e.data_entrada.ano);
    
    printf("Data Saida (dia mes ano): ");
    scanf("%d %d %d", &e.data_saida.dia, &e.data_saida.mes, &e.data_saida.ano);

    e.quantidade_diarias = calcular_dias(e.data_entrada, e.data_saida);
    if (e.quantidade_diarias <= 0) {
        printf("Erro: Data de saida deve ser depois da entrada.\n");
        return;
    }

    int num_quarto = encontrar_quarto_disponivel(qtd, e.data_entrada, e.data_saida);
    
    if (num_quarto == -1) {
        printf("Desculpe, nao ha quartos disponiveis para essa capacidade nessas datas.\n");
        return;
    }

    e.numero_quarto = num_quarto;
    e.status_estadia = 1;

    f = fopen(ARQ_ESTADIAS, "ab");
    fwrite(&e, sizeof(Estadia), 1, f);
    fclose(f);

    printf("Estadia agendada com sucesso! Quarto reservado: %d\n", num_quarto);
    printf("Codigo da Estadia: %d\n", e.codigo_estadia);
}

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
            
            fseek(f, -(long)sizeof(Estadia), SEEK_CUR);
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