#include <iostream>
#include "List.h"

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    List myList(arr, 6);
    std::cout << "Original list: ";
    myList.print();
    myList.BubbleSort();
    std::cout << "Sorted list: ";
    myList.print();
    return 0;
}
