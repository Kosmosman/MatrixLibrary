#include "s21_matrix.h"

/// @brief Создание матрицы
/// @param rows Строки
/// @param columns Стобцы
/// @param result Структура матрицы
/// @return Возвращает 0 в случае успешного создания. 1 - в случае ошибки при
/// создании
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int output = CORRECT_MATRIX;
  s21_zero_matrix(result);
  if (rows && columns) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = NULL;
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
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    s21_zero_matrix(A);
  }
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

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = CORRECT_MATRIX, res1 = CORRECT_MATRIX;
  double minor = 0;
  matrix_t tmp = {0};
  res = s21_matrices_validation_sizes(*A, *result);
  res1 = s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
  if (!res && !res1) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_decrease_matrix(*A, &tmp, i, j);
        res = s21_determinant(&tmp, &minor);
        if ((i + j) % 2) minor = -minor;
        result->matrix[i][j] = minor;
        s21_print_matrix(*result);
        minor = 0;
      }
    }
    s21_zero_matrix(&tmp);
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = CORRECT_MATRIX, state = 0, flag = 0, num = 0, zero = 0;
  double num_const = 0, mul = 1;
  res = s21_matrix_validation(*A);
  *result = 0;
  if (!res) {
    if (A->columns > 1) {
      for (int i = 0; i < A->rows && !zero; i++) {
        if ((num = s21_switch_rows(A, i))) {
          if (num == 2) mul *= -1;
          for (int j = i; j < A->rows - 1; j++) {
            if (!state && A->matrix[j][i]) {
              state = j;
              flag = 1;
            }
            if (flag && A->matrix[j + 1][i] != 0) {
              mul *= A->matrix[state][i];
              num_const = A->matrix[j + 1][i];
              for (int k = i; k < A->columns; k++) {
                A->matrix[j + 1][k] =
                    A->matrix[j + 1][k] * A->matrix[state][i] -
                    A->matrix[state][k] * num_const;
              }
            }
          }
          flag = 0;
          state = 0;
        } else {
          zero = 1;
        }
      }
    } else {
      *result = A->matrix[0][0];
    }
  }
  if (!zero) *result = s21_triangle_determinant(*A, mul);
  return res;
}

/* -------------------- ADDITIONAL FUNCTIONS ------------------------- */

/// @brief Зануление всех элементов матрицы (необходимо для обработки ситуаций,
/// когда передаются неинициализированные структуры матриц)
/// @param A
void s21_zero_matrix(matrix_t *A) {
  A->matrix = NULL;
  A->columns = 0;
  A->rows = 0;
}

/// @brief Определение эквивалентности размеров двух матриц и их корректности
/// @param A
/// @param B
/// @return
int s21_matrices_validation_sizes(matrix_t A, matrix_t B) {
  int res = CORRECT_MATRIX;
  if (A.columns != B.columns || A.rows != B.rows) res = CALCULATION_ERROR;
  return res;
}

/// @brief Проверка матрицы накорректность (стороны не равны 0 и матрица не
/// указывает на NULL)
/// @param A
/// @param B
/// @return
int s21_matrix_validation(matrix_t A) {
  int res = CORRECT_MATRIX;
  if (!A.columns || !A.rows || A.matrix == NULL) res = INCORRECT_MATRIX;
  return res;
}

/// @brief Зануление элементов матрицы
/// @param A
void s21_fill_zero_matrix(matrix_t *A) {
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

/// @brief Нахождение детерминанта путем перемножения членов треугольной
/// матрицы, находящихся на главной диагонали
/// @param A
/// @param mul
/// @return
double s21_triangle_determinant(matrix_t A, double mul) {
  double res = 1;
  for (int i = 0; i < A.rows; i++) {
    res *= A.matrix[i][i];
  }
  return res / mul;
}

/// @brief Заполнение матрицы с вычеркнутыми строкой и столбцом
/// @param A
/// @param row
/// @param column
/// @return Возвращает матрицу
void s21_decrease_matrix(matrix_t A, matrix_t *B, int row, int column) {
  int i_result = 0, j_result = 0;
  for (int i = 0; i < A.rows; i++)
    if (i != row) {
      for (int j = 0; j < A.columns; j++) {
        if (j != column) {
          B->matrix[i_result][j_result++] = A.matrix[i][j];
        }
      }
      j_result = 0;
      i_result++;
    }
}

int main(void) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  s21_print_matrix(A);
  printf("\n");
  matrix_t B = {0};
  s21_create_matrix(3, 3, &B);
  s21_calc_complements(&A, &B);
  printf("\n");
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
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