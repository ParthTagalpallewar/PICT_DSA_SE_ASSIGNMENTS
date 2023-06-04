#include<iostream>
using namespace std;

class Node{
    int data;
    Node* left;
    Node* right;
public:
    Node(){
        data = -1;
        left = NULL;
        right = NULL;
    }

    Node(int data){
        this->data = data;
        left = NULL;
        right = NULL;
    }

    friend class Avl;
};

class Avl{
    Node* root;

    void in_order(Node *t)
    {
        if (t == NULL)
        {
            return;
        }
        in_order(t->left);
        cout << t->data << " ";
        in_order(t->right);
    }

    void preorder(Node *t)
    {
        if (t == NULL)
        {
            return;
        }
        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);
    }

    void postorder(Node *t)
    {
        if (t == NULL)
        {
            return;
        }
        postorder(t->left);
        postorder(t->right);
        cout << t->data << " ";
    }

    Node *insert_node(Node *node, int data)
    {

        if (node == NULL)
        {
            node = new Node(data);
            return node;
        }

        if (data < node->data)
        {
            node->left = insert_node(node->left, data);
            node = balance(node);
        }

        if (data >= node->data)
        {
            node->right = insert_node(node->right, data);
            node = balance(node);
        }

        return node;
    }

    int height(Node *node)
    {
        if (node == NULL)
            return 0;

        int left = height(node->left);
        int right = height(node->right);

        return max(left, right) + 1;
    }

    int diff(Node *node)
    {

        int left = height(node->left);
        int right = height(node->right);

        return left - right;
    }

    // rotations
    Node *rr_rotation(Node *node)
    {

        Node *root = node->right;
        node->right = root->left;
        root->left = node;

        return root;
    }

    Node *ll_rotation(Node *node)
    {
        Node *root = node->left;
        node->left = root->right;
        root->right = node;
        return root;
    }

    Node *lr_rotation(Node *node)
    {

        Node *root = node->left->right;
        Node *left = root->left;
        Node *right = root->right;

        root->left = node->left;
        root->right = node;

        root->left->right = left;
        root->right->left = right;

        return root;
    }

    Node *rl_rotation(Node *node)
    {

        Node *root = node->right->left;
        Node *left = root->left;
        Node *right = root->right;

        root->right = node->right;
        root->left = node;

        root->left->right = left;
        root->right->left = right;

        return root;
    }

    Node *balance(Node *node)
    {

        int bf = diff(node);

        if (bf == 0)
            return node;

        if (bf > 1)
        {

            if (diff(node->left) > 0)
            {
                return ll_rotation(node);
            }
            else
            {
                return lr_rotation(node);
            }
        }

        if (bf < -1)
        {
           
            if (diff(node->right) < 0)
            {
               
                return rr_rotation(node);
            }
            else
            {
                return rl_rotation(node);
            }
        }

        return node;
    }

    public:

    Avl(){
        this->root = NULL;
    }


    void insert(){
        int num;
        cin >> num;

        this->root = insert_node(root, num);
    }

    void traversal(string order){

        cout << endl << " Traversal " << order << endl;

        if(order == "in"){
            this->in_order(this->root);
        }else if(order == "pre"){
            this->preorder(this->root);
        }else{
            this->postorder(this->root);
        }

    }
   
};

int main(){

    int n;
    cin >> n;
    Avl av;
    
    for(int i=0; i<n; i++){
        av.insert();
        av.traversal("in");
        av.traversal("pre");    
    }



}