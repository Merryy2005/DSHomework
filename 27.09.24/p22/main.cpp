#include <iostream>
#include "DoublyList.hpp" 
#include "Iterator.hpp"

int main() {
    DoublyList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    
    for(DoublyListIterator<int> it = list.begin(); !it.isEnd() ; ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
