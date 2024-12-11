#include <omp.h>
#include <stdio.h>

int main() {
    int num_students;
    printf("Enter the number of students: ");
    scanf("%d", &num_students);

    float height[num_students], weight[num_students], bmi[num_students];

    for (int i = 0; i < num_students; i++) {
        printf("Enter height (in meters) and weight (in kilograms) for student %d: ", i + 1);
        scanf("%f %f", &height[i], &weight[i]);
    }

    // Parallel region to calculate BMI for each student
    #pragma omp parallel
    {
        int tid = omp_get_thread_num(); // Get thread number
        int num_threads = omp_get_num_threads(); // Total number of threads

        #pragma omp for
        for (int i = 0; i < num_students; i++) {
            bmi[i] = weight[i] / (height[i] * height[i]);
            printf("Thread %d calculated BMI for student %d: %.2f\n", tid, i + 1, bmi[i]);
        }

        // Identify the master thread
        if (tid == 0) {
            printf("Master thread (Thread %d) is managing the parallel execution.\n", tid);
            printf("Total number of threads: %d\n", num_threads);
        }
    }
    return 0;
}
