#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

#define MAX 200 // maximum number of matrices

long long minMultiplications(int p[], int n)
{
    long long dp[MAX][MAX] = {0};

    for (int L = 2; L <= n; L++)
    { // chain length
        for (int i = 0; i <= n - L; i++)
        {
            int j = i + L - 1;
            dp[i][j] = 1e18; // infinity
            for (int k = i; k < j; k++)
            {
                long long q = dp[i][k] + dp[k + 1][j] + (long long)p[i] * p[k + 1] * p[j + 1];
                if (q < dp[i][j])
                    dp[i][j] = q;
            }
        }
    }
    return dp[0][n - 1];
}

int main()
{
    const int n = 50;
    int bestCase[MAX + 1], averageCase[MAX + 1], worstCase[MAX + 1];

    for (int i = 0; i <= n; i++)
        bestCase[i] = i + 10;

    for (int i = 0; i <= n; i++)
        averageCase[i] = 10 + (i * 7) % 50;

    for (int i = 0; i <= n; i++)
        worstCase[i] = (i % 2 == 0) ? 100 + i : 10 + i;

    int cases[3][MAX + 1];
    for (int i = 0; i <= n; i++)
    {
        cases[0][i] = bestCase[i];
        cases[1][i] = averageCase[i];
        cases[2][i] = worstCase[i];
    }

    string caseName[3] = {"Best Case", "Average Case", "Worst Case"};

    for (int c = 0; c < 3; c++)
    {
        auto start = high_resolution_clock::now();
        minMultiplications(cases[c], n);
        auto end = high_resolution_clock::now();
        duration<double> sec = end - start;

        cout << fixed << setprecision(6);
        cout << caseName[c] << " : " << sec.count() << " seconds" << endl;
    }

    return 0;
}
