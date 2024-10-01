#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <iostream>

template <typename T>
class DoublyList 
{
    private:
        class Node 
        {
            public:
                T val;
                Node* next;
                Node* prev;
                Node(const T& value) : val(value), next(nullptr), prev(nullptr) {}
        };
    private:
        Node* Ptr; 
        int size;
    public:
        DoublyList();
        ~DoublyList();
        bool empty() const;
        int getSize() const;
        void clear();
        void push_back(const T&);
        void pop_back();
        void print() const;
        void makeDecrease();
};

template<typename T>
DoublyList<T>::DoublyList() : Ptr(nullptr), size(0) {}


template<typename T>
DoublyList<T>::~DoublyList() 
{
    clear();
}

template<typename T>
bool DoublyList<T>::empty() const 
{
    return size == 0;
}

template<typename T>
int DoublyList<T>::getSize() const 
{
    return size;
}

template<typename T>
void DoublyList<T>::clear() 
{
    while (!empty()) 
    {
        pop_back();
    }
}

template<typename T>
void DoublyList<T>::push_back(const T& value) 
{
    Node* newNode = new Node(value);
    if (empty()) {
        newNode->next = newNode; 
        newNode->prev = newNode;
        Ptr = newNode;
    } 
    else 
    {
        newNode->next = Ptr->next; 
        newNode->prev = Ptr;       
        Ptr->next->prev = newNode; 
        Ptr->next = newNode;      
        Ptr = newNode;             
    }
    ++size;
}

template<typename T>
void DoublyList<T>::pop_back() 
{
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    Node* tmp = Ptr; 
    if (size == 1) 
    {
        Ptr = nullptr; 
    } 
    else 
    {
        Ptr->prev->next = Ptr->next;
        Ptr->next->prev = Ptr->prev; 
        Ptr = Ptr->prev; 
    }
    delete tmp;
    --size;
}

template<typename T>
void DoublyList<T>::print() const 
{
    if (empty()) 
    {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node* current = Ptr->next;
    do 
    {
        std::cout << current->val << " ";
        current = current->next;
    } while (current != Ptr->next); 
    std::cout << std::endl;
}

template<typename T>
void DoublyList<T>::makeDecrease() {
    if (empty()) return;
    Node* start = Ptr -> next;
    Node* current = Ptr->next;
    Node* temp = nullptr;
    do 
    {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    } while (current != start); 
    Ptr = Ptr->prev;
}
#endif // DOUBLYLIST_H