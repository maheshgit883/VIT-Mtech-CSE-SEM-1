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

    // Determine eligibility
    for (int i = 0; i < N; i++) {
        eligible[i] = (ages[i] >= 16 && ages[i] < 18) ? 1 : 0;
    }

    // Initialize counters
    int eligible_count = 0;
    int not_eligible_count = 0;

    // Start parallel region with sections for counting
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Count non-eligible people
            int local_not_eligible_count = 0;
            for (int i = 0; i < N; i++) {
                if (eligible[i] == 0) {
                    local_not_eligible_count++;
                }
            }
            #pragma omp atomic
            not_eligible_count += local_not_eligible_count;
        }

        #pragma omp section
        {
            // Count eligible people
            int local_eligible_count = 0;
            for (int i = 0; i < N; i++) {
                if (eligible[i] == 1) {
                    local_eligible_count++;
                }
            }
            #pragma omp atomic
            eligible_count += local_eligible_count;
        }
    }

    // Print the results
    printf("Total number of eligible candidates: %d\n", eligible_count);
    printf("Total number of not eligible candidates: %d\n", not_eligible_count);

    return 0;
}
