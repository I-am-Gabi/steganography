#include "../includes/minunit_parser.h"
<<<<<<< HEAD

char* formatImage;
char* pathIn;
char* pathOut;
char* hidePattern;
char* channels;
int bitFactor;
IplImage* imgIn;
=======
#include "../../includes/parser.h"
#include "../../includes/arguments.h"
#include "../../includes/image.h"
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c

/******************************************************************
 *  Module with Unit Tests.
 *  Author: Gabriela Cavalcante
 ******************************************************************/

<<<<<<< HEAD

/******************************************************************
 *  Methods to SET: the test runner will run that method prior to each test.
 *  Example actions: creating object instances, initializing db, preparing rules and so on
 ******************************************************************/
void test_setup() {
}

/******************************************************************
 * Method TEARDOWN: the test runner will invoke that method after each test.
 * Example actions: close files, connections, calling transactions callback and so on
 ******************************************************************/
void test_teardown() {
}

/******************************************************************
 *
 ******************************************************************/
MU_TEST(test_parser) {
    char* input[] = { "./reveal", "-in", "../resource/TEST/test_green_2bit.png", "-Fin", "png", "-b", "2", "-c", "Green" };
    mu_check(parser(9, input,
                    &formatImage, &pathIn, &pathOut, &hidePattern, &channels, &bitFactor, &imgIn) == EXIT_SUCCESS);
    mu_check(formatImage == "png");
    mu_check(pathIn == "../resource/TEST/test_green_2bit.png");
    mu_check(pathOut == NULL);
    mu_check(hidePattern == NULL);
    mu_check(channels == "Green");
    mu_check(bitFactor == 2);
}

/******************************************************************
 *
 ******************************************************************/
MU_TEST(test_In) {
    char* input[] = { "./reveal", "-in", "../resource/TEST/test_green_2bit.png" };
    mu_check(parser(3, input,
                    &formatImage, &pathIn, &pathOut, &hidePattern, &channels, &bitFactor, &imgIn) == EXIT_SUCCESS);
    mu_check(formatImage == "png");
    mu_check(pathIn == "../resource/TEST/test_green_2bit.png");
}

/******************************************************************
 *
 ******************************************************************/
MU_TEST(test_BadArgument) {
    char* input[] = { "./reveal" };
    mu_check(parser(1, input,
                    &formatImage, &pathIn, &pathOut, &hidePattern, &channels, &bitFactor, &imgIn) == EXIT_FAILURE);
=======
/******************************************************************
 * Test the method to add item
 ******************************************************************/
MU_TEST(test_check_parser) {
    char* formatImage = "png";
    char* pathIn = "../../resource/TEST/direct/direct_Red_3.png";
    char* pathOut = "../../resource/TEST/output/direct/direct_Red_3_png.txt";
    char* hidePattern = "direct";
    char* channels = "Red,Green,Blue";
    char* magic_number = "HELP";
    int bitFactor = 3;
    IplImage* imgIn = readImage(pathIn);
    mu_check(parser(formatImage, pathIn, pathOut, channels, hidePattern, magic_number, bitFactor, imgIn) == EXIT_SUCCESS);
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
}

/******************************************************************
 * RUN TESTS
 ******************************************************************/
MU_TEST_SUITE(test_suite) {
<<<<<<< HEAD
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_parser);
    MU_RUN_TEST(test_BadArgument);
    MU_RUN_TEST(test_In);
}

=======
    MU_RUN_TEST(test_check_parser);
}

/******************************************************************
 * MAIN
 ******************************************************************/
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
<<<<<<< HEAD
}

=======
}
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
