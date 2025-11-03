#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstring>
using namespace std;
using namespace std::chrono;

#define MAX 10000
#define d 256
#define q 101

void rabinKarp(const char *text, const char *pattern)
{
    int n = strlen(text), m = strlen(pattern), h = 1, p = 0, t = 0;
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;
    for (int i = 0; i < m; i++)                                                                        
    {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }
    for (int i = 0; i <= n - m; i++)
    {
        if (p == t)
        {
            int j;
            for (j = 0; j < m && text[i + j] == pattern[j]; j++)
                ;
        }
        if (i < n - m)
        {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t += q;
        }
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
        text_avg[i] = 'A' + (i % 3);
    strcpy(pattern_avg, "ABC");
    for (int i = 0; i < n; i++)
        text_worst[i] = 'A';
    strcpy(pattern_worst, "AAAAA");
    string caseName[3] = {"Best Case", "Average Case", "Worst Case"};
    char *texts[3] = {text_best, text_avg, text_worst};
    char *patterns[3] = {pattern_best, pattern_avg, pattern_worst};
    for (int c = 0; c < 3; c++)
    {
        auto start = high_resolution_clock::now();
        rabinKarp(texts[c], patterns[c]);
        auto end = high_resolution_clock::now();
        duration<double> sec = end - start;
        cout << fixed << setprecision(6) << caseName[c] << " : " << sec.count() << " seconds" << endl;
    }
    return 0;
}
 