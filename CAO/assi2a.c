#include <stdio.h>
#include <omp.h>

#define MAX_PEOPLE 100  // Define a maximum number of people

int main() {
    int ages[MAX_PEOPLE];  // Array to store ages
    int eligible[MAX_PEOPLE];  // Array to store eligibility (1 for eligible, 0 for not eligible)
    int N;  // Number of people

    // Get the number of people from the user
    printf("Enter the number of people: ");
    scanf("%d", &N);

    // Ensure N does not exceed the maximum limit
    if (N > MAX_PEOPLE) {
        printf("Number of people exceeds maximum limit of %d.\n", MAX_PEOPLE);
        return 1;
    }

    // Get the ages from the user
    printf("Enter the ages of the people:\n");
    for (int i = 0; i < N; i++) {
        scanf("%d", &ages[i]);
    }

    // Determine eligibility in the main thread
    for (int i = 0; i < N; i++) {
        eligible[i] = (ages[i] >= 16 && ages[i] < 18) ? 1 : 0;
    }


    // Start parallel region with two threads for printing
    #pragma omp parallel num_threads(2)
    {
        int thread_num = omp_get_thread_num();

        // Thread 0: Print non-eligible people
        if (thread_num == 0) {
            for (int i = 0; i < N; i++) {
                if (eligible[i] == 0) {
                    printf("Thread %d: Person with age %d is not eligible.\n", thread_num, ages[i]);
                }
            }
        }
        // Thread 1: Print eligible people
        if (thread_num == 1) {
            for (int i = 0; i < N; i++) {
                if (eligible[i] == 1) {
                    printf("Thread %d: Person with age %d is eligible.\n", thread_num, ages[i]);
                }
            }
        }
    }

      int eligible_count = 0;
       int not_eligible_count = 0;
      #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Count non-eligible people
           
            for (int i = 0; i < N; i++) {
                if (eligible[i] == 0) {
                    not_eligible_count++;
                }
            }
        }

        #pragma omp section
        {
            // Count eligible people
            for (int i = 0; i < N; i++) {
                if (eligible[i] == 1) {
                    eligible_count++;
                }
            }
        }
    }
    printf("Total number of eligible candidates: %d\n", eligible_count);
    printf("Total number of not eligible candidates: %d\n", not_eligible_count);
    return 0;
}