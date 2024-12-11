#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

#define NUM_STUDENTS 10

// Define a structure for student
typedef struct {
    char name[50];
    int reg_no;
    float pay_package;
    char company[50];
} Student;

// Array to hold student data
Student students[NUM_STUDENTS];

// Function to get student data
void get_student_data() {
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Enter details for student %d\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Register Number: ");
        scanf("%d", &students[i].reg_no);
        printf("Pay Package: ");
        scanf("%f", &students[i].pay_package);
        printf("Company (Amazon/Google/Shell/Intel): ");
        scanf("%s", students[i].company);
    }
}

// Function to display total students per company
void display_total_students_per_company() {
    int count_amazon = 0, count_google = 0, count_shell = 0, count_intel = 0;

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < NUM_STUDENTS; i++) {
            if (strcmp(students[i].company, "Amazon") == 0) {
                #pragma omp atomic
                count_amazon++;
            } else if (strcmp(students[i].company, "Google") == 0) {
                #pragma omp atomic
                count_google++;
            } else if (strcmp(students[i].company, "Shell") == 0) {
                #pragma omp atomic
                count_shell++;
            } else if (strcmp(students[i].company, "Intel") == 0) {
                #pragma omp atomic
                count_intel++;
            }
        }
    }

    printf("Total students per company:\n");
    printf("Amazon: %d\n", count_amazon);
    printf("Google: %d\n", count_google);
    printf("Shell: %d\n", count_shell);
    printf("Intel: %d\n", count_intel);
}

// Function to display average pay package
void display_average_pay_package() {
    float total_pay = 0.0;

    #pragma omp parallel
    {
        #pragma omp for reduction(+:total_pay)
        for (int i = 0; i < NUM_STUDENTS; i++) {
            total_pay += students[i].pay_package;
        }
    }

    float average_pay = total_pay / NUM_STUDENTS;
    printf("Average pay package: %.2f\n", average_pay);
}

int main() {
    double start_time, end_time;

    start_time = omp_get_wtime();
    get_student_data();
    end_time = omp_get_wtime();
    printf("Time taken for input student data: %f seconds\n", end_time - start_time);

    // Parallel region with sections
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            double section_start_time = omp_get_wtime();
            display_total_students_per_company();
            double section_end_time = omp_get_wtime();
            printf("Time taken for displaying total students per company: %f seconds\n", section_end_time - section_start_time);
        }

        #pragma omp section
        {
            double section_start_time = omp_get_wtime();
            display_average_pay_package();
            double section_end_time = omp_get_wtime();
            printf("Time taken for calculating average pay package: %f seconds\n", section_end_time - section_start_time);
        }
    }

    return 0;
}
