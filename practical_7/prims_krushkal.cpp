#include <iostream>
using namespace std;
#define I 99

class Graph
{
public:
    int **adjMatrix;
    int size;

    Graph()
    {
        size = 0;
        adjMatrix = NULL;
    }
    Graph(int n)
    {
        size = n;
        adjMatrix = new int *[size];

        for (int i = 0; i < size; i++)
        {
            adjMatrix[i] = new int[size];
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                adjMatrix[i][j] = I;
            }
        }
    };

    void create()
    {
        int n, i, j, k, x;
        cout << "Enter number of edges : " << endl;
        cin >> n;
        for (k = 0; k < n; k++)
        {

            cout << "Enter source ,destination,value :";
            cin >> i;
            // cout << "Enter destination : ";
            cin >> j;
            // cout << "Enter value : ";
            cin >> x;

            adjMatrix[i][j] = x;
            adjMatrix[j][i] = x;
        }

        cout << "created";
    }

    void display()
    {
        cout << "Adjacency Matrix" << endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << adjMatrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void prims()
    {
        int visited[size], min = I, v1, v2, sum = 0;
        int edges[2][size - 1] = {0};
        std::cout << "prims" << std::endl;

        // find initial minnimum edge
        for (int i = 0; i < size; i++)
        {
            visited[i] = I;
            for (int j = i; j < size; j++)
            {
                if (adjMatrix[i][j] < min)
                {
                    min = adjMatrix[i][j];
                    v1 = i;
                    v2 = j;
                }
            }
        }
        std::cout << "initial find :" << min << v1 << v2 << std::endl;

        // insert that edge in edges
        edges[0][0] = v1;
        edges[1][0] = v2;
        visited[v1] = visited[v2] = 0;

        // visited array will keep track of min distance from nodes that are already in spanning tree
        for (int i = 0; i < size; i++)
        {
            if (visited[i] != 0)
            {
                if (adjMatrix[i][v1] < adjMatrix[i][v2])
                {
                    visited[i] = v1;
                }
                else
                {
                    visited[i] = v2;
                }
            }
        }
        std::cout << "visited created" << std::endl;

        // repeat
        for (int i = 1; i < size - 1; i++)
        {
            int k, min = I;
            for (int j = 0; j < size; j++)
            {
                if (visited[j] != 0 && adjMatrix[j][visited[j]] < min)
                {
                    k = j;
                    min = adjMatrix[j][visited[j]];
                }
            }
            edges[0][i] = k;
            edges[1][i] = visited[k];
            visited[k] = 0;

            // update visited array to track min cost edges
            for (int j = 0; j < size; j++)
            {
                if (visited[j] != 0 && adjMatrix[j][k] < adjMatrix[j][visited[j]])
                {
                    visited[j] = k;
                }
            }

            // cout<<endl;
            // cout<<i<<edges[0][i]<<edges[1][i];
            // cout<<endl;
        }
        // print edges array
        for (int i = 0; i < size - 1; i++)
        {
            int c = adjMatrix[edges[0][i]][edges[1][i]];
            cout << "[" << edges[0][i] << "]---[" << edges[1][i] << "] cost: " << c << endl;
            sum += c;
        }
        cout << "MST : " << sum << endl;
    }

    // set operations
    int find(int u, int s[])
    {
        int x = u;
        int v = 0;

        while (s[x] > 0)
        {
            x = s[x];
        }
        while (u != x)
        {
            v = s[u];
            s[u] = x;
            u = v;
        }
        return x;
    }

    void unionn(int u, int v, int s[])
    {
        if (s[u] < s[v])
        {
            s[u] += s[v];
            s[v] = u;
        }
        else
        {
            s[v] += s[u];
            s[u] = v;
        }
    }

    void Kruskals()
    {
        int edges[2][size - 1], minCost = 0;
        int visited[size] = {0};
        int set[size + 1];

        int edgeCount = 0;
        while (edgeCount < size - 1)
        {
            int min = I;
            int u = 0, v = 0, k = 0;

            // find the minimum cost edge
            for (int i = 0; i < size; i++)
            {
                for (int j = i; j < size; j++)
                {
                    if (adjMatrix[i][j] < min)
                    {
                        min = adjMatrix[i][j];
                        adjMatrix[i][j] = I;
                        u = i;
                        v = j;
                        k = j;
                    }
                }
            }
            cout << "min" << min << endl;
            edgeCount++;
            // visited[k] = 1;
            cout << min;
        }

        cout << "mst : " << minCost;
    }
};

int main()
{
    cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    Graph g(5);

    g.display();
    g.create();
    g.display();

    g.Kruskals();
    return 0;
}