#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
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
        arr[i] = n - i - 1;
}

int main()
{
    const int SIZE = 10000;
    int arr[SIZE];
    int choice;
    srand(time(0));

    while (true)
    {
        cout << "\nMerge Sort Performance\n";
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
        mergeSort(arr, 0, SIZE - 1);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_used = end - start;

        cout << ((choice == 1) ? "\nBest Case Time: " : (choice == 2) ? "\nAverage Case Time: "
                                                                      : "\nWorst Case Time: ");
        cout << time_used.count() << " seconds\n";
    }
    return 0;
}
