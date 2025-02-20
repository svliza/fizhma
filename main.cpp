#include <iostream>
#include "func.cpp" 
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <bitset>

#define SIZE 256

using namespace std;


int main()
{
    // Считываем символы в массив
    ifstream fs("cat.bmp", ios::binary);
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
        tree.push_back(p);
    }
    
    // Создаем дерево
    makeTree(tree);
    Node root = *tree.front(); 

    // Сжатие файла
    unordered_map<char, string> huffmanCode; //хэш-таблица кодов
    encode(&root, "", huffmanCode);

  

    fs.seekg(0, ios::beg); 
    string encodeText="";
    for (int i = 0; i < length; ++i)
    {
        unsigned char ch=fs.get();
        encodeText+=huffmanCode[ch];
    }
    fs.close();

    long int finalLenght = encodeText.size();
    
    int padding = 0;
    vector<char> charArray = bitsToChars(encodeText, padding);

    ofstream outputFile("encoded_cat.bmp", ios::binary);
    if (!outputFile.is_open()) {
        return -1;
    }
    // Записываем закодированные данные
    for (char c : charArray) {
        outputFile << c;
    }
    outputFile.close();

    // переводим то, что в .bin файле, обратно в двоичный код
    ifstream fnew("encoded_cat.bmp", ios::binary);
    if (!fnew.is_open())
    {
        return -1;  
    }
    fnew.seekg (0, ios::end);
    long int encodedLenght = fnew.tellg();
    fnew.seekg (0, ios::beg);
    string againBinary = "";
    for (int i = 0; i < encodedLenght; ++i)
    {
        bitset<8>bina(fnew.get());
        againBinary+=bina.to_string<char, char_traits<char>, allocator<char> >();
        
    }
    fnew.close();

    // декодирование
    vector<char> decodedText = decoder(&root, againBinary, finalLenght);

    ofstream decodedFile("new_cat.bmp", ios::binary);
    decodedFile.write(decodedText.data(), decodedText.size()); 
    decodedFile.close();

    return 0;
}