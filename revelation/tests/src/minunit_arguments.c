#include "../includes/minunit_arguments.h"
<<<<<<< HEAD
=======
#include "../../includes/arguments.h"
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c

/******************************************************************
 *  Module with Unit Tests.
 *  Author: Gabriela Cavalcante
 ******************************************************************/



/******************************************************************
 * Test if the program accepts file with valid file signature.
 * Test to ../resource/VALID/RGB_test.png
 * Test to ../resource/VALID/RGBA_test.png
 * Test to ../resource/VALID/BMP_test.bmp
 * Test to ../resource/VALID/PPM_test.ppm
 * Test to ../resource/VALID/PPM_test.txt
 * Test to ../resource/VALID/PGM_test.pgm
 * Test to ../resource/VALID/PGM_test.jpg
 ******************************************************************/
MU_TEST(test_check_imageSignature) {
    char* format;
    mu_check(check_imageSignature("../../resource/VALID/RGB_test.png", &format) == EXIT_SUCCESS);
    mu_check(check_imageSignature("../../resource/VALID/RGBA_test.png", &format) == EXIT_SUCCESS);
    mu_check(check_imageSignature("../../resource/VALID/BMP_test.bmp", &format) == EXIT_SUCCESS);
    mu_check(check_imageSignature("../../resource/VALID/PPM_test.ppm", &format) == EXIT_SUCCESS);
    mu_check(check_imageSignature("../../resource/VALID/PPM_test.txt", &format) == EXIT_SUCCESS);
    mu_check(check_imageSignature("../../resource/VALID/PGM_test.pgm", &format) == EXIT_SUCCESS);
    mu_check(check_imageSignature("../../resource/VALID/PGM_test.jpg", &format) == EXIT_SUCCESS);
}

/******************************************************************
 * Test if images with invalid file signature don't are accepts.
 * Expect return 0 when the input is invalid.
 * Test with input 'format_error', it's not valid.
 * Test with input '../resource/GIT_test.gif', GIF isn't a format valid.
 * Test with input '../resource/ERROR_jpg.png', it's a image JPG but we change the name to .png
 * Test with argument without character.
 ******************************************************************/
MU_TEST(test_check_imageSignature_error) {
    char* format;
    mu_check(check_imageSignature("format_error", &format) == EXIT_FAILURE);
    mu_check(check_imageSignature("../../resource/NOVALID/GIF_test.gif", &format) == EXIT_FAILURE);
    mu_check(check_imageSignature("../../resource/NOVALID/ERROR_txt.png", &format) == EXIT_FAILURE);
    mu_check(check_imageSignature("../../resource/NOVALID/ERROR_jpg.png", &format) == EXIT_FAILURE); // this image is .jpg
    mu_check(check_imageSignature(" ", &format) == EXIT_FAILURE);
}


/******************************************************************
 * Test if path are accepts.
 * Expect return 1 when the input is invalid.
 * Test with input '../resource/street.jpg'
 * Test with input '../resource/BMP_test.bmp'
 * Test with input '../resource/PGM_test.jpg'
 ******************************************************************/
MU_TEST(test_check_pathImageIn) {
    mu_check(check_pathImageIn("../../resource/VALID/PPM_test.txt") == EXIT_SUCCESS);
    mu_check(check_pathImageIn("../../resource/VALID/BMP_test.bmp") == EXIT_SUCCESS);
    mu_check(check_pathImageIn("../../resource/VALID/PGM_test.jpg") == EXIT_SUCCESS);
}

/******************************************************************
 * Test if the program don't accept invalid path
 * Expect return 0 when the input is invalid.
 * Test with input 'image_error', it's not a path valid.
 * Test with argument without character.
 ******************************************************************/
MU_TEST(test_check_pathImageIn_error) {
    mu_check(check_pathImageIn("image_error") == EXIT_FAILURE);
    mu_check(check_pathImageIn(" ") == EXIT_FAILURE);
}

/******************************************************************
 * Test if pathOut are accepts.
 * Expect return 1 when the input is invalid.
 * Test with input '../resource/street.jpg', in this case, the user choose a image file to output
 * Test with input '../resource/', in this case, the user choose a folder to output
 ******************************************************************/
MU_TEST(test_check_pathImageOut) {
    mu_check(check_pathImageOut("../../resource/VALID/RGB_test.png") == EXIT_SUCCESS);
    mu_check(check_pathImageOut("../../resource/") == EXIT_SUCCESS);
}

/******************************************************************
 * Test if the program don't accept invalid path
 * Expect return 0 when the input is invalid.
 * Test with input 'image_error', it's not a path valid.
 * Test with argument without character.
 ******************************************************************/
MU_TEST(test_check_pathImageOut_error) {
    mu_check(check_pathImageOut("image_error") == EXIT_FAILURE);
    mu_check(check_pathImageOut(" ") == EXIT_FAILURE);
}

/******************************************************************
 * Test if the program accept valid bit factor. For this, the bit factor
 * number needs to be less than the depth. The depth indicate to type of
 * each pixel of image. For example for derivatives of image you need
 * 16bit instead of 8bit. (http://goo.gl/N39Sid)
 * Expect return 1 when the input is valid.
 * Test with bit factor 3 and depth 8.
 * Test with bit factor 5 and depth 8.
 ******************************************************************/
MU_TEST(test_check_bitFactor) {
    mu_check(check_bitFactor(3, 8) == EXIT_SUCCESS);
    mu_check(check_bitFactor(5, 8) == EXIT_SUCCESS);
}

/******************************************************************
 * Test if the program don't accept invalid bit factory
 * Expect return 0 when the input is invalid.
 * Test with bit factor 5 and depth 1. Error: factor is bigger that depth.
 * Test with bit factor -1 and depth 1. Error: factor is less, but negative.
 * Test with bit factor 0 and depth 8. Error: factor is 0, then, there aren't hide message.
 ******************************************************************/
MU_TEST(test_check_bitFactor_error) {
    mu_check(check_bitFactor(5, 1) == EXIT_FAILURE);
    mu_check(check_bitFactor(-1, 1) == EXIT_FAILURE);
    mu_check(check_bitFactor(0, 8) == EXIT_FAILURE);
}

/******************************************************************
 * Test if the valid hide patterns are accepts (ignores uper or lower case)
 * Test to direct
 * Test to reverse
 * Test to external_spiral
 * Test to internal_spiral
 ******************************************************************/
MU_TEST(test_check_hidePattern_DIRECT) {
    mu_check(check_hidePattern("direct") == EXIT_SUCCESS);
    mu_check(check_hidePattern("dirEcT") == EXIT_SUCCESS);
    mu_check(check_hidePattern("DIRECT") == EXIT_SUCCESS);
} 

MU_TEST(test_check_hidePattern_REVERSE) {
    mu_check(check_hidePattern("reverse") == EXIT_SUCCESS);
    mu_check(check_hidePattern("reVerSe") == EXIT_SUCCESS);
    mu_check(check_hidePattern("REVERSE") == EXIT_SUCCESS);
} 

MU_TEST(test_check_hidePattern_EXTERNAL) {
    mu_check(check_hidePattern("external_spiral") == EXIT_SUCCESS);
    mu_check(check_hidePattern("exteRnal_SpIral") == EXIT_SUCCESS);
    mu_check(check_hidePattern("EXTERNAL_SPIRAL") == EXIT_SUCCESS);
} 

MU_TEST(test_check_hidePattern_INTERNAL) {
    mu_check(check_hidePattern("internal_spiral") == EXIT_SUCCESS);
    mu_check(check_hidePattern("iNtErnAl_sPiraL") == EXIT_SUCCESS);
    mu_check(check_hidePattern("INTERNAL_SPIRAL") == EXIT_SUCCESS);
}

/******************************************************************
 * Test how the comparison works when the hide pattern is not valid.
 * Expect return 0 when the input is invalid.
 * Test with input 'format_error', it's not a pattern.
 * Test with argument without character.
 ******************************************************************/
MU_TEST(test_check_hidePattern_error) {
    mu_check(check_hidePattern("pattern_error") == EXIT_FAILURE);
    mu_check(check_hidePattern(" ") == EXIT_FAILURE);
}

/******************************************************************
 * RUN TESTS
 ******************************************************************/
MU_TEST_SUITE(test_suite) {
<<<<<<< HEAD
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_check_imageSignature);
=======
    //MU_RUN_TEST(test_check_imageSignature);
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
    MU_RUN_TEST(test_check_imageSignature_error);
    MU_RUN_TEST(test_check_pathImageIn);
    //MU_RUN_TEST(test_check_pathImageIn_error);
    //MU_RUN_TEST(test_check_pathImageOut);
    //MU_RUN_TEST(test_check_pathImageOut_error);
    MU_RUN_TEST(test_check_bitFactor);
    MU_RUN_TEST(test_check_bitFactor_error);
    MU_RUN_TEST(test_check_hidePattern_DIRECT);
    MU_RUN_TEST(test_check_hidePattern_REVERSE);
    MU_RUN_TEST(test_check_hidePattern_EXTERNAL);
    MU_RUN_TEST(test_check_hidePattern_INTERNAL);
    MU_RUN_TEST(test_check_hidePattern_error);
}

<<<<<<< HEAD
=======
/******************************************************************
 * MAIN
 ******************************************************************/
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}