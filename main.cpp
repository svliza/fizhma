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
    cout << "encoded text" << encodeText;
    fs.close();

    int padding = 0;
    
    vector<char> charArray = bitsToChars(encodeText, padding); 

    fstream outputFile("encoded.bin", ios::binary);
    
   
    outputFile.write(reinterpret_cast<char*>(&padding), sizeof(int));
    outputFile.write(reinterpret_cast<char*>(&length), sizeof(long));
    // Записываем закодированные данные
    outputFile.write(charArray.data(), charArray.size());    
    std::cout<<" text zakodirovan "<<std::endl;
    outputFile.close();



    // переводим то что в .bin файле обратно в двоичный код
    ifstream fnew("encoded.bin", ios::binary);
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

    // fstream decodedFile("new.txt", ios::binary);

    // vector<char> decodedText = decoder(root, encodeText);
    // for(int i = 0; i < decodedText.size(); i++) {
    //     cout << decodedText[i];
    // }


    vector<char> newstring;
    Node* mainRoot = root;
    cout << "df" << encodeText.length() << endl;
    for(int i = 0; i < encodeText.length(); i++) {
        if(!root->left && !root->right) {
            newstring.push_back(root->symb);
            root = mainRoot;
            continue;
        }
        if(encodeText[i] = '0') {
            root = root->left;

        }
        else {
            root = root->right;
        }
    }

    return 0;
}