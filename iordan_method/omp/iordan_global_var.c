typedef struct {
  int pivot_row;
  double max_value;
} TThreadPivotRow;

int* ser_pivot_pos;
int* ser_down_pivot_iter;
int* ser_up_pivot_iter;

int* par_pivot_pos;
int* par_down_pivot_iter;
int* par_up_pivot_iter;

// int THREAD_NUMS[] = {1, 2, 4, 8, 16, 32, 64};
int THREAD_NUMS[] = {1, 2, 4, 8};
// int THREAD_NUMS[] = {2, 4, 8, 16, 32, 64};

// int SIZES[] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
// int SIZES[] = {10, 20, 30, 40, 50, 100, 200, 400, 1000};
int SIZES[] = {10, 100, 300, 500, 1000, 1500, 2000, 2500};
// int SIZES[] = {1500, 2000, 2500, 3000, 3500, 4000};
