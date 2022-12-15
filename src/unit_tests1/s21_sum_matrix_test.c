#include "s21_matrix_test.h"

START_TEST(zero_matrix) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result;
  int res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(3, res);
  ck_assert_double_eq(result.columns, 0);
  ck_assert_double_eq(result.rows, 0);
  ck_assert_ptr_eq(result.matrix, NULL);
}

START_TEST(casual_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result;
  matrix_t orig = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &result);
  A.matrix[0][0] = B.matrix[0][0] = 1;
  A.matrix[0][1] = B.matrix[0][0] = 2;
  A.matrix[0][2] = B.matrix[0][0] = 3;
  A.matrix[1][0] = B.matrix[0][0] = 4;
  A.matrix[1][1] = B.matrix[0][0] = 5;
  A.matrix[1][2] = B.matrix[0][0] = 6;
  A.matrix[2][0] = B.matrix[0][0] = 7;
  A.matrix[2][1] = B.matrix[0][0] = 8;
  A.matrix[2][2] = B.matrix[0][0] = 9;
  result.matrix[0][0] = 2;
  result.matrix[0][1] = 4;
  result.matrix[0][2] = 6;
  result.matrix[1][0] = 8;
  result.matrix[1][1] = 10;
  result.matrix[1][2] = 12;
  result.matrix[2][0] = 14;
  result.matrix[2][1] = 16;
  result.matrix[2][2] = 18;
  int res = s21_sum_matrix(&A, &B, &result);
  int eq = s21_eq_matrix(&result, &orig);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, eq);
}

Suite *sum_matrix(void) {
  Suite *s = {0};
  TCase *tc = {0};
  s = suite_create("sum_matrix");
  tc = tcase_create("sum_matrix");

  tcase_add_test(tc, zero_matrix);
  tcase_add_test(tc, casual_matrix_1);

  suite_add_tcase(s, tc);
  return s;
}