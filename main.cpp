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

    
    int padding = 0;
    vector<char> charArray = bitsToChars(encodeText, padding); 
    ofstream outputFile("encoded.txt", ios::out);
   
    outputFile.write(reinterpret_cast<char*>(&padding), sizeof(int));
    outputFile.write(reinterpret_cast<char*>(&length), sizeof(long));
    // Записываем закодированные данные
    outputFile.write(charArray.data(), charArray.size());    
    cout<<" text zakodirovan "<<endl;

    outputFile.close();

    // переводим то что в .bin файле обратно в двоичный код
    ifstream fnew("encoded.txt", ios::out);
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
        bitset<8>bina((char)fnew.get());
        againBinary+=bina.to_string<char, char_traits<char>, allocator<char> >();
        
    }
    cout << againBinary; // строка с двоичным кодом
    fnew.close();

    vector<char> newstring;
    Node mainRoot = root;
    cout << "df" << encodeText.length() << endl;
    for(int i = 0; i < encodeText.length(); i++) {
        if(!root.left && !root.right) {
            newstring.push_back(root.symb);
            root = mainRoot;
            continue;
        }
        if(encodeText[i] == '0') {
            // cout << "ityt";

            root = *root.left;
        }
        else if(encodeText[i] == '1') {
            // cout << "imhere";
            root = *root.right;
        }
    }
    for(int i = 0; i < newstring.size(); i++) {
        cout << newstring[i];
    }

    return 0;

}