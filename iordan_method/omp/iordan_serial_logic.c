int SerialFindPivotRow (double* matrix, int size, int iter) {
  int pivot_row = -1;
  double max_value = 0;
  for (int i = 0; i < size; i++) {
    if ((ser_down_pivot_iter[i] == -1) && \
    (fabs(matrix[i*size + iter]) > max_value)) {
      pivot_row = i;
      max_value = fabs(matrix[i*size + iter]);
    }
  }
  return pivot_row;
}

void SerialColumnElimination(double* matrix, double* vector, int size,
  int iter, int pivot_row, int* pivot_mask) {

  double pivot_value, pivot_factor;
  pivot_value = matrix[pivot_row*size + iter];
  for (size_t i = 0; i < size; i++) {
    if (pivot_mask[i] == -1) {
      pivot_factor = matrix[i*size + iter] / pivot_value;
      for (size_t j = iter; j < size; j++) {
        matrix[i*size + j] -= pivot_factor * matrix[pivot_row*size + j];
      }
      vector[i] -= pivot_factor * vector[pivot_row];
    }
  }
}

void SerialColumnUpElimination(double* matrix, double* vector, int size,
  int iter, int pivot_row, int* pivot_mask) {

  double pivot_value, pivot_factor;
  pivot_value = matrix[pivot_row*size + iter];
  for (size_t i = 0; i < size; i++) {
    if (pivot_mask[i] == -1) {
      pivot_factor = matrix[i*size + iter] / pivot_value;
      matrix[i*size + iter] = 0.0;
      vector[i] -= pivot_factor * vector[pivot_row];
    }
  }
}

void SerialDownElimination(double* matrix, double* vector, int size, int* pivot_mask) {
  int iter;
  int pivot_row;
  for (size_t iter = 0; iter < size; iter++) {
    pivot_row = SerialFindPivotRow(matrix, size, iter);
    ser_pivot_pos[iter] = pivot_row;
    pivot_mask[pivot_row] = iter;
    SerialColumnElimination(matrix, vector, size, iter, pivot_row, pivot_mask);
  }
}

void SerialUpElimination(double* matrix, double* vector, int size, int* pivot_mask) {
  int iter;
  int pivot_row;
  for (size_t iter = size-1; iter > 0; iter--) {
    pivot_row = ser_pivot_pos[iter];
    pivot_mask[pivot_row] = iter;
    SerialColumnUpElimination(matrix, vector, size, iter, pivot_row, pivot_mask);
  }
}

void RelaxElimination(double* matrix, double* vector, int size, int* mask_pivot) {
  double pivot_value;
  size_t j;
  for (size_t i = 0; i < size; i++) {
    j = mask_pivot[i];
    pivot_value = matrix[i*size + j];
    matrix[i*size + j] = 1.0;
    vector[i] /= pivot_value;
  }
}

void SerialCalculation(double* matrix, double* vector, int size){
  SerialDownElimination(matrix, vector, size, ser_down_pivot_iter);
  SerialUpElimination(matrix, vector, size, ser_up_pivot_iter);
  RelaxElimination(matrix, vector, size, ser_down_pivot_iter);
}
