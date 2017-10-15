#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
  printf("Значение OMP_DYNAMIC: %d\n", omp_get_dynamic());
  omp_set_dynamic(1);
  printf("Значение OMP_DYNAMIC: %d\n", omp_get_dynamic());
  printf("Параллельная область, %d максимум нитей\n",
    omp_get_max_threads());
  #pragma omp parallel num_threads(128)
  {

    #pragma omp master
    {
      printf("Параллельная область, %d нитей\n",
        omp_get_num_threads());


    }
  }
}
