#include <iostream>
#include <fstream>
#include "func.h"
#include <string>

#define SIZE 256

using namespace std;

int main()
{
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
    return 0;
}