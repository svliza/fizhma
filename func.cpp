#include "func.h"
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

using namespace std;

Node::Node():left(nullptr), right(nullptr){

}

Node::Node(unsigned char symbol, unsigned int count) : symb(symbol), freq(count), isSymb(true), left(nullptr), right(nullptr) {}

Node::Node(Node *leftChild, Node *rightChild) : isSymb(false), left(leftChild), right(rightChild) {
    freq = leftChild->freq + rightChild->freq;
}
    
// Вывод символа и количества повторений из ноды
void Node::print() const {
    cout << symb << " " << freq << endl;
}

// Функция сортировки списка нод
bool sortTree(const Node *first, const Node *second) {
    return first->freq < second->freq;
}

void makeTree(list<Node*> &myTree)
{
    while (myTree.size() > 1)
    {
        myTree.sort(sortTree);
        auto iter = myTree.begin();
        Node *p = new Node(*iter, *++iter);
        myTree.push_back(p);
        myTree.pop_front();
        myTree.pop_front();
    }
}

//Шифрование текста
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
	if (!root->left && !root->right) {
		huffmanCode[root->symb] = str;
        return;
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
