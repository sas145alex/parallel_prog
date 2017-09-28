int ParallelFindPivotRow (double* matrix, int size, int iter) {
  int pivot_row = -1;
  double max_value = 0;

  #pragma omp parallel
  {
    TThreadPivotRow ThreadPivotRow;
    ThreadPivotRow.max_value = 0;
    ThreadPivotRow.pivot_row = -1;
    #pragma omp for
    for (int i = 0; i < size; i++) {
      if ((par_down_pivot_iter[i] == -1) && \
      (fabs(matrix[i*size + iter]) > ThreadPivotRow.max_value)) {
        ThreadPivotRow.pivot_row = i;
        ThreadPivotRow.max_value = fabs(matrix[i*size + iter]);
      }
    }
    #pragma omp critical
    {
      if (ThreadPivotRow.max_value > max_value) {
        max_value = ThreadPivotRow.max_value;
        pivot_row = ThreadPivotRow.pivot_row;
      }
    } // critical
  } // parallel
  return pivot_row;
}

void ParallelColumnDownElimination(double* matrix, double* vector, int size,
  int iter, int pivot_row, int* pivot_mask) {

  double pivot_value, pivot_factor;
  pivot_value = matrix[pivot_row*size + iter];
  #pragma omp parallel for private(pivot_factor) schedule(dynamic, 1)
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

void ParallelColumnUpElimination(double* matrix, double* vector, int size,
  int iter, int pivot_row, int* pivot_mask) {

  double pivot_value, pivot_factor;
  pivot_value = matrix[pivot_row*size + iter];
  #pragma omp parallel for schedule(dynamic, 1)
  for (size_t i = 0; i < size; i++) {
    if (pivot_mask[i] == -1) {
      pivot_factor = matrix[i*size + iter] / pivot_value;
      matrix[i*size + iter] = 0.0;
      vector[i] -= pivot_factor * vector[pivot_row];
    }
  }
}

void ParallelDownElimination(double* matrix, double* vector, int size, int* pivot_mask) {
  int iter;
  int pivot_row;
  for (size_t iter = 0; iter < size; iter++) {
    pivot_row = ParallelFindPivotRow(matrix, size, iter);
    par_pivot_pos[iter] = pivot_row;
    pivot_mask[pivot_row] = iter;
    ParallelColumnDownElimination(matrix, vector, size, iter, pivot_row, pivot_mask);
  }
}

void ParallelUpElimination(double* matrix, double* vector, int size, int* pivot_mask) {
  int iter;
  int pivot_row;
  for (size_t iter = size-1; iter > 0; iter--) {
    pivot_row = par_pivot_pos[iter];
    pivot_mask[pivot_row] = iter;
    ParallelColumnUpElimination(matrix, vector, size, iter, pivot_row, pivot_mask);
  }
}

void ParallelRelaxElimination(double* matrix, double* vector, int size, int* mask_pivot) {
  double pivot_value;
  size_t j;
  #pragma parallel for
  for (size_t i = 0; i < size; i++) {
    j = mask_pivot[i];
    pivot_value = matrix[i*size + j];
    matrix[i*size + j] = 1.0;
    vector[i] /= pivot_value;
  }
}

void ParallelCalculation(double* matrix, double* vector, int size){
  ParallelDownElimination(matrix, vector, size, par_down_pivot_iter);
  ParallelUpElimination(matrix, vector, size, par_up_pivot_iter);
  ParallelRelaxElimination(matrix, vector, size, par_down_pivot_iter);
}
