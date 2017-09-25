int FindPivotRow (double* matrix, int size, int iter) {
  int pivot_row = -1;
  double max_value = 0;
  for (int i = 0; i < size; i++) {
    if ((ser_pivot_iter[i] == -1) && \
    (fabs(matrix[i*size + iter]) > max_value)) {
      pivot_row = i;
      max_value = fabs(matrix[i*size + iter]);
      // printf("Выбрана строка [%d:%d] = %f\n", iter, pivot_row, max_value);
    }
  }
  return pivot_row;
}

void SerialColumnElimination(double* matrix, double* vector, int size,
  int iter, int pivot_row) {

  double pivot_value, pivot_factor;
  pivot_value = matrix[pivot_row*size + iter];
  for (size_t i = 0; i < size; i++) {
    if (ser_pivot_iter[i] == -1) {
      pivot_factor = matrix[i*size + iter] / pivot_value;
      for (size_t j = iter; j < size; j++) {
        matrix[i*size + j] -= pivot_factor * matrix[pivot_row*size + j];
      }
      vector[i] -= pivot_factor * vector[pivot_row];
    }
  }
}

void SerialGaussianElimination(double* matrix, double* vector, int size) {
  int iter;
  int pivot_row;
  for (size_t iter = 0; iter < size; iter++) {
    pivot_row = FindPivotRow(matrix, size, iter);
    ser_pivot_pos[iter] = pivot_row;
    ser_pivot_iter[pivot_row] = iter;

    // printf("Итерация(%lu): pivot_row(%d) с [%f]\n", iter, pivot_row, matrix[pivot_row*size + iter]);
    // printf("До вычитания\n");
    // PrintMatrix(matrix, size);
    SerialColumnElimination(matrix, vector, size, iter, pivot_row);
    // printf("После вычитания\n");
    // PrintMatrix(matrix, size);
  }
  // printf("Последний вид\n");
  // PrintMatrix(matrix, size);
}

void SerialCalculation(double* matrix, double* vector, int size){
  SerialGaussianElimination(matrix, vector, size);
}
