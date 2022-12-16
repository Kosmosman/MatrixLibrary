#include "s21_test_matrix.h"

START_TEST(remove_null_matrix) {
  matrix_t A = {NULL, 0, 0};
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(0, A.columns);
  ck_assert_int_eq(0, A.rows);
}
END_TEST

START_TEST(remove_non_zero_matrix) {
  matrix_t A = {NULL, 0, 0};
  s21_create_matrix(3, 3, &A);
  _ck_assert_ptr_null(A.matrix, !=);
  ck_assert_int_eq(3, A.columns);
  ck_assert_int_eq(3, A.rows);

  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(0, A.columns);
  ck_assert_int_eq(0, A.rows);
}
END_TEST

Suite *remove_matrix(void) {
  Suite *s = {0};
  TCase *tc = {0};
  s = suite_create("remove_matrix");
  tc = tcase_create("remove_matrix");

  tcase_add_test(tc, remove_null_matrix);
  tcase_add_test(tc, remove_non_zero_matrix);

  suite_add_tcase(s, tc);
  return s;
}