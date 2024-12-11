#include <omp.h>
#include <stdio.h>

int main() {
    int n;

    printf("Enter the number of elements in the arrays: ");
    scanf("%d", &n);

    int arr1[n], arr2[n], result[n];

    printf("Enter elements of the first array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Enter elements of the second array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr2[i]);
    }

    #pragma omp parallel
    {
        int tid = omp_get_thread_num(); // Get thread number
        int num_threads = omp_get_num_threads(); // Total number of threads

        #pragma omp for
        for (int i = 0; i < n; i++) {
            result[i] = arr1[i] + arr2[i];
            printf("Thread %d computed element %d: %d + %d = %d\n", tid, i, arr1[i], arr2[i], result[i]);
        }

        if (tid == 0) {
            printf("Master thread (Thread %d) is managing the parallel execution.\n", tid);
            printf("Total number of threads: %d\n", num_threads);
        }
    }

    printf("\nResulting array after summing the two arrays:\n");
    for (int i = 0; i < n; i++) {
        printf("result[%d] = %d\n", i, result[i]);
    }

    return 0;
}