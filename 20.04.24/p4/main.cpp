#include "Polynom.h"
#include <iostream>

int main() {
    int a[] = {3, 2, 1}; 
    Polynom p1(a, 3);
    int b[] = {5 , 4 , 1, 3, 2}; 
    Polynom p2(b, 5);
    std::cout << "Polynomial 1: ";
    p1.print();
    std::cout << "Polynomial 2: ";
    p2.print();
    Polynom result = p1 - p2;
    std::cout << "Result of p1 - p2: ";
    result.print();
    return 0;
}
