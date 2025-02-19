#include <iostream>
#include <fstream>
#include "func.cpp"
#include "func.cpp" 
#include <string>
#include <list>
#include <list>
#include <vector>
#include <unordered_map>
#define SIZE 256

using namespace std;

int main()
{
    // считываем символы в массив
    ifstream fs("file.txt", ios::binary);
    if (!fs.is_open())
    {
        return -1;  
    }
    fs.seekg (0, ios::end);
    long length = fs.tellg();
    fs.seekg (0, ios::beg);
    int freq[SIZE]={0};
    for (int i = 0; i < length; ++i)
    {
        freq[(unsigned char)fs.get()] ++;
    }
    fs.close();
    


    // создаем список с символами
    list<Node*> tree;
    for(int i = 0; i < SIZE; ++i) {
        if(freq[i] == 0) continue;
        Node *p = new Node((unsigned char)i, freq[i]);
        tree.push_back(p);
    }
    
    // создаем дерево
    makeTree(tree);
    // бля я ебал:
    // 
    // 2. В makeTree два pop_front надо заменить на erase  (в общем и целом необходимо удалять два первых элемента), но я хз как, оно не работает в закомментированной строке 
    // 3. Ну и надо понять что хранить в private а что в public

    
    return 0;
}