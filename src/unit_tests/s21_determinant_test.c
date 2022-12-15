#include "s21_matrix_test.h"

START_TEST(zero_matrix) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 0;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq(0, res);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(casual_matrix) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq(0, res);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(casual_matrix_1) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq(0, res);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(casual_matrix_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 6;
  A.matrix[1][0] = 8;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 9;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 1;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq(-4.0, res);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(casual_matrix_negative_3) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = -8;
  A.matrix[0][1] = -12;
  A.matrix[0][2] = -5;
  A.matrix[1][0] = -22;
  A.matrix[1][1] = -6;
  A.matrix[1][2] = -9;
  A.matrix[2][0] = -11;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -2;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq(-502.0, res);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(casual_matrix_4) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.44;
  A.matrix[0][2] = 6.1;
  A.matrix[1][0] = -2.9;
  A.matrix[1][1] = 11.3;
  A.matrix[1][2] = 12.2;
  A.matrix[2][0] = 4.0;
  A.matrix[2][1] = -9.1;
  A.matrix[2][2] = 12.12;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq(462.05612, res);
  ck_assert_int_eq(0, error);
}
END_TEST

Suite *determinant_matrix(void) {
  Suite *s = {0};
  TCase *tc = {0};
  s = suite_create("suite_matrix");
  tc = tcase_create("create_matrix");

  tcase_add_test(tc, zero_matrix);
  tcase_add_test(tc, casual_matrix);
  tcase_add_test(tc, casual_matrix_1);
  tcase_add_test(tc, casual_matrix_2);
  tcase_add_test(tc, casual_matrix_negative_3);
  tcase_add_test(tc, casual_matrix_4);

  suite_add_tcase(s, tc);
  return s;
}