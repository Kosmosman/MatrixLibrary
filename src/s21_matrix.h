#ifndef SRC_MATRIX_H
#define SRC_MATRIX_H

#define SUCCESS 1
#define FAILURE 0
#define CORRECT_MATRIX 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2
#define CALCULATION_ERROR 2
#define OK 0

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/* ********************* Additional functions ************************ */

int s21_matrices_validation_sizes(matrix_t A, matrix_t B);
int s21_matrix_validation(matrix_t A);
void s21_zero_matrix(matrix_t *A);
void s21_print_matrix(matrix_t A);
double s21_triangle_determinant(matrix_t A, double mul);
int s21_switch_rows(matrix_t *A, int row_1);
void s21_decrease_matrix(matrix_t A, matrix_t *B, int row, int column);
int s21_check_matrices_with_result(matrix_t A, matrix_t B, matrix_t *result,
                                   int row, int column);

#endif  // SRC_MATRIX_H