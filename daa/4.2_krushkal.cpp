#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cstring>
using namespace std;
const int MAX = 500;

struct Edge
{
    int u, v, w;
};

int parent[MAX], rnk[MAX];

int findSet(int x)
{
    if (x != parent[x])
        parent[x] = findSet(parent[x]);
    return parent[x];
}

bool unionSet(int x, int y)
{
    int rx = findSet(x);
    int ry = findSet(y);
    if (rx == ry)
        return false;
    if (rnk[rx] < rnk[ry])
        parent[rx] = ry;
    else if (rnk[ry] < rnk[rx])
        parent[ry] = rx;
    else
    {
        parent[ry] = rx;
        rnk[rx]++;
    }
    return true;
}

int kruskalMST(vector<Edge> &edges, int V)
{
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
        rnk[i] = 0;
    }
    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
         { return a.w < b.w; });

    int totalWeight = 0;
    for (auto &e : edges)
    {
        if (unionSet(e.u, e.v))
        {
            totalWeight += e.w;
        }
    }
    return totalWeight;
}

int main()
{
    srand(time(0));
    int choice;
    int V = 200;

    while (true)
    {
        cout << "\nPrim\n";
        cout << "1. Best Case \n";
        cout << "2. Average Case \n";
        cout << "3. Worst Case \n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        if (choice == 4)
            break;

        vector<Edge> edges;

        if (choice == 1)
        {
            for (int i = 0; i < V - 1; i++)
            {
                edges.push_back({i, i + 1, 1});
            }
        }
        else if (choice == 2)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = i + 1; j < V; j++)
                {
                    if (rand() % 100 < 30)
                    {
                        int w = rand() % 100 + 1;
                        edges.push_back({i, j, w});
                    }
                }
            }
        }
        else if (choice == 3)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = i + 1; j < V; j++)
                {
                    int w = rand() % 100 + 1;
                    edges.push_back({i, j, w});
                }
            }
        }
        else
        {
            cout << "Invalid choice!\n";
            continue;
        }

        auto start = chrono::high_resolution_clock::now();
        int totalWeight = kruskalMST(edges, V);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_used = end - start;

        cout << "MST Total Weight = " << totalWeight << "\n";
        cout << "Time Taken = " << time_used.count() << " seconds\n";
    }
    return 0;
}