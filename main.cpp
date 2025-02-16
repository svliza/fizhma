#include <iostream>
#include <fstream>
#include "func.h"
#include <string>

using namespace std;

int main()
{
    string line;
    ifstream fs("file.txt", std::ios::binary);
    if (fs.is_open())
    {
        cout << "ok" << endl;
    }
    if (fs.is_open())
    {
        while (getline(fs, line))
        {
            cout << line << endl;
        }
    }
    
    fs.close();

    return 0;
}