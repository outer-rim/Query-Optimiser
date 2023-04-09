#include "test_translator.h"

Node::Node() : nodeType(-1), left(NULL), right(NULL) {}
Node::Node(Node* node) : nodeType(node->nodeType), content(node->content), left(node->left), right(node->right) {}

Node *makeTermNode(char* s)
{
    Node *node = new Node();
    node->nodeType = WORD_;
    node->content = s;
    return node;
}

Node *makeAndNode(Node* left, Node *right)
{
    Node *node = new Node();
    node->nodeType = AND_;
    node->content = "AND";
    node->left = left;
    node->right = right;
    return node;
}

Node *makeTree(Node* left, Node *right)
{
    Node *node = new Node();
    node->nodeType = TABLE_;
    node->content = "TABLE";
    node->right = right;
    node->left = left;
    return node;
}

void printTable(Node* node)
{
    if(node == NULL) return;
    switch(node->nodeType) {
    case WORD_:
        cout << node->content;
        return;
    case TABLE_:
    case AND_:
        cout << "[ " << node->content << " :: { ";
        printTable(node->left);
        cout << " : ";
        printTable(node->right);
        cout << " } ] ";
        return;
    }
}

void parse(Node* node)
{
    Node *res = new Node();
    Node *temp = get_and(node->left, res);
    *temp = *(node->right);
    cout << endl;
    // printTable(res);
    revert(res);
    return;
}

Node *get_and(Node* node, Node* res)
{
    Node* temp = res;
    if(node->left != NULL) temp = get_and(node->left, temp);
    if(node->right != NULL) temp = get_and(node->right, temp);
    if(node->nodeType != WORD_) return temp;
    temp->nodeType = TABLE_;
    temp->content = "TABLE";
    temp->left = new Node(node);
    temp->right = new Node();
    return temp->right;
}

void revert(Node* node)
{
    if(node->nodeType == TABLE_ && node->right == NULL)
    {
        revert(node->left);
        return;
    }
    if(node->nodeType == TABLE_)
    {
        cout << "SELECT [ ";
        revert(node->left);
        cout << " ] (";
        revert(node->right);
        cout << ")";
    }
    else cout << node->content;
}