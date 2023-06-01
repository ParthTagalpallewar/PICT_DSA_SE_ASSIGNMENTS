#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int i, j, w;

    Edge(){
        this->i = 0;
        this->j = 0;
        this->w = 0;
    }

    Edge(int i, int j, int w)
    {
        this->i = i;
        this->j = j;
        this->w = w;
    }
};
void sortt(Edge *edges, int ne)
{
    for (int i = 0; i < ne; i++)
    {
        Edge min = edges[i];
        int min_i = i;


        for (int j = i + 1; j < ne; j++)
        {
            if (edges[j].w < min.w)
            {
                min = edges[j];
                min_i = j;
            }
        }

        // swap
        Edge temp = edges[i];
        edges[i] = edges[min_i];
        edges[min_i] = temp;
    }
}
Edge find_min_edge_no_cycle(int visited[], Edge* edges, int ne){

    sortt(edges, ne);

    //iterate over edges
    for(int i=0; i<ne; i++){

        Edge curr = edges[i];

        if(visited[curr.i] == visited[curr.j]) continue;

        int temp = i;
        while(visited[temp] != temp){
            temp = visited[temp];
        }
        edges[i].w = 999;
        visited[curr.j] = temp;        

        return curr;                               

    }

    return Edge(0, 0, 0);

}



int main()
{
    // taking number of vertex and edges as input
    int nv, ne;
    cin >> nv >> ne;

    // creating dynamic array
    int **graph;
    Edge* edges;

    graph = new int *[nv + 1];
    edges = new Edge[nv];
    for (int i = 0; i <= nv; i++)
    {
        graph[i] = new int[nv + 1];
    }

    // creating graph by taking input form user
    for (int i = 0; i < ne; i++)
    {
        int v, u, w;
        cin >> v >> u >> w;

        graph[v][u] = w;
        graph[u][v] = w;

        edges[i] = Edge(u, v, w);
    }

    // kruskals started
    int visited[nv + 1];
    for (int i = 0; i <= nv; i++)
        visited[i] = i;

    // creating graph for storing answers
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

    // for finding each edge
    // as we need to find [number of vertex] - 1
    // we are iterating over for nv-1 times
    int arr[ne];

    for (int e = 0; e < nv - 1; e++)
    {
        Edge min = find_min_edge_no_cycle(visited, edges, ne);
        cout << " Min (" << min.i << ", " << min.j << ", " << min.w << " )" <<endl;
        ans[min.i][min.j] = min.w;
        ans[min.j][min.i] = min.w;

        mst += min.w;

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