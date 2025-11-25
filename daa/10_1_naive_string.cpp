#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstring>
using namespace std;
using namespace std::chrono;

#define MAX 10000

void naiveSearch(const char *text, const char *pattern)
{
    int n = strlen(text), m = strlen(pattern);
    for (int i = 0; i <= n - m; i++)
    {
        int j;
        for (j = 0; j < m && text[i + j] == pattern[j]; j++)
            ;
    }
}

int main()
{
    const int n = 5000;
    char text_best[MAX], pattern_best[50], text_avg[MAX], pattern_avg[50], text_worst[MAX], pattern_worst[50];
    for (int i = 0; i < n; i++)
        text_best[i] = 'A';
    strcpy(pattern_best, "B");
    for (int i = 0; i < n; i++)
        text_avg[i] = (i % 5 == 0) ? 'A' : 'B';
    strcpy(pattern_avg, "ABBAB");
    for (int i = 0; i < n; i++)
        text_worst[i] = 'A';
    strcpy(pattern_worst, "AAAAA");
    string caseName[3] = {"Best Case", "Average Case", "Worst Case"};
    char *texts[3] = {text_best, text_avg, text_worst};
    char *patterns[3] = {pattern_best, pattern_avg, pattern_worst};
    for (int c = 0; c < 3; c++)
    {
        auto start = high_resolution_clock::now();
        naiveSearch(texts[c], patterns[c]);
        auto end = high_resolution_clock::now();
        duration<double> sec = end - start;
        cout << fixed << setprecision(6) << caseName[c] << " : " << sec.count() << " seconds" << endl;
    }
    return 0;
}