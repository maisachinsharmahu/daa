#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstring>
using namespace std;
using namespace std::chrono;

#define MAX 1000

int LCS(char X[], char Y[], int m, int n) {
    int dp[MAX + 1][MAX + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

int main() {
    const int n = 800;

    char X_best[MAX], Y_best[MAX];
    char X_avg[MAX], Y_avg[MAX];
    char X_worst[MAX], Y_worst[MAX];

    // Best Case: identical strings (max matches)
    for (int i = 0; i < n; i++)
        X_best[i] = Y_best[i] = 'A' + (i % 3);

    // Average Case: partially similar
    for (int i = 0; i < n; i++) {
        X_avg[i] = 'A' + (i % 5);
        Y_avg[i] = 'A' + ((i + 2) % 5);
    }

    // Worst Case: completely different characters
    for (int i = 0; i < n; i++) {
        X_worst[i] = 'A' + (i % 26);
        Y_worst[i] = 'Z' - (i % 26);
    }

    string caseName[3] = {"Best Case", "Average Case", "Worst Case"};
    char *casesX[3] = {X_best, X_avg, X_worst};
    char *casesY[3] = {Y_best, Y_avg, Y_worst};

    for (int c = 0; c < 3; c++) {
        auto start = high_resolution_clock::now();
        LCS(casesX[c], casesY[c], n, n);
        auto end = high_resolution_clock::now();
        duration<double> sec = end - start;

        cout << fixed << setprecision(6);
        cout << caseName[c] << " : " << sec.count() << " seconds" << endl;
    }

    return 0;
}
