#include <iostream>
using namespace std;

class Node
{
private:
    string place;
    Node *next;

public:
    Node()
    {
        this->place = "";
        next = NULL;
    }

    Node(string place)
    {
        this->place = place;
        next = NULL;
    }

    friend class Graph;
    friend class Stack;

    bool has_next()
    {
        return next != NULL;
    }

    Node *get_next()
    {
        return next;
    }

    void add_next(Node *node)
    {
        this->next = node;
    }
};

class Graph
{
private:
    int nv;

    Node **vertices;

    void dfs_traversal(Node* node, bool is_visited[]){
        int index = get_index(node->place);
        node = vertices[index];


        is_visited[index] = true;

        cout << node->place << " ";

        if(!node->has_next()) return;

        Node* curr = node->get_next();

        

        while(curr != NULL){

            index = get_index(curr->place);


            if(!is_visited[index]){

                dfs_traversal(curr, is_visited);
            }

            curr = curr->get_next();

        }

    }

public:
    Graph()
    {

        cout << "Enter Number of vertices " ;
        cin >> nv;

        cout << endl;

        vertices = new Node *[nv];
    }

    void create()
    {

        // take all places in vertices
        for (int i = 0; i < nv; i++)
        {

            cout << "Enter the name of place ";
            string curr;
            cin >> curr;

            vertices[i] = new Node(curr);
        }

        cout << endl;

        for (int i = 0; i < nv; i++)
        {
            Node* temp = vertices[i];
            Node *curr = vertices[i];

            cout << endl;

            for (int j = 0; j < nv - 1; j++)
            {

                string place;
                cout << "Enter the name of place to which " << temp->place << " is connected " ;
                cin >> place;

                int index = get_index(place);

                if (index == -1)
                {
                    break;
                }

                curr->add_next(new Node(place));
                curr = curr->get_next();
            }
        }
    }

    void bfs()
    {

        string visited[nv];
        int itr = 0;

        for (int i = 0; i < nv; i++)
        {

            Node *curr = vertices[i];

            while (curr != NULL)
            {

                bool is_visited = false;
                for (int i = 0; i < nv; i++)
                {
                    if (curr->place == visited[i])
                    {
                        is_visited = true;
                    }
                }

                if (!is_visited)
                {
                    cout << curr->place << " ";
                    visited[itr] = curr->place;
                    itr += 1;
                }

                curr = curr->get_next();
            }
        }

        cout << endl;
    }

    void dfs(){

        bool is_visited[nv];

        for(int i=0; i<nv; i++){
            is_visited[i] = false;
        }

        dfs_traversal(vertices[0], is_visited);

    }

   

    void display()
    {
        cout << endl;

        for (int i = 0; i < nv; i++)
        {
            Node *curr = vertices[i];

            while (curr != NULL)
            {
                cout << curr->place << " -> ";
                curr = curr->get_next();
            }

            cout << endl;
        }

        cout << endl;
    }

    int get_index(string place)
    {
        for (int i = 0; i < nv; i++)
        {
            Node *curr = vertices[i];
            if (curr->place == place)
                return i;
        }

        return -1;
    }
};

int main()
{

    Graph graph;

    graph.create();

    graph.display();

    // graph.bfs();
    graph.dfs();

    return 0;
}