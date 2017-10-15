#include <stdio.h>
int main(int argc, char *argv[])
{
  int count = 0;
  #pragma omp parallel reduction (+: count)
  // #pragma omp parallel reduction (+: count) num_threads(8)
  {
    // count2++;
    count++;
    printf("Текущее значение count: %d\n", count);
    // printf("Текущее значение count2: %d\n", count2);
  }
  printf("Число нитей: %d\n", count);
  // printf("Число нитей count2: %d\n", count2);
}
