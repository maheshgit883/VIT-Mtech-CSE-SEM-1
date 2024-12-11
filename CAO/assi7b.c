#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_STUDENTS 100

// Global variables
int registered[MAX_STUDENTS]; // Array to store registered students
int num_registered = 0;       // Number of registered students
omp_lock_t lock;              // Lock for synchronization

// Function to register a student
void registerStudent(int student_id)
{
    omp_set_lock(&lock); // Acquire the lock to perform registration
    registered[num_registered] = student_id;
    num_registered++;
    printf("Student %d registered.\n", student_id);
    omp_unset_lock(&lock); // Release the lock
}

// Function to unregister a student
void unregisterStudent(int student_id)
{
    omp_set_lock(&lock); // Acquire the lock to perform unregistration
    int found = 0;
    for (int i = 0; i < num_registered; i++)
    {
        if (registered[i] == student_id)
        {
            // Remove the student from the list by shifting elements
            for (int j = i; j < num_registered - 1; j++)
            {
                registered[j] = registered[j + 1];
            }
            num_registered--;
            found = 1;
            printf("Student %d unregistered.\n", student_id);
            break;
        }
    }
    if (!found)
    {
        printf("Student %d not found in the registered list.\n", student_id);
    }
    omp_unset_lock(&lock); // Release the lock
}

// Function to display the registered list
void displayRegisteredList()
{
    omp_set_lock(&lock); // Acquire the lock to display the list
    printf("Registered students: ");
    for (int i = 0; i < num_registered; i++)
    {
        printf("%d ", registered[i]);
    }
    printf("\n");
    omp_unset_lock(&lock); // Release the lock
}
int main()
{
    int choice, student_id;
    omp_init_lock(&lock); // Initialize the lock
    while (1)
    {
        printf("Enter your choice:\n");
        printf("1. Register\n");
        printf("2. Unregister\n");
        printf("3. Display registered list\n");
        printf("4. Exit\n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter student ID to register: ");
            scanf("%d", &student_id);
            registerStudent(student_id);
        }
        else if (choice == 2)
        {
            printf("Enter student ID to unregister: ");
            scanf("%d", &student_id);
            unregisterStudent(student_id);
        }
        else if (choice == 3)
        {
            displayRegisteredList();
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    }
    omp_destroy_lock(&lock); // Destroy the lock
    return 0;
}
