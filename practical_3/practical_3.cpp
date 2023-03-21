/*
Create an in_ordered threaded binary search tree. Perform in_order, preorder
traversals without recursion and deletion of a node. Analyze time and space
complexity of the algorithm.
*/

#include <iostream>
using namespace std;

class Node
{
private:
    int data = -1;
    bool has_left = false;
    bool has_right = false;
    Node *left = NULL;
    Node *right = NULL;

public:
    Node() {}
    Node(int data)
    {
        this->data = data;
    }

    bool is_left_node()
    {
        return this->has_left == false && this->has_right == false;
    }

    friend class ThreadedBinarySearchTree;
};

class ThreadedBinarySearchTree
{
private:
    Node *dummy = NULL;
    Node *root = NULL;

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

    void delete_root()
    {
        Node *temp = root;

        // root node has no childs (root node is leaf node)
        if (temp->is_left_node())
        {
            root == NULL;
            return;
        }

        // todo: Handle four cases of delete root function
        // 1. if temp is root
        // 2. if temp has only right
        // 3. if temp has only left
        // 4. if temp has both childs
    }

public:
    ThreadedBinarySearchTree()
    {
        dummy = new Node(-99);
    }

    void insert(int data)
    {

        if (root == NULL)
        {
            create(data);
            return;
        }
        Node *new_node = new Node(data);
        Node *temp = root;

        while (temp != dummy)
        {

            if (temp->data == data)
            {
                cout << "Duplicate Node are not allow" << endl;
                return;
            }

            if (data < temp->data)
            {

                if (temp->has_left)
                {
                    temp = temp->left;
                }
                else
                {
                    // configure new_node
                    new_node->left = temp->left;
                    new_node->right = temp;

                    // configure parent node
                    temp->left = new_node;
                    temp->has_left = true;

                    return;
                }
            }
            else
            {

                if (temp->has_right)
                {
                    temp = temp->right;
                }
                else
                {
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

        cout << endl;
    }

    void in_order()
    {
        if (root == NULL)
            return;

        Node *temp = root;
        while (temp != dummy)
        {

            while (temp->has_left)
            {
                temp = temp->left;
            }
            cout << temp->data << " ";

            while (temp->has_right == false)
            {

                temp = temp->right;

                if (temp == dummy)
                {
                    cout << endl;
                    return;
                }
                cout << temp->data << " ";
            }

            if (temp->has_right)
            {
                temp = temp->right;
                continue;
            }
        }

        cout << endl;
    }

    void pre_order()
    {

        if (root == NULL)
        {
            return;
        }

        Node *temp = root;

        while (temp != dummy)
        {

            cout << temp->data << " ";

            while (temp->has_left)
            {
                temp = temp->left;
                cout << temp->data << " ";
            }

            while (temp->has_right == false)
            {
                temp = temp->right;
                if (temp == dummy)
                {
                    cout << endl;
                    return;
                }
            }

            if (temp->has_right)
            {
                temp = temp->right;
            }
        }
        cout << endl;
    }

    void delete_node(int data)
    {
        if (root == NULL)
            return;

        if (root->data == data)
        {
            delete_root();
            return;
        }

        Node *temp = root;

        // todo: handle four condition for delete node
    }
};

int main()
{

    ThreadedBinarySearchTree tbst;

    tbst.insert(20);
    tbst.insert(10);
    tbst.insert(30);
    tbst.insert(5);
    tbst.insert(15);
    tbst.insert(25);
    tbst.insert(35);

    tbst.in_order();

    tbst.pre_order();

    return 0;
}