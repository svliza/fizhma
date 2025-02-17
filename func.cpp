#include "func.h"
#include <iostream>
#include <list>

using namespace std;

Node::Node():left(nullptr), right(nullptr){

}

Node::Node(unsigned char symbol, unsigned int count): symb(symbol), freq(count)
{
    isSymb = true;
}

Node::Node(Node *leftChild, Node *rightChild):isSymb(0), left(leftChild), right(rightChild)
{
    freq = leftChild->freq + rightChild->freq;
}

// вывод символа и количества повторений из ноды
void Node::print()const {
    cout << symb << " " << freq << endl;
}


// функция сортировки списка нод
bool sortTree(const Node *first, const Node *second)
{
    return first->freq < second->freq;
}

// вопрос по функции лежит в main
void makeTree(list<Node*> &myTree)
{
    while (myTree.size() > 1)
    {
        myTree.sort(sortTree);
        auto iter = myTree.begin();
        Node *p = new Node(*iter++, *iter);
        myTree.push_back(p);
        myTree.pop_front();
        myTree.pop_front();
    }
    
}
