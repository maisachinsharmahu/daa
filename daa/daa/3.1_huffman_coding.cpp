#include <iostream>
#include <chrono>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *l, *r;
    Node(char c, int f) : ch(c), freq(f), l(NULL), r(NULL) {}
};

void getCodes(Node *root, string code, unordered_map<char, string> &huff)
{
    if (!root)
        return;
    if (!root->l && !root->r)
        huff[root->ch] = code;
    getCodes(root->l, code + "0", huff);
    getCodes(root->r, code + "1", huff);
}

string decode(const string &enc, Node *root)
{
    string res = "";
    Node *cur = root;
    for (char b : enc)
    {
        cur = (b == '0' ? cur->l : cur->r);
        if (!cur->l && !cur->r)
        {
            res += cur->ch;
            cur = root;
        }
    }
    return res;
}

void huffmanCoding(const string &text, bool printCodes)
{
    unordered_map<char, int> freq;
    for (char c : text)
        freq[c]++;

    auto cmp = [](Node *a, Node *b)
    { return a->freq > b->freq; };
    priority_queue<Node *, vector<Node *>, decltype(cmp)> pq(cmp);

    for (auto &p : freq)
        pq.push(new Node(p.first, p.second));

    while (pq.size() > 1)
    {
        auto l = pq.top();
        pq.pop();
        auto r = pq.top();
        pq.pop();
        auto n = new Node('\0', l->freq + r->freq);
        n->l = l;
        n->r = r;
        pq.push(n);
    }

    unordered_map<char, string> huff;
    getCodes(pq.top(), "", huff);

    if (printCodes)
    {
        cout << "\nHuffman Codes:\n";
        for (auto &p : huff)
            cout << p.first << " : " << p.second << "\n";
    }

    // Encode + Decode (just to validate, but no output)
    string enc = "";
    for (char c : text)
        enc += huff[c];
    string dec = decode(enc, pq.top());
    (void)dec; // suppress unused warning
}

int main()
{
    int choice;
    while (true)
    {
        cout << "\nHuffman Coding Performance Analysis\n";
        cout << "1. Best Case \n";
        cout << "2. Average Case \n";
        cout << "3. Worst Case \n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        string text;
        switch (choice)
        {
        case 1:
            // Best case: perfect balance (50k chars)
            text = string(12500, 'a') + string(12500, 'b') +
                   string(12500, 'c') + string(12500, 'd');
            break;

        case 2:
            // Average case: uneven distribution (100k chars)
            text = string(30000, 'a') + string(22000, 'b') +
                   string(18000, 'c') + string(14000, 'd') +
                   string(10000, 'e') + string(8000, 'f');
            break;

        case 3:
            // Worst case: highly skewed (150k chars)
            text = string(147000, 'a') + string(1500, 'b') +
                   string(800, 'c') + string(400, 'd') + string(300, 'e');
            break;

        case 4:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice! Try again.\n";
            continue;
        }

        auto start = chrono::high_resolution_clock::now();
        huffmanCoding(text, choice == 1); // codes sirf best case me print honge
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_used = end - start;
        cout << "Time used: " << time_used.count() << " seconds\n";
    }
}
