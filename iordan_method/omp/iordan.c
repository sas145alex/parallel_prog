#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#include "iordan_global_var.c"
#include "iordan_helpers.c"
#include "iordan_serial_logic.c"
#include "iordan_parallel_logic.c"

#define SIZE 5
#define SINGLE_RESULT (1)
#define THREAD (16)

int main(int argc, char const *argv[]) {

  omp_set_nested(1);
  omp_set_dynamic(1);


  // Инициализация
  double* ser_matrix;
  double* ser_vector;
  double* par_matrix;
  double* par_vector;
  int size;

  double start_time, end_time, tick;

  if SINGLE_RESULT { // единичный тест
    size = SIZE;
    ser_pivot_pos = (int*) malloc(size * sizeof(int));
    ser_down_pivot_iter = (int*) malloc(size * sizeof(int));
    ser_up_pivot_iter = (int*) malloc(size * sizeof(int));
    par_pivot_pos = (int*) malloc(size * sizeof(int));
    par_down_pivot_iter = (int*) malloc(size * sizeof(int));
    par_up_pivot_iter = (int*) malloc(size * sizeof(int));
    ser_vector = (double*) malloc(size * sizeof(double));
    ser_matrix = (double*) malloc(size * size * sizeof(double*));
    par_vector = (double*) malloc(size * sizeof(double));
    par_matrix = (double*) malloc(size * size * sizeof(double*));


    omp_set_num_threads(THREAD);
    int t = omp_get_max_threads();
    printf("max threads = %d\n", t);

    srand(time(NULL));
    for (size_t i = 0; i < size; i++) {
      double rand_value = rand() % 100;
      ser_vector[i] = rand_value;
      par_vector[i] = rand_value;
      ser_down_pivot_iter[i] = -1;
      ser_up_pivot_iter[i] = -1;
      par_down_pivot_iter[i] = -1;
      par_up_pivot_iter[i] = -1;
      for (size_t j = 0; j < size; j++) {
        double rand_value = (rand() % 100) + 1;
        ser_matrix[i*size + j] = rand_value;
        par_matrix[i*size + j] = rand_value;
      }
    }

    printf("матраца ser до вычислений\n");
    PrintExtendedMatrix(ser_matrix, ser_vector, size);
    printf("матраца par до вычислений\n");
    PrintExtendedMatrix(par_matrix, par_vector, size);

    start_time = omp_get_wtime();
    SerialCalculation(ser_matrix, ser_vector, size);
    end_time = omp_get_wtime();
    printf("Последовательное %lf\n", end_time - start_time);

    start_time = omp_get_wtime();
    ParallelCalculation(par_matrix, par_vector, size);
    end_time = omp_get_wtime();
    printf("Парралельное %lf\n", end_time - start_time);

    printf("матраца ser после вычислений\n");
    PrintExtendedMatrix(ser_matrix, ser_vector, size);
    printf("матраца par после вычислений\n");
    PrintParallelExtendedTriangleMatrix(par_matrix, par_vector, size);
  }
  else { // несколько тестов
    int thread_nums_length = sizeof(THREAD_NUMS)/sizeof(int);
    int sizes_length = sizeof(SIZES)/sizeof(int);

    printf("Размер | Нитей | Время выполнения\n");
    for (int i = 0; i < sizes_length; i++) {
      size = SIZES[i];
      ser_pivot_pos = (int*) malloc(size * sizeof(int));
      ser_down_pivot_iter = (int*) malloc(size * sizeof(int));
      ser_up_pivot_iter = (int*) malloc(size * sizeof(int));
      par_pivot_pos = (int*) malloc(size * sizeof(int));
      par_down_pivot_iter = (int*) malloc(size * sizeof(int));
      par_up_pivot_iter = (int*) malloc(size * sizeof(int));
      ser_vector = (double*) malloc(size * sizeof(double));
      ser_matrix = (double*) malloc(size * size * sizeof(double*));
      par_vector = (double*) malloc(size * sizeof(double));
      par_matrix = (double*) malloc(size * size * sizeof(double*));

      for ( int char_num = 0; char_num < 27; char_num++) {
        printf("-");
      }
      printf("\n");


      for (int j = 0; j < thread_nums_length; j++) {
        int thread_num = THREAD_NUMS[j];
        omp_set_num_threads(thread_num);
        srand(time(NULL));
        // инициализация

        // заполнение
        for (size_t k = 0; k < size; k++) {
          double rand_value = rand() % 100;
          ser_vector[k] = rand_value;
          par_vector[k] = rand_value;
          ser_down_pivot_iter[k] = -1;
          ser_up_pivot_iter[k] = -1;
          par_down_pivot_iter[k] = -1;
          par_up_pivot_iter[k] = -1;
          for (size_t t = 0; t < size; t++) {
            double rand_value = rand() % 100;
            ser_matrix[k*size + t] = rand_value;
            par_matrix[k*size + t] = rand_value;
          }
        }

        // вычисления
        start_time = omp_get_wtime();
        ParallelCalculation(par_matrix, par_vector, size);
        end_time = omp_get_wtime();
        double par_time = end_time - start_time;

        printf("%7d|%7d|%11lf\n", size, thread_num, par_time);
      }
    }
  } // вывод таблицы результатов

  return 0;
}
