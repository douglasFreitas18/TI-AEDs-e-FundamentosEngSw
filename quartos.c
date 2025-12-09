#include "hotel.h"

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