#include <iostream>
#include <fstream>
#include "func.cpp" 
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#define SIZE 256

using namespace std;

int main()
{
    // Считываем символы в массив
    ifstream fs("file.txt", ios::binary);
    if (!fs.is_open())
    {
        return -1;  
    }
    fs.seekg(0, ios::end);
    long length = fs.tellg();
    fs.seekg(0, ios::beg);
    
    unsigned int freq[SIZE] = {0};
    for (int i = 0; i < length; ++i)
    {
        freq[(unsigned char)fs.get()] ++;
    }
    

    // Создаем список с символами
    list<Node*> tree;
    for (int i = 0; i < SIZE; ++i) {
    if (freq[i] == 0) continue;
    Node* p = new Node((unsigned char)i, freq[i]);
    tree.push_back(p);}

    // Создаем дерево
    makeTree(tree);
    cout << tree.front()->freq<<endl;
    Node* root = tree.front();

    // Сжатие файла
    unordered_map<char, string> huffmanCode; //хэш-таблица кодов
    encode(root, "", huffmanCode);
    
    fs.seekg(0, ios::beg); 
    string encodeText="";
    for (int i = 0; i < length; ++i)
    {
        unsigned char ch=fs.get();
        encodeText+=huffmanCode[ch];
    }
    fs.close();

    int padding = 0;
    vector<char> charArray = bitsToChars(encodeText, padding); 
    ofstream outputFile("encoded.bin", ios::binary);
    
   
    outputFile.write(reinterpret_cast<char*>(&padding), sizeof(int));
    outputFile.write(reinterpret_cast<char*>(&length), sizeof(long));
    // Записываем закодированные данные
    outputFile.write(charArray.data(), charArray.size());    
    std::cout<<" text zakodirovan "<<std::endl;

    outputFile.close();

    return 0;

}

