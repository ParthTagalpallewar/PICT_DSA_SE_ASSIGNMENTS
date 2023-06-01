#include <bits/stdc++.h>
using namespace std;

class Data
{
public:
    int i, j, w;

    Data(int i, int j, int w)
    {
        this->i = i;
        this->j = j;
        this->w = w;
    }
};

Data find_visited_min(int nv, bool visited[], int **graph)
{
    int _min = INT_MAX;
    int _i = 0;
    int _j = 0;

    // iterate over visited array
    for (int i = 1; i <= nv; i++)
    {
        //if current vertex is not visited
        if (visited[i] == false)
            continue;

        // iterate over childs
        for (int j = 1; j <= nv; j++)
        {

            int curr = graph[i][j];

            if (curr == 0 || visited[j])
                continue;

            if (curr < _min)
            {
                _min = curr;
                _i = i;
                _j = j;
            }
        }
    }

    visited[_i] = true;
    visited[_j] = true;

    return Data(_i, _j, _min);
}

int main()
{
    //taking number of verex and edges as input
    int nv, ne;
    cin >> nv >> ne;

    //creating dynamic array
    int **graph;
    graph = new int *[nv + 1];
    for (int i = 0; i <= nv; i++)
    {
        graph[i] = new int[nv + 1];
    }

    //creating graph by taking input form user
    for (int i = 0; i < ne; i++)
    {
        int v, u, w;
        cin >> v >> u >> w;

        graph[v][u] = w;
        graph[u][v] = w;
    }

    //prims started
    bool visited[nv + 1];
    for (int i = 0; i <= nv; i++)
        visited[i] = false;

    //creating graph for storing answers 
    int **ans;
    ans = new int *[nv + 1];
    for (int i = 0; i <= nv; i++)
    {
        ans[i] = new int[nv + 1];
    }
    for (int i = 1; i <= nv; i++)
    {
        for (int j = 1; j <= nv; j++)
        {
            ans[i][j] = 0;
        }
    }
    int mst = 0;

    //for finding each edge
    //as we need to find [number of vertex] - 1
    //we are iterating over for nv-1 times

    visited[1] = true; // as our stating vertex is one we are marking it as true

    for (int e = 0; e < nv - 1; e++)
    {   
        //this function gives min i, j, weight
        Data min_ans = find_visited_min(nv, visited, graph);

        //marking 0 to original graph after finding min edges 
        graph[min_ans.i][min_ans.j] = 0;
        graph[min_ans.j][min_ans.i] = 0;

        //setting weight of i and j after finding min edges that dont form cycle
        ans[min_ans.i][min_ans.j] = min_ans.w;
        ans[min_ans.j][min_ans.i] = min_ans.w;

        //to find total cost
        mst += min_ans.w;
    }
    cout << "------- Mst ----------" << endl;
    for (int i = 1; i <= nv; i++)
    {
        for (int j = 1; j <= nv; j++)
        {
            cout << ans[i][j] << " ";
        }

        cout << endl;
    }

    cout << "sum of all paths " << mst << endl;

    return 0;
}