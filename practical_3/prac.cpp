#include<iostream>
using namespace std;

class Node{
    int data;
    Node* left;
    Node* right;
    bool is_left;
    bool is_right;

    public:
        Node(){
            data = -1;
            left = NULL;
            right = NULL;
            is_left = false;
            is_right = false;
        }

        Node(int data)
        {
            this->data = data;
            left = NULL;
            right = NULL;
            is_left = false;
            is_right = false;
        }

        friend class TBST;
};

class TBST{

    Node* head;

    bool search(int data, Node* &curr, Node* &par){

        while(curr != NULL){

            if (curr->data == data)
            {
                return true;
            }

            par = curr;
            if(data < curr->data){

                if(curr->is_left){
                    curr = curr->left;
                }else{
                    return false;
                }

            }

            if (data > curr->data)
            {

                if (curr->is_right)
                {
                    curr = curr->right;
                }
                else
                {
                    return false;
                }
            }
        }

        
        return false;
        


    }

    public:
        Node *root;
        TBST()
        {
            this->root = NULL;

            head = new Node(-1);
            head->left = head;
            head->right = head;
        }

        void insert(){

            int data;
            cout << "Enter Data you wanted to insert :- ";
            cin >> data; 

            cout << data << endl;

            Node* nn = new Node(data);
            
            //if data inserted is root element
            if(root == NULL){

                root = nn;
                root->left = head;
                root->right = head;
                head->is_left = true;

                cout << "Data inserted successfully " << endl;
                return;

            }
           
            Node* par = NULL;
            Node* temp = root;

            while(temp != NULL){
               
                
                if(temp->data == data) {
                    cout << "Duplicate Entry " << endl;
                    return;
                }

                par = temp;
                if(data < temp->data){
                    if(temp->is_left){
                        temp = temp->left;
                    }else{
                        nn->left = par->left;
                        par->left = nn;
                        par->is_left = true;

                        nn->right = par;
                        cout << "Data inserted successfully " << endl;
                        return;
                    }
                }
                else if(data > temp->data){
                    if(temp->is_right){
                        temp = temp->right;
                    }else{
                        nn->right = par->right;
                        par->right = nn;
                        par->is_right = true;

                        nn->left = par;
                        cout << "Data inserted successfully " << endl;
                        return;
                    }
                   
                }

            }
        }

        void in_order(Node* node){
            if(node == NULL) return;
            if(node->is_left)
                in_order(node->left);
            cout << node->data << " .";
            if(node->is_right)
                in_order(node->right);
        }

     
};

int main(){
    int n;
    cin >> n;
    TBST tbst;

    while(n--){
        tbst.insert();
    }

    tbst.in_order(tbst.root);
}

