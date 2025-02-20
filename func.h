#pragma once
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#define CODE_SIZE 8


class Node {
public:
    unsigned char symb;       // Символ
    bool isSymb;             // Указывает, является ли узел символом
    unsigned int freq;       // Частота символа
    
    Node();
    Node(unsigned char symbol, unsigned int count);
    Node(Node *leftChild, Node *rightChild);
    void print() const;
    Node *left;              // Левый дочерний узел
    Node *right;             // Правый дочерний узел
};

bool sortTree(const Node *first, const Node *second);

void makeTree(std::list<Node*>& myTree);

void encode(Node* root, std::string str, std::unordered_map<unsigned char, std::string>& huffmanCode);

// vector<char> bitsToChars(string& bitString, int& padding);

// vector<char> decoder(Node *root, string bin);