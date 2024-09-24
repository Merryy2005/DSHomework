#include <iostream>
#include "List.h"

int main()
{
    int arr[] = {5,4,2,1,2}; 
    List myList(arr, 5);
    std::cout << "Original list: ";
    myList.print(); 
    myList.AddElem(3);
    std::cout << "After adding : ";
    myList.print();
    myList.AddElem(3);
    std::cout << "After adding : ";
    myList.print();
    myList.AddElem(1);
    std::cout << "After adding : ";
    myList.print();
    myList.AddElem(2);
    std::cout << "After adding : ";
    myList.print();
    myList.AddElem(10);
    std::cout << "After adding : ";
    myList.print();
    return 0;
}
