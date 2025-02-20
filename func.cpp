#include "func.h"
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

Node::Node():left(nullptr), right(nullptr) {}

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
        auto iter1 = myTree.begin();
        Node* left = *iter1;
        myTree.pop_front();
        auto iter2 = myTree.begin();
        Node* right = *iter2;
        myTree.pop_front();
        Node *p = new Node(left, right); 
        myTree.push_back(p);
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

//функция перевода бит в символы
vector<char> bitsToChars(const string& bitString, int& padding) {
    size_t bitStringLength = bitString.length();
    padding = 0;
    // Создаем копию строки для добавления padding
    string paddedBitString = bitString;
    if (bitStringLength % 8 != 0) {
        padding = 8 - (bitStringLength % 8);
        for (int i = 0; i < padding; ++i) {
            paddedBitString += '0';
        }
    }

    size_t charCount = paddedBitString.length() / 8;
    vector<char> result(charCount);

    for (size_t i = 0; i < charCount; ++i) {
        unsigned char byte = 0;
        for (int j = 0; j < 8; ++j) {
            if (paddedBitString[i * 8 + j] == '1') {
                byte |= (1 << (7 - j));
            }
        }
        result[i] = static_cast<char>(byte);
    }

    return result;
}

vector<char> decoder(Node *root, string bin, int len) {
    vector<char> newstring;
    Node mainRoot = *root;
    for(int i = 0; i <= len; i++) {
        if(!root->left && !root->right) {
            newstring.push_back(root->symb);
            root = &mainRoot;
            i-=1;
            continue;
        }
        if(bin[i] == '0') {
            root = root->left;
        }
        if(bin[i] == '1') {
            root = root->right;
        }
    }
    return newstring;
}