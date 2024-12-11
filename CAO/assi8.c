#include <stdio.h>
#include <omp.h>

int main()
{
    int N;
    double sum = 0.0, term;
    FILE *fptr;

    // Prompt user for the number of terms
    printf("Enter the number of terms (N): ");
    scanf("%d", &N);

    // Open file for writing output
    fptr = fopen("series.txt", "w");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

#pragma omp parallel shared(sum) private(term)
    {
        int tid = omp_get_thread_num();

#pragma omp for schedule(static) reduction(+ : sum) ordered
        for (int i = 1; i <= N; i++)
        {
            // Calculate the term of the series
            term = 1.0 / (1 << i); // Equivalent to 1.0 / (2^i)

#pragma omp ordered
            {
                // Print thread info, term, and partial sum to file and console in the order of execution
                printf("Thread %d - Term %d: %f\n", tid, i, term);
                fprintf(fptr, "Thread %d - Term %d: %f\n", tid, i, term);
            }

            sum += term;
        }

// Ensure all threads have completed their updates to `sum`
#pragma omp barrier

// Only one thread prints the final output for the sum and last term
#pragma omp single
        {
            printf("Sum of series: %f\n", sum);
            printf("Last term in series: %f\n", term);

            fprintf(fptr, "Sum of series: %f\n", sum);
            fprintf(fptr, "Last term in series: %f\n", term);
        }
    }

    // Close the file
    fclose(fptr);

    printf("Results written to series.txt\n");
    return 0;
}

