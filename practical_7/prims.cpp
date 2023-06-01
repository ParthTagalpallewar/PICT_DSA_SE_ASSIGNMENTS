#include<iostream>
using namespace std;

class Graph{

    int nv;
    int ne;

    int** graph;

public:

    Graph(){
        graph = NULL;
    }

    Graph(int n){
        nv = n;
        graph = new int*[n+1];

        for(int i=0; i<n; i++){
            graph[i] = new int[nv];
        }
    }

    void create(){
        cout << "Enter number of edges" << endl;
        cin >> ne;

        for(int i=0; i<ne; i++){
            cout << "Enter Source Destination and Weight" << endl;
            int u, v, w;
            cin >> u >> v >> w;

            graph[u][v] = w;
            graph[v][u] = w;
        }
    }

    void prims(){




    }

};


int main(){

    return 0;
}