// Beginning with an empty binary tree, Construct binary tree by inserting the values
// in the order given. After constructing a binary tree perform following operations
// on it-
//  Perform inorder, preorder and post order traversal
//  Change a tree so that the roles of the left and right pointers are swapped at
// every node
//  Find the height of tree
//  Copy this tree to another [operator=]
//  Count number of leaves, number of internal nodes.
//  Erase all nodes in a binary tree.
// (Implement both recursive and non-recursive methods)

//TODO: Need to create copy method using = sign

#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    T arr[100];
    int front;
    int rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }

    bool is_empty()
    {
        return front == -1 || front >= rear;
    }

    bool is_full()
    {
        return front > rear;
    }

    void enqueue(T data)
    {
        if (is_full())
        {
            cout << "Queue is already full" << endl;
            return;
        }

        if (front == -1)
        {
            front = 0;
            rear = 1;
            arr[front] = data;
            return;
        }

        arr[rear] = data;
        rear += 1;
        return;
    }

    T dequeue()
    {

        if (is_empty())
        {
            cout << "Queue is Already Empty" << endl;
            return NULL;
        }

        T data = arr[front];
        front += 1;
        return data;
    }
};

template <class T>
class Stack{
private:
    T arr[100];
    int itr = -1;

public:
    bool is_full(){
        return itr >= (99);
    }

    bool is_empty(){
        return itr == -1;
    }

    void push(T data){

        if(is_full()){
            cout << "stack is already full " << endl;
            return;
        }

        itr += 1;
        arr[itr] = data;
    }

    T pop(){
        if(is_empty()){
            cout << "Stack is Empty " << endl;
            return NULL;
        }

        T data = arr[itr];
        arr[itr] = NULL;
        itr -= 1;
        return data;
    }

};

class Node
{
private:
    int data;
    Node *left;
    Node *right;

public:
    Node()
    {
        data = -1;
        left = NULL;
        right = NULL;
    }

    Node(int data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }

    friend class BinaryTree;
};

class BinaryTree
{
private:
    Node *root;

    void in_order(Node *node)
    {
        if (node == NULL)
            return;
        in_order(node->left);
        cout << node->data << " ";
        in_order(node->right);
    }

    void post_order(Node *node)
    {
        if (node == NULL)
            return;
        post_order(node->left);
        post_order(node->right);
        cout << node->data << " ";
    }

    void pre_order(Node *node)
    {
        if (node == NULL)
            return;
        cout << node->data << " ";
        pre_order(node->left);
        pre_order(node->right);
    }

public:
    BinaryTree()
    {
        root = NULL;
    }

    // Iterative method for creation of binary tree
    void creation()
    {

        int data;
        cout << "Enter Data to be inserted ";
        cin >> data;

        root = new Node(data);
        Queue<Node *> queue;
        queue.enqueue(root);

        while (!queue.is_empty())
        {

            Node *curr = queue.dequeue();

            // check if user want to insert left node
            cout << "Do you want to insert Data to left of " << curr->data << " (Y/N)";
            char input;
            cin >> input;

            if (input == 'Y' || input == 'y')
            {
                cout << "Enter Data ";
                cin >> data;

                Node *left = new Node(data);
                curr->left = left;
                queue.enqueue(left);
            }

            // check if user want to insert right node
            cout << "Do you want to insert Data to right of " << curr->data << " (Y/N)";
            cin >> input;

            if (input == 'Y' || input == 'y')
            {
                cout << "Enter Data ";
                cin >> data;

                Node *right = new Node(data);
                curr->right = right;
                queue.enqueue(right);
            }
        }
    }

    void traversals(string name)
    {

        cout << "Traversal :- ";

        if (name == "in")
        {
            in_order(root);
        }
        else if (name == "pre")
        {
            pre_order(root);
        }
        else
        {
            post_order(root);
        }
        cout << endl;
    }

    void swap()
    {
        Queue<Node *> queue;
        queue.enqueue(root);

        while (!queue.is_empty())
        {

            Node *curr = queue.dequeue();

            // swapping left and right
            if (curr->left != NULL && curr->right != NULL)
            {
                Node *temp = curr->left;
                curr->left = curr->right;
                curr->right = temp;

                queue.enqueue(curr->left);
                queue.enqueue(curr->right);
            }
            else if (curr->left != NULL)
            {
                curr->right = curr->left;
                curr->left = NULL;
                queue.enqueue(curr->right);
            }
            else if (curr->right != NULL)
            {
                curr->left = curr->right;
                curr->right = NULL;
                queue.enqueue(curr->left);
            }
        }
    }

    int height(Node *node)
    {

        if (node == NULL || (node->left == NULL && node->right == NULL))
        {
            return 0;
        }

        int left = 1 + height(node->left);
        int right = 1 + height(node->right);

        return max(left, right);
    }

    Node *get_root()
    {
        return root;
    }

    void count_left_and_internal_nodes(int &leaf, int &internal){
        Queue<Node*> queue;
        queue.enqueue(root);

        while(!queue.is_empty()){

            Node* curr = queue.dequeue();

            if(curr->left != NULL){

                if(curr->left->left == NULL && curr->left->right == NULL){
                    leaf += 1;
                }else{
                    internal += 1;
                }

                queue.enqueue(curr->left);

            }

            if(curr->right != NULL){
                
                if (curr->right->left == NULL && curr->right->right == NULL)
                {
                    leaf += 1;
                }
                else
                {
                    internal += 1;
                }

                queue.enqueue(curr->right);
            }

        }
    }

    void operator=(Node *other)
    {

        Queue<Node *> queue;
        queue.enqueue(root);

        while (!queue.is_empty())
        {
            Node *curr = queue.dequeue();

            Node *new_node = new Node(curr->data);

            if (curr->left != NULL)
            {
                queue.enqueue(curr->left);
            }

            if (curr->right != NULL)
            {
                queue.enqueue(curr->right);
            }
        }
    }

    void erase_all_nodes(Node *node){
        if(node == NULL) return;

        erase_all_nodes(node->left);
        erase_all_nodes(node->right);
        free(node);
    }

    

    void iterative_in_order(){
        Stack<Node*> stack;
        Node* curr = root;
        

        while(!stack.is_empty() || curr != NULL){

            if(curr != NULL){
                stack.push(curr);
                curr = curr->left;
            }

            else{
                curr = stack.pop();
                cout << curr->data << " ";
                curr = curr->right;
            }

        }

        cout << endl;
    }

    void iterative_pre_order(){
        Stack<Node*> stack;
        Node* curr = root;
       
        while(!stack.is_empty() || curr != NULL){
            
            if(curr != NULL){
                cout << curr->data << " ";
                stack.push(curr);
                curr = curr->left;
            }else{
                curr = stack.pop();
                curr = curr->right;
            }
        }
        cout << endl;
    }

    void iterative_post_order(){
        Stack<Node*> stack;
        Node* curr = root;

        int count = 0;

        while(!stack.is_empty() || curr != NULL){

            if(count > 1000) break;

            count += 1;

            if(curr != NULL){

                stack.push(curr);   

                if(curr->right != NULL){
                    curr->right->data *= -1;
                    stack.push(curr->right);
                }

                curr = curr->left;

            }else{

                curr = stack.pop();

                while (!stack.is_empty() && curr->data > 0)
                {
                    cout << curr->data << " ";
                    curr = stack.pop();
                }

                if(stack.is_empty()){
                    cout << curr->data << endl;
                    break;
                }

                if(curr->data < 0){
                    curr->data *= -1;
                    continue;
                }
            }


        }
    }

    void build(){
        root = new Node(20);
        root->left = new Node(10);
        // root->left->left = new Node(5);
        root->left->right = new Node(15);
        root->right = new Node(30);
        root->right->left = new Node(25);
        root->right->right = new Node(35);
    }
};

int main()
{

    BinaryTree btree;

    btree.build();


    // btree.iterative_in_order();
    btree.iterative_post_order();    



    return 0;
}