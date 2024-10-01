#ifndef DOUBLYLISTITERATOR_H
#define DOUBLYLISTITERATOR_H

#include "DoublyList.hpp"

template <typename T>
class DoublyList;

template <typename T>
class DoublyListIterator
{
    private:
        typename DoublyList<T>::Node* current;
        DoublyList<T>* list;
    public:
        DoublyListIterator(typename DoublyList<T>::Node* node, DoublyList<T>* list);
        T& operator*();
        DoublyListIterator& operator++();
        DoublyListIterator operator++(int);
        DoublyListIterator& operator--();
        DoublyListIterator operator--(int);
        bool isBegin() const; 
        bool isEnd() const;  
};

template<typename T>
DoublyListIterator<T>::DoublyListIterator(typename DoublyList<T>::Node* node, DoublyList<T>* list) 
    : current(node), list(list) {}

template<typename T>
T& DoublyListIterator<T>::operator*() 
{
    return current->val;
}

template<typename T>
DoublyListIterator<T>& DoublyListIterator<T>::operator++() 
{
    current = current->next;
    return *this;
}

template<typename T>
DoublyListIterator<T> DoublyListIterator<T>::operator++(int) 
{
    DoublyListIterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
DoublyListIterator<T>& DoublyListIterator<T>::operator--() 
{
    current = current->prev;
    return *this;
}

template<typename T>
DoublyListIterator<T> DoublyListIterator<T>::operator--(int) 
{
    DoublyListIterator temp = *this;
    --(*this);
    return temp;
}

template<typename T>
bool DoublyListIterator<T>::isBegin() const 
{
    return current == list->head;
}

template<typename T>
bool DoublyListIterator<T>::isEnd() const 
{
    return current == nullptr;
}

#endif // DOUBLYLISTITERATOR_H
