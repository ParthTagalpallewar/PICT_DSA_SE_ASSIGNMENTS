/*
Aim: -
 Create Dictionary,
 Insert
 Delete
 Update
 Traversal
 Search Keyword and count comparision

 Do all this using BST
*/
#include <bits/stdc++.h>
using namespace std;

class Node
{
private:
string word;
string meaning;
Node* left;
Node* right;

public:
Node(){
    this->word = "";
    this->meaning = "";
    left = NULL;
    right = NULL;
}

Node(string word, string meaning){
    this->word = word;
    this->meaning = meaning;
    left = NULL;
    right = NULL;
}

friend class BST;
};

class BST{
private:
    Node* root;

    void in_order(Node* node){
        if(node == NULL) return;
        in_order(node->left);
        cout << node->word << ": " << node->meaning << " ";
        in_order(node->right);
    }

    void post_order(Node* node){
        if(node == NULL) return;
        post_order(node->left);
        post_order(node->right);
        cout << node->word << ": " << node->meaning << " ";
    }

    bool is_left(Node* current, Node* parent){

        if (parent->left != NULL && parent->left->word == current->word)
        {
           return true;
        }

        if (parent->right != NULL && parent->right->word == current->word)
        {
           return false;
        }

        cout << "Both left and right not exist returning null " << endl;
        return NULL;
    }
    

public:
BST(){
    root = NULL;
}

void insert(string word, string meaning){
    Node* new_node = new Node(word, meaning);

    if(root == NULL){
        root = new_node;
        return;
    }
    
    Node* current = root;
    while(current != NULL){
        if (current->word > word)
        {
            if (current->left == NULL)
            {
                current->left = new_node;
                return;
            }

            current = current->left;
        }
        else
        {
            if (current->right == NULL)
            {
                current->right = new_node;
                return;
            }

            current = current->right;
        }
    }
    

}

void traversals(string name){
    if(name == "ascending"){
        in_order(root);
    }else{
        post_order(root);
    }
    cout << endl;
}

void update(string word, string meaning){
    Node* current = root;
    while(current != NULL){
        if(current->word == word){
            current->meaning = meaning;
            return;
        }

        if(word < current->word)
        {
            current = current->left;
        }else{
            current = current->right;
        }
    }
}

void delete_node(string word){
    Node* parent = NULL;
    Node* current = root;

    while(current != NULL){

        if(word < current->word){
            parent = current;
            current = current->left;
        }

        if(word > current->word){
            parent = current;
            current = current->right;
        }

        else{

            // case 1: current node is leaf node
            if(current->left == NULL && current->right == NULL){
                if(is_left(current, parent)){
                    parent->left = NULL;
                }else{
                   parent->right = NULL;
                }
                return;
            }
            //if both childs are exists
            if(current->left != NULL && current->right != NULL){

                //check if element exist at left or right side of parent
                Node* current_right = current->right;
                Node* right_short = current_right;
                while(right_short -> left != NULL){
                    right_short = right_short->left;
                }

                right_short->left = current->left;

                if (is_left(current, parent))
                {
                    parent->left = current->right;
                }
                else
                {
                    parent->right = current->right;
                }
            }
            //if left child exists
            else if(current->left != NULL){
                if (is_left(current, parent))
                {
                    parent->left = current->left;
                }
                else
                {
                    parent->right = current->left;
                }
            }
            //if right child exists
            else{
                
                if (is_left(current, parent))
                {
                    parent->left = current->right; 
                }
                else
                {
                    parent->right = current->right;
                }
            }
            
            return;
        }

    }
}

int search(string word){
    int counts = 0;

    Node* current = root;
    while(current != NULL){

        counts += 1;

        if(current->word == word){
            return counts;
        }

        if(word < current->word){
            current = current->left;
        }else{
            current = current->right;
        }
    }

    return counts;
    
}

};

int main(){

    BST bst;
    bst.insert("d", "");

    bst.insert("b", "");
   
    bst.insert("f", "");
   
    bst.insert("a", "");
    bst.insert("c", "");
    bst.insert("e", "");
    bst.insert("g", "");

    bst.traversals("ascending");

    bst.update("a", "A");

    bst.traversals("descending");

    cout << bst.search("g") << endl;

    bst.delete_node("b");

    bst.traversals("ascending");



}