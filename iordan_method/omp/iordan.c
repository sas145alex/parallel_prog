#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "iordan_global_var.c"
#include "iordan_helpers.c"
#include "iordan_logic.c"

#define SIZE 7

int main(int argc, char const *argv[]) {
  // Инициализация
  double* matrix;
  double* vector;
  double* result;
  int size;

  size = SIZE;
  ser_pivot_pos = (int*) malloc(size * sizeof(int));
  ser_down_pivot_iter = (int*) malloc(size * sizeof(int));
  ser_up_pivot_iter = (int*) malloc(size * sizeof(int));
  vector = (double*) malloc(size * sizeof(double));
  result = (double*) malloc(size * sizeof(double));
  matrix = (double*) malloc(size * size * sizeof(double*));

  srand(time(NULL));
  for (size_t i = 0; i < size; i++) {
    vector[i] = rand() % 100;
    ser_down_pivot_iter[i] = -1;
    ser_up_pivot_iter[i] = -1;
    for (size_t j = 0; j < size; j++) {
      matrix[i*size + j] = rand() % 100;
    }
  }

  // Печать
  // PrintVector(vector, size);
  // PrintArray(pivot_iter, size);
  // PrintMatrix(matrix, size);
  // PrintExtendedMatrix(matrix, vector, size);

  // Вызов алгоритма Иордана
  SerialCalculation(matrix, vector, size);
  // PrintArray(ser_down_pivot_iter, size);
  // PrintArray(ser_pivot_pos, size);
  // PrintExtendedMatrix(matrix, vector, size);
  // PrintExtendedTriangleMatrix(matrix, vector, size);
  // PrintTriangleMatrix(matrix, size);

  return 0;
}
