#include <list>
#pragma once
#define CODE_SIZE 8


class Node {
    
    public:
        unsigned char symb;
	    unsigned char isSymb;
	    unsigned int freq;
        Node(unsigned char symbol, unsigned int count);
        Node(Node *leftChild, Node *rightChild);
        void print()const;
    private:
        Node *left;
        Node *right;
};

bool sortTree(const Node *first, const Node *second);

void makeTree(std::list<Node*>&myTree);