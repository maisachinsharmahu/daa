#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cstring>
using namespace std;

const int INF = 1e9;
const int MAX = 500;

int graph[MAX][MAX];

int primMST(int V)
{
    int key[MAX];
    bool inMST[MAX];

    for (int i = 0; i < V; i++)
    {
        key[i] = INF;
        inMST[i] = false;
    }

    key[0] = 0;
    int totalWeight = 0;

    for (int count = 0; count < V; count++)
    {
        int u = -1;
        for (int i = 0; i < V; i++)
        {
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;
        }

        inMST[u] = true;
        totalWeight += key[u];

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
            }
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

        if (choice == 1)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                    graph[i][j] = 0;
            }
            // Sparse: connect only like a chain
            for (int i = 0; i < V - 1; i++)
            {
                graph[i][i + 1] = graph[i + 1][i] = 1;
            }
        }
        else if (choice == 2)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = i + 1; j < V; j++)
                {
                    if (rand() % 100 < 30)
                    { // ~30% edges present
                        int w = rand() % 100 + 1;
                        graph[i][j] = graph[j][i] = w;
                    }
                    else
                    {
                        graph[i][j] = graph[j][i] = 0;
                    }
                }
                graph[i][i] = 0;
            }
        }
        else if (choice == 3)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = i + 1; j < V; j++)
                {
                    int w = rand() % 100 + 1;
                    graph[i][j] = graph[j][i] = w;
                }
                graph[i][i] = 0;
            }
        }
        else
        {
            cout << "Invalid choice!\n";
            continue;
        }

        auto start = chrono::high_resolution_clock::now();
        int totalWeight = primMST(V);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> time_used = end - start;

        cout << "MST Total Weight = " << totalWeight << "\n";
        cout << "Time Taken = " << time_used.count() << " seconds\n";
    }
    return 0;
}
