#include "func.cpp" 
#include <iostream>
#include <fstream>
#include "func.h"
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <sstream> 

#define SIZE 256

using namespace std;

int main() {
    // Считываем символы в массив
    ifstream fs("file.txt"); // Текстовый файл
    if (!fs.is_open()) {
        cerr << "Ошибка открытия file.txt" << endl;
        return -1;
    }

    string fileContent((istreambuf_iterator<char>(fs)),
                       (istreambuf_iterator<char>()));
    fs.close();
    long length = fileContent.length();


    unsigned int freq[SIZE] = {0};
    for (char c : fileContent) {
        freq[(unsigned char)c]++;
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
    Node* root = tree.front(); 

    // Сжатие файла
    unordered_map<char, string> huffmanCode; //хэш-таблица кодов
    encode(root, "", huffmanCode);


    string encodeText = "";
    for (char c : fileContent) {
        encodeText += huffmanCode[c];
    }


    int padding = 0;
    vector<char> charArray = bitsToChars(encodeText, padding);


    ofstream outputFile("encoded.txt"); // Текстовый файл
    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия encoded.txt" << endl;
        return -1;
    }

    // Записываем padding и length в файл
    outputFile << padding << endl;
    outputFile << length << endl;

    // Записываем закодированные данные
    for (char c : charArray) {
        outputFile << c;
    }
    cout << "Текст закодирован" << endl;
    outputFile.close();

    // === Декодирование ===
    ifstream fnew("encoded.txt"); // Текстовый файл
    if (!fnew.is_open()) {
        cerr << "Ошибка открытия encoded.txt" << endl;
        return -1;
    }

    int readPadding;
    long readLength;
    string line;

    getline(fnew, line);
    readPadding = stoi(line);

    getline(fnew, line);
    readLength = stoi(line);

    string encodedText;
    while (getline(fnew, line)) {
        encodedText += line;
    }
    fnew.close();

    // Преобразуем байты в битовую строку
    string againBinary = "";
    for (char byte : encodedText) {
        bitset<8> bina(byte);
        againBinary += bina.to_string();
    }

    // Обрезаем padding
    if (readPadding > 0) {
        againBinary = againBinary.substr(0, againBinary.length() - readPadding);
    }
    // cout << "Binary string: " << againBinary << endl;
    vector<char> decodedText = decoder(root, againBinary, againBinary.length());

    cout << "Decoded text: ";
    for (char c : decodedText) {
        cout << c;
    }
    cout << endl;


    ofstream decodedFile("new.txt"); // Текстовый файл
    if (!decodedFile.is_open()) {
        cerr << "Ошибка открытия new.txt" << endl;
        return -1;
    }

    decodedFile.write(decodedText.data(), decodedText.size());
    decodedFile.close();

    
    
    return 0;
}