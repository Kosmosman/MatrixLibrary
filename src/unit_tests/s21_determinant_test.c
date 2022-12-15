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
  ck_assert_double_eq_tol(0, res, 1e-7);
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
  ck_assert_double_eq_tol(0, res, 1e-7);
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
  ck_assert_double_eq_tol(0, res, 1e-7);
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
  ck_assert_double_eq_tol(-4.0, res, 1e-7);
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
  ck_assert_double_eq_tol(-502.0, res, 1e-7);
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
  ck_assert_double_eq_tol(462.05612, res, 1e-7);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(casual_matrix_5) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 1.2;
  A.matrix[0][2] = 1.3;
  A.matrix[1][0] = 1.4;
  A.matrix[1][1] = 1.1;
  A.matrix[1][2] = 1.2;
  A.matrix[2][0] = 1.3;
  A.matrix[2][1] = 1.8;
  A.matrix[2][2] = 1.0;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq_tol(0.019, res, 1e-7);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(casual_matrix_6) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2.45;
  A.matrix[0][1] = 5.11;
  A.matrix[1][0] = 3.1;
  A.matrix[1][1] = 9.99;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq_tol(8.6345, res, 1e-7);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(casual_matrix_7) {
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 21.425;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq_tol(21.425, res, 1e-7);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(casual_matrix_8) {
  matrix_t A = {0};
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 21.42;
  A.matrix[0][1] = 11.2;
  A.matrix[0][2] = 13.8;
  A.matrix[0][3] = 123.12;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 12.22;
  A.matrix[1][2] = 44.12;
  A.matrix[1][3] = 17.1;
  A.matrix[2][0] = -11.12;
  A.matrix[2][1] = 3.02;
  A.matrix[2][2] = 66.7;
  A.matrix[2][3] = 15.16;
  A.matrix[3][0] = -2.26;
  A.matrix[3][1] = -0.007;
  A.matrix[3][2] = 13.87;
  A.matrix[3][3] = 1.34;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq_tol(-54206.8204245137, res, 1e-7);
  ck_assert_int_eq(0, error);
}
END_TEST

Suite *determinant_matrix(void) {
  Suite *s = {0};
  TCase *tc = {0};
  s = suite_create("determinant_matrix");
  tc = tcase_create("determinant_matrix");

  tcase_add_test(tc, zero_matrix);
  tcase_add_test(tc, casual_matrix);
  tcase_add_test(tc, casual_matrix_1);
  tcase_add_test(tc, casual_matrix_2);
  tcase_add_test(tc, casual_matrix_negative_3);
  tcase_add_test(tc, casual_matrix_4);
  tcase_add_test(tc, casual_matrix_5);
  tcase_add_test(tc, casual_matrix_6);
  tcase_add_test(tc, casual_matrix_7);
  tcase_add_test(tc, casual_matrix_8);

  suite_add_tcase(s, tc);
  return s;
}