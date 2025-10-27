#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstring>
using namespace std;
using namespace std::chrono;

void naiveSearch(char txt[], char pat[]) {
    int n = strlen(txt);
    int m = strlen(pat);
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++)
            if (txt[i + j] != pat[j])
                break;
    }
}

int main() {
    const int n = 50000;
    char text_best[n + 1], text_avg[n + 1], text_worst[n + 1];
    char pattern[] = "ABC";

    // Best Case: pattern mismatches immediately
    for (int i = 0; i < n; i++) text_best[i] = 'X';
    text_best[n] = '\0';

    // Average Case: some matches in between
    for (int i = 0; i < n; i++) text_avg[i] = (i % 5 == 0 ? 'A' : 'B');
    text_avg[n] = '\0';

    // Worst Case: all same characters (forces full comparison each time)
    for (int i = 0; i < n; i++) text_worst[i] = 'A';
    text_worst[n] = '\0';

    string caseName[3] = {"Best Case", "Average Case", "Worst Case"};
    char* texts[3] = {text_best, text_avg, text_worst};

    for (int c = 0; c < 3; c++) {
        auto start = high_resolution_clock::now();
        naiveSearch(texts[c], pattern);
        auto end = high_resolution_clock::now();
        duration<double> sec = end - start;
        cout << fixed << setprecision(6);
        cout << caseName[c] << " : " << sec.count() << " seconds" << endl;
    }

    return 0;
}
