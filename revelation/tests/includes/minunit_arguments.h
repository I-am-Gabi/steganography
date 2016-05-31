<<<<<<< HEAD
/******************************************************************
 *  Module with Unit Tests.
 *  Author: Gabriela Cavalcante
 ******************************************************************/

#ifndef _TESTARGUMENTS_H_
#define _TESTARGUMENTS_H_

#include "../../includes/arguments.h"
#include "../../lib/minunit.h"

void test_setup();

void test_teardown();

MU_TEST(test_check_imageSignature);

MU_TEST(test_check_imageSignature_error);

MU_TEST(test_check_pathImageIn);

MU_TEST(test_check_pathImageIn_error);

MU_TEST(test_check_pathImageOut);

MU_TEST(test_check_pathImageOut_error);

MU_TEST(test_check_bitFactor);

MU_TEST(test_check_bitFactor_error);

MU_TEST(test_check_hidePattern_DIRECT);

MU_TEST(test_check_hidePattern_REVERSE);

MU_TEST(test_check_hidePattern_EXTERNAL);

MU_TEST(test_check_hidePattern_INTERNAL);

MU_TEST(test_check_hidePattern_error);

MU_TEST_SUITE(test_suite);

#endif
=======
//
// Created by Gabriela on 09/12/15.
//

#ifndef PROTOTYPE_MINUNIT_ARGUMENTS_C_H
#define PROTOTYPE_MINUNIT_ARGUMENTS_C_H


#include "../../lib/minunit.h"

#endif //PROTOTYPE_MINUNIT_REVEAL_C_H
>>>>>>> 0a619f2d2eb734c4008a700e946c038c417f1c6c
