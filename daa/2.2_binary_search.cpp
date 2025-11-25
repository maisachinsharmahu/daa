#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>
using namespace std;

int binarySearch(int arr[], int n, int target)
{
    int left = 0, right = n - 1;
    int comparisons = 0;

    while (left <= right)
    {
        comparisons++;
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            cout << "Comparisons made: " << comparisons << "\n";
            return mid;
        }

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    cout << "Comparisons made: " << comparisons << "\n";
    return -1;
}

int main()
{
    const int SIZE = 100000;
    int arr[SIZE];
    int target;
    int choice;

    srand(time(0));

    while (true)
    {
        cout << "\nBinary Search Performance Analysis\n";
        cout << "Array size: " << SIZE << " elements\n";

        cout << "1. Best Case (Element at middle position)\n";
        cout << "2. Average Case (Element requires average comparisons)\n";
        cout << "3. Worst Case (Element at leaf level)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        if (choice == 4)
        {
            cout << "Exiting program. Bye!\n";
            break;
        }

        for (int i = 0; i < SIZE; i++)
            arr[i] = i + 1;

        switch (choice)
        {
        case 1:
            target = arr[SIZE / 2];
            break;
        case 2:
            target = arr[SIZE / 4];
            break;
        case 3:
            target = arr[0];
            break;
        default:
            cout << "Invalid choice! Try again.\n";
            continue;
        }

        auto start = chrono::high_resolution_clock::now();
        int result = binarySearch(arr, SIZE, target);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_used = end - start;

        cout << ((choice == 1) ? "\nBest Case - " : (choice == 2) ? "\nAverage Case - "
                                                                  : "\nWorst Case - ");
        cout << "Element " << target << ((result != -1) ? " found at index " + to_string(result) : " not found");
        cout << "\nTime taken: " << time_used.count() << " seconds\n";
    }

    return 0;
}