#include<iostream>
using namespace std;

class Node{
    private:
    int data = -1;
    bool has_left = false;
    bool has_right = false;
    Node* left = NULL;
    Node* right = NULL;

    public:
    Node(){}
    Node(int data){
        this->data = data;
    }
    friend class ThreadedBinarySearchTree;
};

class ThreadedBinarySearchTree{
    private:
    Node* dummy = NULL;
    Node* root = NULL;

    void create(int data)
    {
        // created new Node
        root = new Node(data);
        root->left = dummy;
        root->right = dummy;

        // changes in dummy node
        dummy->left = root;
        dummy->has_left = true;
    }

    public:

    ThreadedBinarySearchTree(){
        dummy = new Node(-99);
    }

    void insert(int data){
        // int data;
        // cout << "Enter Data to be inserted ";
        // cin >> data;

        if(root == NULL){
             create(data);
             return;
        }
        Node *new_node = new Node(data);
        Node* temp = root;

        while(temp != NULL){

            if(temp->data == data){
                cout << "Duplicate Node are not allow" << endl;
                return;
            }

            if(temp->data < data){

                if(temp->left != NULL){
                    temp = temp->left;
                }else{
                    //configure new_node
                    new_node->left = temp->left;
                    new_node->right = temp;

                    //configure parent node
                    temp->left = new_node;
                    temp->has_left = true;
                    return;
                }
            }else{

                if(temp->right != NULL){
                    temp = temp->right;
                }else{
                    // configure new_node
                    new_node->right = temp->right;
                    new_node->left = temp;

                    // configure parent node
                    temp->right = new_node;
                    temp->has_right = true;
                    return;
                }


            }

        }

        
    }

    void in_order(){
        if(root == NULL) return;
        
        int count = 0;

        Node* temp = root;
        while(temp != dummy){

            cout << "inside while" << endl;
            count += 1;

            if(count > 10){
                return;
            }

            while(temp->has_left){
                temp = temp->left;
            }
            cout << " hello" << endl;
            cout << "printing" << temp->data << " ";

            if(temp->has_right){
                temp = temp->right;
                continue;
            }

            while(temp->has_right == false){

                temp = temp->right;

                if(temp == dummy) return;

                cout << temp->data << " ";

            }
        }
    }

    
};

int main(){

    ThreadedBinarySearchTree tbst;


    tbst.insert(20);
    tbst.in_order();



    return 0;
}