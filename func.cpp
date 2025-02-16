#include "func.h"
#include <iostream>
#include <list>

using namespace std;

Node::Node(){

}

Node::Node(char symbol, unsigned int count)
{
    symb = (unsigned char)symbol;
    freq = count;
}
