#include <bits/stdc++.h>
using namespace std;

class Node
{
private:
    char data;
    Node *left;
    Node *right;

public:
    Node()
    {
        data = 'z';
        left = NULL;
        right = NULL;
    }

    Node(char a)
    {
        data = a;
        left = NULL;
        right = NULL;
    }

    friend class ExpressionTree;
};

class ExpressionTree
{

private:
    Node *root = NULL;
    map<char, int> priority;

public:
    ExpressionTree()
    {
        priority['+'] = 1;
        priority['-'] = 1;

        priority['*'] = 2;
        priority['/'] = 2;

        priority['^'] = 3;
    }

    void post_order(Node *root)
    {
        if (root == NULL)
            return;

        post_order(root->left);
        post_order(root->right);
        cout << root->data << " ";
    }

    bool is_operator(char data)
    {
        return data == '+' ||
               data == '-' ||
               data == '*' ||
               data == '/';
    }

    Node *build(string &s)
    {

        stack<Node *> nodeStack;
        stack<char> charStack;

        Node *root;

        for (int i = 0; i < s.length(); i++)
        {
            char curr = s[i];

            if (curr == '(')
            {
                charStack.push(curr);
                continue;
            }

            if (curr == ')')
            {
                while (!charStack.empty() && charStack.top() != '(')
                {

                    root = new Node(charStack.top());
                    charStack.pop();

                    Node *left = nodeStack.top();
                    nodeStack.pop();

                    Node *right = nodeStack.top();
                    nodeStack.pop();

                    root->left = right;
                    root->right = left;
                    nodeStack.push(root);
                }

                charStack.pop();
                continue;
            }

            if (is_operator(curr))
            {
                while (
                    !charStack.empty() &&
                    charStack.top() != '(' &&
                    priority[charStack.top()] >= priority[curr])
                {

                    root = new Node(charStack.top());
                    charStack.pop();

                    Node *left = nodeStack.top();
                    nodeStack.pop();

                    Node *right = nodeStack.top();
                    nodeStack.pop();

                    root->left = right;
                    root->right = left;

                    nodeStack.push(root);
                }

                charStack.push(curr);
            }
            else
            {
                root = new Node(curr);
                nodeStack.push(root);
            }
        }

        root = nodeStack.top();
        return root;
    }
};

int main()
{

    string s = "((a+b)*c-e*f)";

    ExpressionTree expTree;

    Node *root = expTree.build(s);

    expTree.post_order(root);
    cout << endl;

    return 0;
}