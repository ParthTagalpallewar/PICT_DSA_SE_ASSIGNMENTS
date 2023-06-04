#include<iostream>
using namespace std;

class Node{
    int key;
    Node* left;
    Node* right;

    public:
        Node(){
            key = -1;
            left = NULL;
            right = NULL;
        }
        Node(int key){
            this->key = key;
            left = NULL;
            right = NULL;
        }

        friend class Obst;
};

class Obst{

    int n;
    int *key;
    int *success;
    int *failure;
    int **w;
    int **c;
    int **r;
    Node* root;

public:
    Obst()
    {
        cout << "Enter Number of Keys :- ";
        cin >> n;

        key = new int[n];

        cout << "Enter the value of " << n << " keys" << endl;
        for (int i = 0; i < n; i++)
        {
            cin >> key[i];
        }

        success = new int[n];
        cout << "Enter the values of " << n << " Success probabilities" << endl;
        for (int i = 0; i < n; i++)
        {
            cin >> success[i];
        }

        failure = new int[n + 1];
        cout << "Enter the values of " << (n + 1) << " unsuccess probabilities" << endl;
        for (int i = 0; i <= n; i++)
        {
            cin >> failure[i];
        }

        w = new int*[n + 1];
        c = new int*[n + 1];
        r = new int*[n + 1];

        for (int i = 0; i <= n; i++)
        {
            w[i] = new int[n + 1];
            c[i] = new int[n + 1];
            r[i] = new int[n + 1];
        }

        cout << "initialization completed" << endl;
    }

    void construct(){
        for(int i=0; i<n+1; i++){
            w[i][i] = failure[i];
            c[i][i] = 0;
            r[i][i] = 0;

            w[i][i+1] = w[i][i]+success[i]+failure[i+1];
            c[i][i+1] = w[i][i+1];
            r[i][i+1] = i+1;
        }

        for(int ri=2; ri<=n; ri++){
            for(int rj=0; rj<=n-ri; rj++){

                int i = rj;
                int j = ri+rj;
                
                w[i][j] = success[j-1]+failure[j]+w[i][j-1];

                c[i][j] = 9999;
                
                
                for(int k=i+1; k<=j; k++){

                    int cost = c[i][k-1]+c[k][j];

                    if(cost < c[i][j]){
                        c[i][j] = cost;
                        r[i][j] = k;
                    }
                
                }

                c[i][j] += w[i][j];

            }
        }

        cout <<endl<< "Total cost is " << c[0][n] << endl;
        

        root = bst(0, n);
       
    }

    Node* bst(int i, int j){

        if(i >= j) return NULL;
        
        int idx = r[i][j];
        Node *node = new Node(key[idx - 1]);

        node->left = bst(i, idx - 1);
        node->right = bst(idx, j);

        return node;
      
    }

    void in_order(Node* node){
        if(node == NULL) return;

        in_order(node->left);
        cout<<node->key << " ";
        in_order(node->right);
    }

    Node* get_root(){
        return root;
    }
};

int main(){

    Obst obst;
    obst.construct();
    obst.in_order(obst.get_root());

    return 0;
}