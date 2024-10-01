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
    l.print();
    l.insert(0,5);
    l.print();
    l.insert(4,6);
    l.print();
    l.erase(3);
    l.print();
    return 0;
}