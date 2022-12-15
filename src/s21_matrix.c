#include "s21_matrix.h"

/// @brief Создание матрицы
/// @param rows Строки
/// @param columns Стобцы
/// @param result Структура матрицы
/// @return
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int output = CORRECT_MATRIX;
  if (rows && columns) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < columns && !output; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          output = INCORRECT_MATRIX;
        }
      }
    } else {
      output = INCORRECT_MATRIX;
    }
  } else {
    output = INCORRECT_MATRIX;
  }
  return output;
}
/// @brief Очистка матрицы
/// @param A Указатель на структуру матрицы
void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
}

/// @brief Сравнение двух матриц
/// @param A
/// @param B
/// @return
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A->columns != B->columns || A->rows != B->rows) {
    result = FAILURE;
  } else if (!(A->columns) || !(A->rows)) {
    result = FAILURE;
  } else {
    for (int i = 0; i < A->rows && result; i++) {
      for (int j = 0; j < A->columns && result; j++) {
        if (round(A->matrix[i][j] * pow(10, 7)) !=
            round(B->matrix[i][j] * pow(10, 7)))
          result = FAILURE;
      }
    }
  }
  return result;
}

/// @brief Сумма двух матриц
/// @param A
/// @param B
/// @param result
/// @return
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = CORRECT_MATRIX;
  res = s21_matrices_validation_sizes(*A, *B);
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return res;
}

/// @brief Разница двух матриц
/// @param A
/// @param B
/// @param result
/// @return
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = CORRECT_MATRIX;
  res = s21_matrices_validation_sizes(*A, *B);
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res;
}

/// @brief Произведение матрицы на число
/// @param A
/// @param number
/// @param result
/// @return
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = CORRECT_MATRIX;
  res = s21_matrix_validation(*A);
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

/// @brief Умножение матриц
/// @param A
/// @param B
/// @param result
/// @return
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = CORRECT_MATRIX;
  res = !(A->columns == B->rows);
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

/// @brief Транспонирование матрицы
/// @param A
/// @param result
/// @return
int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = CORRECT_MATRIX;
  if (A->rows == result->columns && A->columns == result->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = result->matrix[j][i];
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = CORRECT_MATRIX, mul = 1, sign = 1, state = 0, flag = 0, num = 0,
      zero = 0;
  res = s21_matrix_validation(*A);
  *result = 0;
  if (!res) {
    for (int i = 0; i < A->rows && !zero; i++) {
      if (num = s21_switch_rows(A, i)) {
        if (num == 2) mul *= -1;
        for (int j = i; j < A->rows - 1; j++) {
          // Находим первое вхождение строки с ненулевым i-м элементом
          if (!state && A->matrix[j][i]) {
            state = j;
            flag = 1;
          }
          if (flag) {
            if ((A->matrix[state][i] > 0 && A->matrix[j + 1][i] > 0) ||
                (A->matrix[state][i] < 0 && A->matrix[j + 1][i] < 0))
              sign = -1;
            printf("mul = %d\n", mul);
            if (A->matrix[j + 1][i] != 0) {
              mul *= A->matrix[state][i];
              num = A->matrix[j + 1][i];
              for (int k = i; k < A->columns; k++) {
                A->matrix[j + 1][k] =
                    A->matrix[j + 1][k] * A->matrix[state][i] +
                    A->matrix[state][k] * sign * num;
                s21_print_matrix(*A);
              }
            }
          }
          sign = 1;
        }
        flag = 0;
        state = 0;
      } else {
        zero = 1;
      }
    }
  }
  if (!zero) *result = s21_triangle_determinant(*A, mul);
  return res;
}

/* -------------------- ADDITIONAL FUNCTIONS ------------------------- */

/// @brief Определение эквивалентности размеров двух матриц
/// @param A
/// @param B
/// @return
int s21_matrices_validation_sizes(matrix_t A, matrix_t B) {
  int res = s21_matrix_validation(A);
  if (A.columns != B.columns || A.rows != B.rows) res = CALCULATION_ERROR;
  return res;
}

/// @brief Определение, не является ли одна из сторон матрицы нулевого размера
/// @param A
/// @param B
/// @return
int s21_matrix_validation(matrix_t A) {
  int res = CORRECT_MATRIX;
  if (!A.columns || !A.rows) res = INCORRECT_MATRIX;
  return res;
}

/// @brief Зануление элементов матрицы
/// @param A
void s21_zero_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = 0;
    }
  }
}

/// @brief Проверяет строку на наличие в ней 0 в i-м столбце.
/// В положительном случае, находит первую строку с ненулевым элементом. При
/// ненахождении таковой, возвращает 0.
/// @param A
/// @param row_1
/// @return res = 1 - первый проверяемый элемент ненулевой. res = 2 - строки
/// поменяли местами, необходимо домножить mul на -1.
int s21_switch_rows(matrix_t *A, int row_1) {
  int tmp = 0, res = 0, row_2 = 0;
  if (A->matrix[row_1][row_1] == 0) {
    for (int count = row_1 + 1; !res && count < A->rows; count++) {
      if (A->matrix[count][row_1] != 0) {
        row_2 = count;
        res = 2;
      }
    }
    if (res) {
      for (int i = 0; i < A->columns; i++) {
        tmp = A->matrix[row_1][i];
        A->matrix[row_1][i] = A->matrix[row_2][i];
        A->matrix[row_2][i] = tmp;
      }
    }
  } else {
    res = 1;
  }
  return res;
}

double s21_triangle_determinant(matrix_t A, int mul) {
  double res = 1;
  for (int i = 0; i < A.rows; i++) {
    res *= A.matrix[i][i];
  }
  printf("mul = %d\n", mul);
  return res / mul;
}

int main(void) {
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
  s21_print_matrix(A);
  printf("\n");
  double res = 0;
  s21_determinant(&A, &res);
  printf("\n");
  printf("%lf\n", res);
  s21_remove_matrix(&A);
  return 0;
}

void s21_print_matrix(matrix_t A) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      printf("%lf ", A.matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}