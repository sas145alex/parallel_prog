#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#include "iordan_global_var.c"
#include "iordan_helpers.c"
#include "iordan_serial_logic.c"
#include "iordan_parallel_logic.c"

#define SIZE 2000
#define SINGLE_RESULT (1)
#define THREAD (4)

int main(int argc, char const *argv[]) {

  omp_set_dynamic(1);
  omp_set_num_threads(THREAD);

  // Инициализация
  double* ser_matrix;
  double* ser_vector;
  double* par_matrix;
  double* par_vector;
  int size;

  double start_time, end_time, tick;

  if SINGLE_RESULT { // единичный тест
    int t = omp_get_max_threads();
    printf("t = %d\n",t );

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
        double rand_value = rand() % 100;
        ser_matrix[i*size + j] = rand_value;
        par_matrix[i*size + j] = rand_value;
      }
    }

    start_time = omp_get_wtime();
    SerialCalculation(ser_matrix, ser_vector, size);
    end_time = omp_get_wtime();
    printf("%lf\n", end_time - start_time);

    start_time = omp_get_wtime();
    ParallelCalculation(par_matrix, par_vector, size);
    end_time = omp_get_wtime();
    printf("%lf\n", end_time - start_time);
  }
  else { // несколько тестов
    int thread_nums_length = sizeof(THREAD_NUMS)/sizeof(int);
    int sizes_length = sizeof(SIZES)/sizeof(int);

    printf("Нитей Размер Время выполнения\n");
    for (int i = 0; i < thread_nums_length-1; i++) {
      int thread_num = THREAD_NUMS[i];
      omp_set_num_threads(thread_num);
      srand(time(NULL));

      for (int j = 0; j < sizes_length-1; j++) {
        // инициализация
        size = SIZES[j];
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

        // заполнение
        for (size_t i = 0; i < size; i++) {
          double rand_value = rand() % 100;
          ser_vector[i] = rand_value;
          par_vector[i] = rand_value;
          ser_down_pivot_iter[i] = -1;
          ser_up_pivot_iter[i] = -1;
          par_down_pivot_iter[i] = -1;
          par_up_pivot_iter[i] = -1;
          for (size_t j = 0; j < size; j++) {
            double rand_value = rand() % 100;
            ser_matrix[i*size + j] = rand_value;
            par_matrix[i*size + j] = rand_value;
          }
        }

        // вычисления
        start_time = omp_get_wtime();
        ParallelCalculation(par_matrix, par_vector, size);
        end_time = omp_get_wtime();
        double par_time = end_time - start_time;
        printf("%5d %6d %10lf\n", thread_num, size, par_time);
      }
    }
  } // вывод таблицы результатов

  // печать
  // PrintArray(ser_down_pivot_iter, size);
  // PrintArray(par_down_pivot_iter, size);
  // PrintArray(ser_pivot_pos, size);
  // PrintExtendedMatrix(ser_matrix, ser_vector, size);
  // PrintSerialExtendedTriangleMatrix(ser_matrix, par_vector, size);
  // PrintParallelExtendedTriangleMatrix(par_matrix, par_vector, size);
  // PrintTriangleMatrix(ser_matrix, size);

  return 0;
}
