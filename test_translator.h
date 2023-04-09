#ifndef _TRANSLATOR_H
#define _TRANSLATOR_H

#include <bits/stdc++.h>
using namespace std;

#define WORD_ 101
#define AND_ 102
#define OR_ 103
#define TABLE_ 104

class Node {
    public:
        int nodeType;
        string content;
        Node* left;
        Node* right;
        Node();
        Node(Node*);
};

Node *makeTermNode(char*);
Node *makeAndNode(Node*, Node*);
Node *makeOrNode(Node*, Node*);
Node *makeTree(Node*, Node*);
void printTable(Node*);
void revert(Node*);
void parse(Node*);
Node *get_and(Node*, Node*);

extern FILE *yyin;
extern int yyparse();

#endif