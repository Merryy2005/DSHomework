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
    DoublyList<int>::Node* ptr = l.getHead();
    ptr = ptr -> next;
    l.insertAfter(ptr , 10);
    l.print();
    l.erase(l.getHead() -> next);
    l.print();
    return 0;
}