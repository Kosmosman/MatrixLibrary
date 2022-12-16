#include "s21_test_matrix.h"

START_TEST(create_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  int res = s21_create_matrix(rows, cols, &m);
  if (!res) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        m.matrix[i][j] = 0;
        ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-07);
      }
    }
    ck_assert_int_eq(m.rows, rows);
    ck_assert_int_eq(m.columns, cols);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(create_2) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_3) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_4) {
  const int rows = 1;
  const int cols = 1;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), OK);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_zero_matrix) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(0, 0, &matrix);
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(create_zero_matrix_1) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(2, 0, &matrix);
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(create_zero_matrix_2) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(0, 2, &matrix);
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(create_size_one_matrix) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(1, 1, &matrix);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, matrix.columns);
  ck_assert_int_eq(1, matrix.rows);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_size_ten_matrix) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(10, 10, &matrix);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(10, matrix.columns);
  ck_assert_int_eq(10, matrix.rows);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_non_square_matrix) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(5, 3, &matrix);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(3, matrix.columns);
  ck_assert_int_eq(5, matrix.rows);
  s21_remove_matrix(&matrix);
}
END_TEST

Suite* suite_create_matrix(void) {
  Suite* s = suite_create("suite_create_matrix");
  TCase* tc = tcase_create("case_create_matrix");

  tcase_add_test(tc, create_1);
  tcase_add_test(tc, create_2);
  tcase_add_test(tc, create_3);
  tcase_add_test(tc, create_4);

  tcase_add_test(tc, create_zero_matrix);
  tcase_add_test(tc, create_zero_matrix_1);
  tcase_add_test(tc, create_zero_matrix_2);
  tcase_add_test(tc, create_size_one_matrix);
  tcase_add_test(tc, create_size_ten_matrix);
  tcase_add_test(tc, create_non_square_matrix);

  suite_add_tcase(s, tc);
  return s;
}