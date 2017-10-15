void PrintVector(double* vector, int size) {
  for (int i = 0; i < size; i++) {
    printf("%f ", vector[i]);
  }
  printf("\n");

  return;
}

void PrintArray(int* array, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  return;
}

void PrintMatrix(double* matrix, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%11f ", matrix[i*size + j]);
    }
    printf("\n");
  }
  printf("\n");
}

void PrintSerialTriangleMatrix(double* matrix, int size) {
  for (int i = 0; i < size; i++) {
    int row = ser_pivot_pos[i];
    for (int j = 0; j < size; j++) {
      printf("%11f ", matrix[row*size + j]);
    }
    printf("\n");
  }
}

void PrintExtendedMatrix(double* matrix, double* vector, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%11f ", matrix[i*size + j]);
    }
    printf(" | %11f\n", vector[i]);
  }
  printf("\n");
}

void PrintSerialExtendedTriangleMatrix(double* matrix, double* vector, int size) {
  for (int i = 0; i < size; i++) {
    int row = ser_pivot_pos[i];
    for (int j = 0; j < size; j++) {
      printf("%11f ", matrix[row*size + j]);
    }
    printf(" | %11f\n", vector[row]);
  }
  printf("\n");
}

void PrintParallelExtendedTriangleMatrix(double* matrix, double* vector, int size) {
  for (int i = 0; i < size; i++) {
    int row = par_pivot_pos[i];
    for (int j = 0; j < size; j++) {
      printf("%11f ", matrix[row*size + j]);
    }
    printf(" | %11f\n", vector[row]);
  }
  printf("\n");
}

void PrintParallelTriangleMatrix(double* matrix, int size) {
  for (int i = 0; i < size; i++) {
    int row = par_pivot_pos[i];
    for (int j = 0; j < size; j++) {
      printf("%11f ", matrix[row*size + j]);
    }
    printf("\n");
  }
}
