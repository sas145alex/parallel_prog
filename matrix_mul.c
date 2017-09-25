#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int show_matrix(int**, int, int);
int show_vector(int*, int);
int check_result(int*, int*, int);
int* mul(int**, int*, int);
int* mul_omp(int**, int*, int, int);

int main(int argc, char* argv[]){
    double begin, end, time_spent;
    srand(time(NULL));
    int size = 20000;
    int thr = 4;
    int *result, *result_omp;
    int **matrix = (int**) malloc(size * sizeof(int*));
    int *vector = (int*) malloc(size * sizeof(int));
    for (int i=0; i<size; i++){
        vector[i] = rand() % 100;
        matrix[i] = (int*) malloc(size * sizeof(int));
        for (int j=0; j<size; j++){
            matrix[i][j] = rand() % 100;
        }
    }
    // show_vector(vector, size);
    // show_matrix(matrix, size, size);
    begin = omp_get_wtime();
    result_omp = mul_omp(matrix, vector, size, thr);
    end = omp_get_wtime();
    time_spent = end - begin;
    printf("Parallel: %lf\n", time_spent);

    begin = omp_get_wtime();
    result = mul(matrix, vector, size);
    end = omp_get_wtime();
    time_spent = end - begin;
    printf("Consistent: %lf\n", time_spent);

    check_result(result_omp, result, size);
    // show_vector(result, size);
    return 0;
}

int show_matrix(int** matrix, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++ ){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int show_vector(int* vector, int size){
    printf("Vector: ");
    for (int i=0; i < size; i++)
        printf("%d ", vector[i]);
    printf("\n");
    return 0;
}

int* mul(int** matrix, int* vector, int size){
    int* result = (int*) malloc(size * sizeof(int));
    for (int i=0; i<size; i++){
        result[i] = 0;
        for (int j=0; j<size; j++){
            result[i] += matrix[i][j] * vector[j];
        }
    }
    return result;
}

int check_result(int* vector_a, int* vector_b, int size){
    for(int i=0; i<size; i++){
        if (vector_a[i] != vector_b[i]){
            printf("Vectors are different.\n");
            return -1;
        }
    }
    printf("Vectors are same.\n");
    return 0;
}

int* mul_omp(int** matrix, int* vector, int size, int thr){
    omp_set_nested(1);
    omp_set_dynamic(0);
    omp_set_num_threads(thr);
    int i,j;
    int* result = (int*) malloc(size * sizeof(int));
    #pragma omp parallel shared(result) private(i,j)
    {
    #pragma omp for
        for (i=0; i<size; i++){
            result[i] = 0;
            for (j=0; j<size; j++){
                result[i] += matrix[i][j] * vector[j];
            }
        }
    }
    return result;
}
