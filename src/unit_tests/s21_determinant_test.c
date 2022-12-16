#include "s21_test_matrix.h"

START_TEST(determinant1) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant2) {
  const int size = 4;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j + i;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant3) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][1] = 6;
  m.matrix[0][2] = -2;
  m.matrix[0][3] = -1;
  m.matrix[0][4] = 5;
  m.matrix[1][3] = -9;
  m.matrix[1][4] = -7;
  m.matrix[2][1] = 15;
  m.matrix[2][2] = 35;
  m.matrix[3][1] = -1;
  m.matrix[3][2] = -11;
  m.matrix[3][3] = -2;
  m.matrix[3][4] = 1;
  m.matrix[4][0] = -2;
  m.matrix[4][1] = -2;
  m.matrix[4][2] = 3;
  m.matrix[4][4] = -2;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 2480, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant4) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 3;
  m.matrix[0][2] = 1;
  m.matrix[1][0] = 7;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 1;
  m.matrix[2][0] = 9;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = 1;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -32, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant5) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;
  m.matrix[0][1] = -4;
  m.matrix[1][0] = -2;
  m.matrix[1][1] = -3;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 7, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant6) {
  const int size = 1;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -5, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant7) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  rows = -rows;
  s21_create_matrix(rows, rows, &m);
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant8) {
  matrix_t m = {0};
  int rows = 4;
  int cols = 5;
  s21_create_matrix(rows, cols, &m);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

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
  s21_remove_matrix(&A);
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
  s21_remove_matrix(&A);
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
  s21_remove_matrix(&A);
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
  s21_remove_matrix(&A);
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
  s21_remove_matrix(&A);
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
  s21_remove_matrix(&A);
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
  s21_remove_matrix(&A);
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
  s21_remove_matrix(&A);
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
  s21_remove_matrix(&A);
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
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_determinant(void) {
  Suite *s = suite_create("suite_determinant");
  TCase *tc = tcase_create("case_determinant");

  tcase_add_test(tc, determinant1);
  tcase_add_test(tc, determinant2);
  tcase_add_test(tc, determinant3);
  tcase_add_test(tc, determinant4);
  tcase_add_test(tc, determinant5);
  tcase_add_test(tc, determinant6);
  tcase_add_loop_test(tc, determinant7, 0, 100);
  tcase_add_test(tc, determinant8);
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
