#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void bestCase(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
}
void averageCase(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;
}
void worstCase(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

int main()
{
    const int SIZE = 10000;
    int arr[SIZE];
    int choice;
    srand(time(0));

    while (true)
    {
        cout << "\nHeap Sort Performance\n";
        cout << "1. Best Case \n2. Average Case\n3. Worst Case\n4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        if (choice == 4)
        {
            cout << "Exiting program. Bye!\n";
            break;
        }

        switch (choice)
        {
        case 1:
            bestCase(arr, SIZE);
            break;
        case 2:
            averageCase(arr, SIZE);
            break;
        case 3:
            worstCase(arr, SIZE);
            break;
        default:
            cout << "Invalid choice! Try again.\n";
            continue;
        }

        auto start = chrono::high_resolution_clock::now();
        heapSort(arr, SIZE);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_used = end - start;

        cout << ((choice == 1) ? "\nBest Case Time: " : (choice == 2) ? "\nAverage Case Time: "
                                                                      : "\nWorst Case Time: ");
        cout << time_used.count() << " seconds\n";
    }
    return 0;
}