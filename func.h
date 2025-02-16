#pragma once
#define CODE_SIZE 8

class Node {
    
    public:
        unsigned char symb;
	    unsigned char isSymb;
	    unsigned int freq;

        Node();
        Node(unsigned char symbol, unsigned int count);
    private:
        Node *left;
        Node *right;
        Node *next;
};