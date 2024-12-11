#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10  // Size of the array

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for QuickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Pivot element
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Parallel QuickSort function
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array
        int pi = partition(arr, low, high);

        // Parallelize recursive calls
        #pragma omp parallel sections
        {
            #pragma omp section
            quicksort(arr, low, pi - 1);

            #pragma omp section
            quicksort(arr, pi + 1, high);
        }
    }
}

int main() {
    int arr[N];

    // Taking array input from the user
    printf("Enter %d elements for sorting:\n", N);
    for (int i = 0; i < N; i++) {
        printf("Element[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    // Start time measurement
    double start_time = omp_get_wtime();

    // Call parallel QuickSort
    #pragma omp parallel
    {
        #pragma omp single
        quicksort(arr, 0, N - 1);
    }

    // End time measurement
    double end_time = omp_get_wtime();

    // Display sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Display the time taken
    printf("Time taken for parallel QuickSort: %f seconds\n", end_time - start_time);

    return 0;
}
