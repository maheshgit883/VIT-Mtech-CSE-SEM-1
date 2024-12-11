#include <stdio.h>
#include <omp.h>

#define MAX_SIZE 100  // Define a fixed maximum size for the array

int main() {
    int i, size;
    int array[MAX_SIZE];
    int sum_even = 0, sum_odd = 0;

    // Take the size of the array as input
    printf("Enter the size of the array (max %d): ", MAX_SIZE);
    scanf("%d", &size);

    if (size > MAX_SIZE) {
        printf("Size exceeds maximum allowed value of %d.\n", MAX_SIZE);
        return 1;
    }

    // Take input for the array
    printf("Enter elements of the array:\n");
    for (i = 0; i < size; i++) {
        printf("Element %d: ", i);
        scanf("%d", &array[i]);
    }

    // Parallel region to compute sums and print thread information
    #pragma omp parallel
    {
        // Get the thread ID
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // Print total threads information only once
        #pragma omp master
        {
            printf("Total threads: %d\n", num_threads);
        }

        // Print thread-specific information
        printf("Thread %d: ", thread_id);
        if (thread_id == 0) {
            printf("This is the master thread.\n");
        } else {
            printf("This is not the master thread.\n");
        }

        // Private variables for sums
        int local_sum_even = 0;
        int local_sum_odd = 0;

        #pragma omp for
        for (i = 0; i < size; i++) {
            if (array[i] % 2 == 0) {
                local_sum_even += array[i];
            } else {
                local_sum_odd += array[i];
            }
        }

        // Update global sums in a thread-safe manner
        #pragma omp critical
        {
            sum_even += local_sum_even;
            sum_odd += local_sum_odd;
        }
    }

    // Print the results
    printf("Sum of even numbers: %d\n", sum_even);
    printf("Sum of odd numbers: %d\n", sum_odd);

    return 0;
}
