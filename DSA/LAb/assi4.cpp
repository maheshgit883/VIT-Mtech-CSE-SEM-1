#include <iostream>
#include <algorithm>  // For using 'swap' function
using namespace std;

// Function to perform a bitonic merge
void bitonicMerge(int arr[], int start, int length, bool asc) {
    if (length > 1) {
        int mid = length / 2;
        // Compare and swap elements based on asc order
        for (int i = start; i < start + mid; i++) {
            if ((arr[i] > arr[i + mid]) == asc) {
                swap(arr[i], arr[i + mid]);
            }
        }
        // Recursively merge both halves
        bitonicMerge(arr, start, mid, asc);
        bitonicMerge(arr, start + mid, mid, asc);
    }
}

// Function to perform bitonic sort
void bitonicSort(int arr[], int start, int length, bool asc) {
    if (length > 1) {
        int mid = length / 2;
        // Sort first half in asc order
        bitonicSort(arr, start, mid, true);
        // Sort second half in descending order
        bitonicSort(arr, start + mid, mid, false);
        // Merge the entire array in the required order
        bitonicMerge(arr, start, length, asc);
    }
}

// Function to perform interpolation search on a sorted array
int interpolationSearch(const int arr[], int size, int target) {
    int low = 0, high = size - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (arr[low] == arr[high])  // Avoid division by zero
            break;

        // Estimate the probable position of the target element
        int pos = low + ((target - arr[low]) * (high - low) / (arr[high] - arr[low]));

        // If the element is found
        if (arr[pos] == target) {
            return pos;
        }

        // If target is greater, ignore left half
        if (arr[pos] < target) {
            low = pos + 1;
        } 
        // If target is smaller, ignore right half
        else {
            high = pos - 1;
        }
    }
    return -1;  // Target not found
}

int main() {
    int n;
    // Take input for the number of elements
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    // Ensure the number of elements is a power of 2 (required for bitonic sort)
    if (n & (n - 1)) {
        cout << "Error: Number of elements must be a power of 2 for bitonic sort." << endl;
        return 1;
    }

    // Dynamic array to store user inputs
    int* arr = new int[n];
    
    // Take input for array elements
    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Perform Bitonic Sort in asc order
    bitonicSort(arr, 0, n, true);

    // Display the sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Input the target element to search
    int target;
    cout << "Enter the target value to search for: ";
    cin >> target;

    // Perform Interpolation Search
    int result = interpolationSearch(arr, n, target);

    // Display search result
    if (result != -1) {
        cout << "Element found at index " << result << ".\n";
    } else {
        cout << "Element not found in the array.\n";
    }

    // Free dynamically allocated memory
    delete[] arr;

    return 0;
}
