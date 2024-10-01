#include <iostream>
#include "DoublyList.hpp" 


int main() {
    DoublyList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    list.print();
    list.makeDecrease();
    list.print();
    return 0;
}
