#include <iostream>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

const int N = 10000, M = 10;
int adj[N][M], cost[N][M], deg[N], dist[N];

bool bellman_ford(int n, int src)
{
    fill(dist, dist + n, INT_MAX);
    dist[src] = 0;

    for (int k = 1; k < n; k++)
        for (int u = 0; u < n; u++)
            for (int j = 0; j < deg[u]; j++)
            {
                int v = adj[u][j], w = cost[u][j];
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;
            }

    for (int u = 0; u < n; u++)
        for (int j = 0; j < deg[u]; j++)
        {
            int v = adj[u][j], w = cost[u][j];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                return false;
        }
    return true;
}

void create_graph(int n, int type)
{
    memset(deg, 0, sizeof(deg));
    for (int i = 0; i < n; i++)
    {
        if (type == 1 && i < n - 1)
        { // Worst: chain
            adj[i][deg[i]] = i + 1;
            cost[i][deg[i]++] = 1;
        }
        else if (type == 2 && i < n - 1)
        { // Average: 3 edges
            for (int j = 1; j <= 3 && i + j < n; j++)
                adj[i][deg[i]] = i + j, cost[i][deg[i]++] = (j * 3) % 10 + 1;
        }
        else if (type == 3)
        { // Best: 10 edges
            for (int j = 1; j <= M; j++)
                adj[i][deg[i]] = (i + j) % n, cost[i][deg[i]++] = 1;
        }
    }
}

int main()
{
    for (int t = 1; t <= 3; t++)
    {
        create_graph(N, t);
        auto st = high_resolution_clock::now();
        bool ok = bellman_ford(N, 0);
        auto en = high_resolution_clock::now();
        string name = (t == 1) ? "Best" : (t == 2) ? "Average"
                                                   : "Worst";
        cout << name << " Case Time: "
             << duration<double>(en - st).count() << "s\n";
        if (!ok)
            cout << "Negative cycle detected!\n";
    }
}
