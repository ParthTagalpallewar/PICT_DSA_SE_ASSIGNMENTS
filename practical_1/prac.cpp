#include<iostream>
using namespace std;

class Node{
    private:
        string key;
        string value;
        Node* left;
        Node* right;
    public:
        Node(){
            key = "";
            value = "";
            left = NULL;
            right = NULL;
        }

        Node(string key, string value){
            this->key = key;
            this->value = value;
            left = NULL;
            right = NULL;
        }

        friend class Dictionary;
};

class Dictionary{
    private:
        Node* root = NULL;

        bool is_left(Node* node, Node* par){

            if(par->left != NULL && par->left == node) return true;
            
            if(par->right != NULL && par->right == node) return false;

            return NULL;

        }

        void asc(Node *node){
            
            if(node == NULL) 
                return;

            asc(node->left);
            cout << node->key << " " << node->value << endl;
            asc(node->right);
        }
        
        void desc(Node* node){
            if (node == NULL)
                return;

            desc(node->right);
            cout << node->key << " " << node->value << endl;
            desc(node->left);
        }

        Node* get_left_most_node(Node* node){
            Node* curr = node;

            while(curr->left != NULL){
                curr = curr->left;
            }

            return curr;
        }
        
        bool search(string key, Node* &node, Node* &par){

            while(node != NULL){

                if(node->key == key) 
                    return true;

                par = node;

                if(key < node->key){
                    node = node->left;
                }else{
                    node = node->right;
                }

            }


            return false;

        }
        
        bool is_leaf_node(Node* node){
            return node->left == NULL && node->right == NULL;
        }
    
    public:
    
        Dictionary()
        {
            this->root = NULL;
        }

        void insert(string key, string value){

            Node* node = new Node(key, value);

            if(root == NULL){
                this->root = node;
                return;
            }

            Node* par = NULL;
            Node* curr = root;

            while(curr != NULL){

                if(key == curr->key){
                    cout << "Duplicate key cant be insert " << endl;
                    return;
                }
                
                if(key < curr->key){
                    par = curr;
                    curr = curr->left;
                }else{
                    par = curr;
                    curr = curr->right;
                }
            }

            if(key < par->key){
                par->left = node;
            }else{
                par->right = node;
            }

        }
        
        void update(string key, string value){

            if(root == NULL){
                cout << "No Data is present" << endl;
                return;
            }

            Node* curr = root;

            while(curr != NULL){

                if(curr->key == key){
                    curr->value = value;
                    cout << "Key " << key << " updated successfully" << endl;
                    return; 
                }

                if(key < curr->key){
                    curr = curr->left;
                }else{
                    curr = curr->right;
                }

            }

            cout << "No key Found" << endl;

        }

        void del(string key ){
            
            if(key == root->key){

                if(root->left == NULL && root->right == NULL){
                    root = NULL;
                    cout << key << " Deleted Successfully" << endl;
                    return;
                }

                if(root->left != NULL && root->right != NULL){

                    Node* left_most = get_left_most_node(root->right);

                    Node* root_left = root->left;

                    left_most->left = root->left;

                    root = root->right;
                    cout << key << " Deleted Successfully" << endl;
                    return;
                }

                if(root->left != NULL){
                    root = root->left;
                    cout << key << " Deleted Successfully" << endl;
                    return;
                }

                if(root->right != NULL){
                    root = root->right;
                    cout << key << " Deleted Successfully" << endl;
                    return;
                }

                return;
            }

            //delete key
            //first key and its parent
            Node* par = NULL;
            Node* node = root;

            bool is_exist =  search(key, node, par);

            cout << node->key << endl;

            if(!is_exist){
                cout << key << " Does not exist" << endl;
                return;
            }

            if (is_leaf_node(node)){

                if(par->left == node) 
                    par->left = NULL;
                else 
                    par->right = NULL;
                return;
            }
       
            if(node->left != NULL && node->right != NULL){

                // first left most node of right size
                Node* left_most = get_left_most_node(node->right);
                Node* left = node->left;


                left_most->left = left;

                if(par->left == node){

                    par->left = node->right;
                    return;

                }

                else{
                    par->right = node->right;
                    return;
                }

            }

            if(node->left != NULL){

                if(par->left == node){
                    par->left = node->left;
                }else{
                    par->right = node->left;
                }
                return;

            }

            if(node->right != NULL){

                if(par->right == node){
                    par->right = node->right;
                }else{
                    par->left = node->right;
                }
                return;
            }
        }

        void print_data(string order){
            cout << endl;
            if(order == "asc"){
                asc(root);
            }else if(order == "man"){
                cout << root->key << endl;
                //level 0
                if(root->left != NULL){
                    cout << root->left->key << endl;
                }
                //level 1
                if (root->left != NULL)
                {
                    cout << "left of " << root->left->key << endl;
                }
                if (root->right != NULL)
                {
                    cout << root->right->left->key << endl;
                }
               
               

               
                
            }
            
            
            else{
                desc(root);
            }
        }
};

int main(){
    int n;
    cin >> n;

    Dictionary dict;

    for(int i=0; i<n; i++){
        string key, value;
        cin >> key >> value;

        dict.insert(key, value);
    }
   
     dict.print_data("asc");
     dict.del("c");
     dict.print_data("man");

    
    
    dict.print_data("asc");





}