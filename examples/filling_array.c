#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define THREAD_NUM 4

int show_matrix(int** matrix, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++ ){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}


int main(int argc, char const *argv[]) {
  omp_set_num_threads(THREAD_NUM);


  double begin, end, time_spent;
  srand(time(NULL));
  int size = 20000;
  // int thr = 4;
  // int *result, *result_omp;
  int **matrix = (int**) malloc(size * sizeof(int*));
  // int *vector = (int*) malloc(size * sizeof(int));
  for (int i=0; i<size; i++){
      // vector[i] = -1;
      // vector[i] = rand() % 100;
      matrix[i] = (int*) malloc(size * sizeof(int));
      for (int j=0; j<size; j++){
          matrix[i][j] = -1;
      }
  }


  // show_vector(vector, size);
  // printf("Перед парралельной областью\n");
  // show_matrix(matrix, size, size);
  begin = omp_get_wtime();
  #pragma omp parallel
  {
  #pragma omp for
      for (int i=0; i<size; i++){
        for (int j = 0; j < size; j++) {
          matrix[i][j] = omp_get_thread_num();
        }
      }
  }


  end = omp_get_wtime();
  time_spent = end - begin;
  printf("Parallel: %lf\n", time_spent);


  begin = omp_get_wtime();
  for (int i=0; i<size; i++){
    for (int j = 0; j < size; j++) {
      matrix[i][j] = omp_get_thread_num();
    }
  }
  end = omp_get_wtime();
  time_spent = end - begin;
  printf("Послед: %lf\n", time_spent);

  // printf("После парралельной области\n");
  // show_matrix(matrix, size, size);

  return 0;
}
