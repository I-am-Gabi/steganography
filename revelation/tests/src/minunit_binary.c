#include "../includes/minunit_binary.h"

MU_TEST(test_getBit) {
    mu_check(getBit(0b01010111, 1) == 1);
    mu_check(getBit(0b01010111, 2) == 1);
    mu_check(getBit(0b01010111, 3) == 0);
    mu_check(getBit(0b01010111, 4) == 1);
    mu_check(getBit(0b01010111, 5) == 0);
    mu_check(getBit(0b01010111, 6) == 1);
    mu_check(getBit(0b01010111, 7) == 0);
    mu_check(getBit(0b01010111, 8) == 0);
}

MU_TEST(test_setBit) {
    mu_check(setBit(0b01010111, 1, 0) == 0b01010101);
    mu_check(setBit(0b01010111, 2, 0) == 0b01010011);
    mu_check(setBit(0b01010111, 3, 1) == 0b01011111);
    mu_check(setBit(0b01010111, 4, 0) == 0b01000111);
    mu_check(setBit(0b01010111, 5, 1) == 0b01110111);
    mu_check(setBit(0b01010111, 6, 0) == 0b00010111);
    mu_check(setBit(0b11010111, 7, 1) == 0b11010111);
}

/**
 * Runs tests one after the other
 */
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_setBit);
    MU_RUN_TEST(test_getBit);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
