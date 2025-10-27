#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;
using namespace std::chrono;

bool isSafe(int pos[], int row, int col)
{
    for (int i = 0; i < row; i++)
        if (pos[i] == col || abs(pos[i] - col) == row - i)
            return false;
    return true;
}

bool solveNQueens(int pos[], int row, int n, int colOrder[])
{ 
    if (row == n)
        return true;
    for (int i = 0; i < n; i++)
    {
        int col = colOrder[i];
        if (isSafe(pos, row, col))
        {
            pos[row] = col;
            if (solveNQueens(pos, row + 1, n, colOrder))
                return true;
        }
    }
    return false;
}

int main()
{
    const int n = 24; // Change N as needed
    int pos[n];
    int orders[3][n];

    // Best Case: middle columns first
    for (int i = 0; i < n; i++)
        orders[0][i] = n / 2 + (i % 2 == 0 ? i / 2 : -((i + 1) / 2));

    // Average Case: 0..N-1
    for (int i = 0; i < n; i++)
        orders[1][i] = i;

    // Worst Case: N-1..0
    for (int i = 0; i < n; i++)
        orders[2][i] = n - 1 - i;

    string caseName[3] = {"Best Case", "Average Case", "Worst Case"};

    for (int c = 0; c < 3; c++)
    {
        auto start = high_resolution_clock::now();
        solveNQueens(pos, 0, n, orders[c]);
        auto end = high_resolution_clock::now();
        duration<double> sec = end - start;

        cout << fixed << setprecision(6);
        cout << caseName[c] << " : " << sec.count() << " seconds" << endl;
    }

    return 0;
}
