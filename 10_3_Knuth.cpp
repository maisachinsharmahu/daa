#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

void computeLPSArray(string pat, int M, vector<int> &lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();

    vector<int> lps(M);
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    int comparisons = 0;
    bool found = false;

    while (i < N)
    {
        comparisons++;
        if (pat[j] == txt[i])
        {
            i++;
            j++;
        }

        if (j == M)
        {
            cout << "Pattern found at index " << i - j << endl;
            found = true;
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        cout << "Pattern not found.\n";

    cout << "Total comparisons: " << comparisons << endl;
}

int main()
{
    string txt = "ABABDABACDABABCABAB";
    string pat = "ABABCABAB";

    auto start = high_resolution_clock::now();
    KMPSearch(pat, txt);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}
