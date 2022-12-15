#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include <check.h>
#include <stdbool.h>
#include <unistd.h>

#include "../s21_matrix.h"

Suite *create_matrix(void);
Suite *remove_matrix(void);
Suite *determinant_matrix(void);

void run_testcase(Suite *testcase);
void run_tests(void);

#endif  // MATRIX_TEST_H