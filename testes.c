#include "munit.c"
#include <unistd.h>
#include "biblioteca.c"

static void* setup(const MunitParameter params[], void* user_data) {
    return NULL;
}

static void tear_down(void* fixture) {
}

static MunitResult teste_calculo_dias(const MunitParameter params[], void* data) {
    Data entrada = {1, 1, 2024};
    Data saida = {5, 1, 2024};

    int dias = calcular_dias(entrada, saida);

    munit_assert_int(dias, ==, 4);

    int dias_erro = calcular_dias(saida, entrada);
    munit_assert_int(dias_erro, <, 0); // Deve dar negativo

    return MUNIT_OK;
}

static MunitResult teste_sobreposicao_datas(const MunitParameter params[], void* data) {
    Data antiga_ent = {10, 1, 2024};
    Data antiga_sai = {20, 1, 2024};

    Data nova_ent1 = {12, 1, 2024};
    Data nova_sai1 = {15, 1, 2024};
    int resultado1 = verifica_sobreposicao_datas(nova_ent1, nova_sai1, antiga_ent, antiga_sai);
    munit_assert_int(resultado1, ==, 1);

    Data nova_ent2 = {21, 1, 2024};
    Data nova_sai2 = {25, 1, 2024};
    int resultado2 = verifica_sobreposicao_datas(nova_ent2, nova_sai2, antiga_ent, antiga_sai);
    munit_assert_int(resultado2, ==, 0);

    Data nova_ent3 = {1, 1, 2024};
    Data nova_sai3 = {9, 1, 2024};
    int resultado3 = verifica_sobreposicao_datas(nova_ent3, nova_sai3, antiga_ent, antiga_sai);
    munit_assert_int(resultado3, ==, 0);

    return MUNIT_OK;
}

static MunitResult teste_persistencia_cliente(const MunitParameter params[], void* data) {
    unlink(ARQ_CLIENTES);

    Cliente c_teste = {999, "Cliente Teste Automatizado", "Rua CPU", "0000-0000"};

    FILE *f = fopen(ARQ_CLIENTES, "wb");
    munit_assert_not_null(f);
    fwrite(&c_teste, sizeof(Cliente), 1, f);
    fclose(f);

    int existe = verificar_cliente_existe(999);
    munit_assert_int(existe, ==, 1);

    int nao_existe = verificar_cliente_existe(12345);
    munit_assert_int(nao_existe, ==, 0);

    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  { "/logica/calculo_dias", teste_calculo_dias, setup, tear_down, MUNIT_TEST_OPTION_NONE, NULL },
  { "/logica/colisao_datas", teste_sobreposicao_datas, setup, tear_down, MUNIT_TEST_OPTION_NONE, NULL },
  { "/arquivo/persistencia_cliente", teste_persistencia_cliente, setup, tear_down, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  "/hotel_testes", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}
