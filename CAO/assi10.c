#include <stdio.h>
#include <omp.h>

#define N 3  // Size of the matrices (N x N)

int main() {
    int A[N][N], B[N][N], C[N][N] = {0};

    // Taking input for Matrix A
    printf("Enter elements of %dx%d matrix A:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    // Taking input for Matrix B
    printf("Enter elements of %dx%d matrix B:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    // Start time measurement
    double start_time = omp_get_wtime();

    // Matrix multiplication in parallel
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // End time measurement
    double end_time = omp_get_wtime();

    // Display the result
    printf("Resultant matrix C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Display the time taken
    printf("Time taken for matrix multiplication: %f seconds\n", end_time - start_time);

    return 0;
}
