#include "hotel.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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