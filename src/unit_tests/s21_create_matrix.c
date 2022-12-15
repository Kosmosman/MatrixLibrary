#include "../s21_matrix.h"

START_TEST(create_zero_matrix) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(0, 0, &matrix);
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

Suite *create_matrix(void) {
  Suite *s = {0};
  TCase *tc = {0};
  s = suite_create("create_matrix");
  tc = tcase_create("create_matrix");

  tcase_add_test(tc, create_zero_matrix);
  tcase_add_test(tc, create_size_one_matrix);
  tcase_add_test(tc, create_size_ten_matrix);
  tcase_add_test(tc, create_non_square_matrix);

  suite_add_tcase(s, tc);
  return s;
}