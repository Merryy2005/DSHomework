#include <iostream>
#include "List.h"

int main()
{
    int arr[] = {8 , 5, 5 , 3, 8, 3, 1, 4, 3, 8, 1}; 
    List myList(arr, 11);
    std::cout << "Original list: ";
    myList.print(); 
    myList.RemoveMaximums();
    std::cout << "After removing Maximums: ";
    myList.print();
    return 0;
}
