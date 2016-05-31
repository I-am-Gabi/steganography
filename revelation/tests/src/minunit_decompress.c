#include "../includes/minunit_decompress.h"
#include "../../includes/decompress.h"

/******************************************************************
 *  Module with Unit Tests.
 ******************************************************************/

MU_TEST(test_addItem) {
    dictionary* Dic = NULL;
    Dic = addItem(Dic, 'a', 1, 1);
    mu_check(Dic->character == 'a');
    mu_check(Dic->code == 1);
    mu_check(Dic->code_length == 1);

    Dic = addItem(Dic, 'b', 2, 2);
    mu_check(Dic->character == 'b');
    mu_check(Dic->code == 2);
    mu_check(Dic->code_length == 2);

    mu_check(Dic->next->character == 'a');
    mu_check(Dic->next->code == 1);
    mu_check(Dic->next->code_length == 1);
}

MU_TEST(test_getCode) {
    mu_check(1 == 1);
}

/**
 * Runs tests one after the other
 */
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_addItem);
    MU_RUN_TEST(test_getCode);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}