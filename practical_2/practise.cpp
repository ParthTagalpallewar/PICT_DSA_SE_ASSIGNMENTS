#include<iostream>
using namespace std;



template<class T>
class Queue{
private:
    T* arr;
    int front = -1;
    int rear = -1;
public:

    Queue(int size){
        arr = new T[size];
    }

    bool is_empty(){
        if(front == -1 && rear == -1) 
            return true;
        
        if(front > rear)
            return true;

        return false;
        
    }

    void enqueue(T data){
        if(rear == -1){
            front += 1;
        }

        rear += 1;
        arr[rear] = data;
        return;
    }
    
    T dequeue(){
        front += 1;
        return arr[front-1];
    }

    void print(){

        for(int i=front; i<=rear; i++){
            cout << "data" <<  arr[i] << endl;
        }
    }

};

class Node
{
private:
    int data;
    Node *left;
    Node *right;

public:
    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }

    friend class Queue<Node*>;
    friend class BinaryTree;
};

class BinaryTree{
    Node* root;

    void in_order(Node* node){
        if(node == NULL) return;

        in_order(node->left);
        cout << node->data << " ";
        in_order(node->right);
    }

    void pre_order(Node *node)
    {
        if (node == NULL)
            return;

        cout << node->data << " ";

        pre_order(node->left);
        pre_order(node->right);
    }

    void post_order(Node *node)
    {
        if (node == NULL)
            return;

        post_order(node->left);
        post_order(node->right);

        cout << node->data << " ";
    }

    public:
        BinaryTree(){
            this->root = NULL;
        }

        Node* get_root(){
            return this->root;
        }

        void create(){

            Queue<Node*> q(10e5); 

            cout << "Enter Root of tree" << endl;
            int rk;
            cin >> rk;

            root = new Node(rk);

            q.enqueue(root);

            while(!q.is_empty()){

                Node* curr = q.dequeue();

                char ans;
                cout << "Do you want to insert key in left of " << curr->data << ":- " << endl;
                cin >> ans;

                if(ans == 'Y'){
                    cout << " Enter key to insert :- "; 
                    int data;
                    cin >> data;
                    
                    Node* left = new Node(data);
                    curr->left = left;
                    q.enqueue(left);
                }

                cout << "Do you want to insert key in right of " << curr->data << ":- " << endl;
                cin >> ans;

                if (ans == 'Y')
                {
                    cout << " Enter key to insert :- ";
                    int data;
                    cin >> data;

                    Node *right = new Node(data);
                    curr->right = right;
                    q.enqueue(right);
                }
            }

            cout << "Tree Created Successfully"<<endl;
        }

        void print(string order){
            cout << "Traversal :- " << order << endl; 
            if(order == "asc"){
                in_order(root);
            }

            cout << endl;
        }

        void swap(Node* node){
            if(node == NULL) return;

            Node* lchild = node->left;
            Node* rchild = node->right;

            node->left = rchild;
            node->right = lchild;

            swap(node->left);
            swap(node->right);
        }
};

int main()
{

    BinaryTree bt;

    bt.create();

    bt.print("asc");
    bt.swap(bt.get_root());
    bt.print("asc");
    

    return 0;
}