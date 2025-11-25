#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstring>
using namespace std;
using namespace std::chrono;

#define MAX 10000

void computeLPS(const char *pat, int m, int *lps)
{
    int len = 0, i = 1;
    lps[0] = 0;
    while (i < m)
    {
        if (pat[i] == pat[len])
            lps[i++] = ++len;
        else if (len)
            len = lps[len - 1];
        else
            lps[i++] = 0;
    }
}

void KMP(const char *text, const char *pat)
{
    int n = strlen(text), m = strlen(pat), lps[MAX];
    computeLPS(pat, m, lps);
    int i = 0, j = 0;
    while (i < n)
    {
        if (pat[j] == text[i])
        {
            i++;
            j++;
        }
        if (j == m)
            j = lps[j - 1];
        else if (i < n && pat[j] != text[i])
            j ? j = lps[j - 1] : i++;
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
        text_avg[i] = (i % 4 == 0) ? 'A' : 'B';
    strcpy(pattern_avg, "ABAB");
    for (int i = 0; i < n; i++)
        text_worst[i] = 'A';
    strcpy(pattern_worst, "AAAAA");
    string caseName[3] = {"Best Case", "Average Case", "Worst Case"};
    char *texts[3] = {text_best, text_avg, text_worst};
    char *patterns[3] = {pattern_best, pattern_avg, pattern_worst};
    for (int c = 0; c < 3; c++)
    {
        auto start = high_resolution_clock::now();
        KMP(texts[c], patterns[c]);
        auto end = high_resolution_clock::now();
        duration<double> sec = end - start;
        cout << fixed << setprecision(6) << caseName[c] << " : " << sec.count() << " seconds" << endl;
    }
    return 0;
}
