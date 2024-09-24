#include <iostream>
#include "List.h"

int main()
{
    int arr[] = {5, 5 , 3, 8, 3, 1, 4, 3, 5, 1}; 
    List myList(arr, 10);
    std::cout << "Original list: ";
    myList.print(); 
    myList.RemoveRepetitives();
    std::cout << "After removing duplicates: ";
    myList.print();
    return 0;
}
