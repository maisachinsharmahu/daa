#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

int linearSearch(int arr[], int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

int main()
{
    const int SIZE = 1000000;
    int *arr = new int[SIZE];
    int target;
    int choice;

    srand(time(0));

    while (true)
    {
        cout << "\nLinear Search Performance Analysis\n";
        cout << "1. Best Case (Element at first position)\n";
        cout << "2. Average Case (Element at middle position)\n";
        cout << "3. Worst Case (Element at last position)\n";
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
            target = 1;
            break;
        case 2:
            target = SIZE / 2;
            break;
        case 3:
            target = SIZE;
            break;
        default:
            cout << "Invalid choice! Try again.\n";
            continue;
        }

        auto start = chrono::high_resolution_clock::now();
        int result = linearSearch(arr, SIZE, target);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_used = end - start;

        cout << ((choice == 1) ? "\nBest Case - " : (choice == 2) ? "\nAverage Case - "
                                                                  : "\nWorst Case - ");
        cout << "Element " << target << ((result != -1) ? " found at index " + to_string(result) : " not found");
        cout << "\nTime taken: " << time_used.count() << " seconds\n";
        cout << "Comparisons made: " << ((result != -1) ? result + 1 : SIZE) << "\n";
    }

    delete[] arr;
    return 0;
}
