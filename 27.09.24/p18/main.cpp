#include <iostream>
#include "DoublyList.hpp"

int main()
{
    DoublyList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(1);
    l.push_back(4);
    l.push_back(6);
    l.push_back(1);
    l.push_back(1);
    l.push_back(2);
    l.print();
    l.eraseByValue(1);
    l.print();
    return 0;
}