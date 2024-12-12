#include <iostream>
using namespace std;

// Function to get the maximum element in the array
int getMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];
    return maxVal;
}

void countingSort(int arr[], int n, int exp) {
    int output[n];            // Output array to store the sorted numbers
    int count[10] = {0};       // Count array to store the frequency of each digit (0-9)

    // Step 1: Count occurrences of each digit at 'exp' place
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;  // Extract the digit at 'exp' place
        count[digit]++;                   // Increment the count for that digit
    }

    // Step 2: Modify count[] so it contains the position of each digit in the output array
    for (int i = 1; i < 10; i++) {
        count[i] = count[i] + count[i - 1]; // Adjust count to hold the position in output array
    }

    // Step 3: Build the output array by placing numbers in the correct positions
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;         // Get the digit at the current 'exp' place
        output[count[digit] - 1] = arr[i];       // Place the number in the correct position
        count[digit]--;                          // Decrease the count for the digit
    }

    // Step 4: Copy the sorted output array back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];                      // Copy each sorted element back to the array
    }
}


// Radix Sort function
void radixSort(int arr[], int n) {
    int maxVal = getMax(arr, n);  // Find maximum value
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

// Recursive Binary Search function
int binarySearch(int arr[], int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid; // Target found
        if (arr[mid] > target)
            return binarySearch(arr, left, mid - 1, target); // Search in left half
        return binarySearch(arr, mid + 1, right, target); // Search in right half
    }
    return -1; // Target not found
}

// Exponential Search function
int exponentialSearch(int arr[], int n, int target) {
    if (arr[0] == target) return 0;

    int i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }

    // Binary search for the range [i/2, min(i, n)]
    return binarySearch(arr, i / 2, min(i, n - 1), target);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n;

    // Taking input for the size of the array
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];

    // Taking input for the array elements
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Sorting the array using Radix Sort
    radixSort(arr, n);

    cout << "Sorted array: ";
    printArray(arr, n);

    // Taking input for the element to search
    int target;
    cout << "Enter the element to search: ";
    cin >> target;

    // Searching for the element using Exponential Search
    int result = exponentialSearch(arr, n, target);

    if (result != -1) {
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found in the array." << endl;
    }

    return 0;
}
