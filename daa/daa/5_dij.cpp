#include <iostream>
#include <climits>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int MAX_NODES = 100000;
const int MAX_EDGES_PER_NODE = 10;

int adj[MAX_NODES][MAX_EDGES_PER_NODE];
int cost[MAX_NODES][MAX_EDGES_PER_NODE];
int degree[MAX_NODES];
int dist[MAX_NODES];
bool visited[MAX_NODES];

int find_min_dist_node(int n)
{
    int minDist = INT_MAX, node = -1;
    for (int i = 0; i < n; i++)
        if (!visited[i] && dist[i] < minDist)
            minDist = dist[i], node = i;
    return node;
}

void dijkstra(int n, int source)
{
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, visited[i] = false;
    dist[source] = 0;
    for (int i = 0; i < n; i++)
    {
        int u = find_min_dist_node(n);
        if (u == -1)
            break;
        visited[u] = true;
        for (int j = 0; j < degree[u]; j++)
        {
            int v = adj[u][j], w = cost[u][j];
            if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }
}

void create_graph(int n, int type)
{
    for (int i = 0; i < n; i++)
        degree[i] = 0;
    if (type == 1)
    {
        for (int i = 0; i < n - 1; i++)
        {
            adj[i][degree[i]] = i + 1;
            cost[i][degree[i]++] = 1;
        }
    }
    else if (type == 2)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 1; j <= 3 && i + j < n; j++)
            {
                adj[i][degree[i]] = i + j;
                cost[i][degree[i]++] = (j * 3) % 10 + 1;
            }
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 1; j <= MAX_EDGES_PER_NODE; j++)
            {
                int v = (i + j) % n;
                adj[i][degree[i]] = v;
                cost[i][degree[i]++] = 1;
            }
        }
    }
}

int main()
{
    const int n = 10000, source = 0;
    for (int type = 1; type <= 3; type++)
    {
        create_graph(n, type);
        auto start = high_resolution_clock::now();
        dijkstra(n, source);
        auto end = high_resolution_clock::now();
        duration<double> sec = end - start;
        cout << fixed << setprecision(4);
        string case_name = (type == 1) ? "Worst Case" : (type == 2) ? "Average Case"
                                                                    : "Best Case";
        cout << case_name << " Execution Time: " << sec.count() << " seconds\n";
    }
    return 0;
}
