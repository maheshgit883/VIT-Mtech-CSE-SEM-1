#include <stdio.h>
#include <omp.h>

#define ROWS 2   // Number of rows in the matrix
#define COLS 3   // Number of columns in the matrix (and size of the vector)

int main() {
    int matrix[ROWS][COLS], vector[COLS], result[ROWS] = {0};

    // Taking matrix input from the user
    printf("Enter elements of %dx%d matrix:\n", ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("Matrix[%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    // Taking vector input from the user
    printf("Enter elements of vector of size %d:\n", COLS);
    for (int i = 0; i < COLS; i++) {
        printf("Vector[%d]: ", i);
        scanf("%d", &vector[i]);
    }

    // Start time measurement
    double start_time = omp_get_wtime();

    // Matrix-vector multiplication in parallel
    #pragma omp parallel for
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    // End time measurement
    double end_time = omp_get_wtime();

    // Display the result
    printf("Resultant vector:\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%d\n", result[i]);
    }

    // Display the time taken
    printf("Time taken for matrix-vector multiplication: %f seconds\n", end_time - start_time);

    return 0;
}
