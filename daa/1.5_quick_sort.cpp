#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Cases
void bestCase(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}
void averageCase(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;
}
void worstCase(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i; // sorted (bad for basic quicksort)
}

int main() {
    const int SIZE = 10000;
    int arr[SIZE];
    int choice;
    srand(time(0));

    while (true) {
        cout << "\nQuick Sort Performance\n";
        cout << "1. Best Case \n2. Average Case\n3. Worst Case\n4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        if (choice == 4) {
            cout << "Exiting program. Bye!\n";
            break;
        }

        switch (choice) {
            case 1: bestCase(arr, SIZE); break;
            case 2: averageCase(arr, SIZE); break;
            case 3: worstCase(arr, SIZE); break;
            default: cout << "Invalid choice! Try again.\n"; continue;
        }

        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, SIZE - 1);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_used = end - start;

        cout << ((choice == 1) ? "\nBest Case Time: " : 
                (choice == 2) ? "\nAverage Case Time: " : 
                                "\nWorst Case Time: ");
        cout << time_used.count() << " seconds\n";
    }
    return 0;
}
