#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <iostream>
#include "Iterator.hpp"

template <typename T>
class DoublyList
{
    public:
        class Node
        {
            public:
                T val;
                Node* next;
                Node* prev;
            public:
                Node();
                Node(const T&);
                ~Node();
            friend class DoublyList;
            friend class DoublyListIterator<T>;
        };
    private:
        Node* head;
        Node* tail;
        int size; 
    public:
        DoublyList();
        DoublyList(const DoublyList&);
        DoublyList& operator=(const DoublyList&);
        ~DoublyList();
        bool empty() const;
        int getSize() const;
        void clear();
        void push_back(const T&);
        void push_front(const T&);
        void pop_back();
        void pop_front();
        void insert(int, const T&);
        void insertAfter(Node*, const T&);
        void erase(int);
        void erase(Node*);
        Node* getHead();
        Node* getTail();
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        void print() const;
        DoublyListIterator<T> begin();
        DoublyListIterator<T> end();
        friend class DoublyListIterator<T>;
};

template<typename T>
DoublyList<T>::Node::Node() : val(T()), next(nullptr), prev(nullptr) {}

template<typename T>
DoublyList<T>::Node::Node(const T& val) : val(val), next(nullptr), prev(nullptr) {}

template<typename T>
DoublyList<T>::Node::~Node() {}

template<typename T>
DoublyList<T>::DoublyList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& other) : head(nullptr), tail(nullptr), size(0)
{
    Node* current = other.head;
    while (current) 
    {
        push_back(current->val);
        current = current->next;
    }
}

template<typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& other)
{
    if (this != &other) 
    {
        clear();
        Node* current = other.head;
        while (current) 
        {
            push_back(current->val);
            current = current->next;
        }
    }
    return *this;
}

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
    while (size > 0) 
    {
        pop_front();
    }
}

template<typename T>
void DoublyList<T>::push_back(const T& value)
{
    Node* newNode = new Node(value);
    if (empty()) 
    {
        head = newNode;
        tail = newNode;
    } 
    else 
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

template<typename T>
void DoublyList<T>::push_front(const T& value)
{
    Node* newNode = new Node(value);
    if (empty()) 
    {
        head = newNode;
        tail = newNode;
    } 
    else 
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    ++size;
}

template<typename T>
void DoublyList<T>::pop_back()
{
    if (empty()) 
    {
        throw std::out_of_range("List is empty");
    }
    if (size == 1) 
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    } 
    else 
    {
        Node* tmp = tail;
        tail = tail->prev;
        delete tmp;
        tail->next = nullptr;
    }
    --size;
}

template<typename T>
void DoublyList<T>::pop_front()
{
    if (empty()) 
    {
        throw std::out_of_range("List is empty");
    }
    if (size == 1) 
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    } 
    else 
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        head->prev = nullptr; 
    }
    --size;
}

template<typename T>
void DoublyList<T>::insert(int pos, const T& value)
{
    if (pos < 0 || pos > size) 
    {
        throw std::out_of_range("Invalid position");
    }
    if (pos == 0) 
    {
        push_front(value);
    } 
    else if (pos == size) 
    {
        push_back(value);
    } 
    else 
    {
        Node* current = head;
        for (int i = 0; i < pos - 1; ++i)
        {
            current = current->next;
        }
        insertAfter(current, value);
    }
}

template<typename T>
void DoublyList<T>::insertAfter(Node* node, const T& value)
{
    if (node == nullptr) 
    {
        throw std::invalid_argument("Node cannot be null");
    }
    Node* newNode = new Node(value);
    newNode->next = node->next; 
    newNode->prev = node; 
    if (node->next)
    {
        node->next->prev = newNode;
    }
    node->next = newNode;    
    if (node == tail)
    {
        tail = newNode;
    }
    ++size;
}

template<typename T>
void DoublyList<T>::erase(int pos)
{
    if (pos < 0 || pos >= size) 
    {
        throw std::out_of_range("Invalid position");
    }

    if (pos == 0) 
    {
        pop_front();
    } 
    else if (pos == size - 1) 
    {
        pop_back();
    } 
    else 
    {
        Node* current = head;
        for (int i = 0; i < pos; ++i)
        {
            current = current->next;
        }
        erase(current);
    }
}

template<typename T>
void DoublyList<T>::erase(Node* node)
{
    if (node == nullptr) 
    {
        throw std::invalid_argument("Node cannot be null");
    }
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }
    if(node == head)
    {
        head = node->next;
    }
    if (node == tail) 
    {
        tail = node->prev;
    }
    delete node;
    --size;
}

template<typename T>
typename DoublyList<T>::Node* DoublyList<T>::getHead()
{
    return head;
}

template<typename T>
typename DoublyList<T>::Node* DoublyList<T>::getTail()
{
    return tail;
}

template<typename T>
T& DoublyList<T>::front()
{
    if (empty()) 
    {
        throw std::out_of_range("List is empty");
    }
    return head->val;
}

template<typename T>
const T& DoublyList<T>::front() const
{
    if (empty()) 
    {
        throw std::out_of_range("List is empty");
    }
    return head->val;
}

template<typename T>
T& DoublyList<T>::back()
{
    if (empty()) 
    {
        throw std::out_of_range("List is empty");
    }
    return tail->val;
}

template<typename T>
const T& DoublyList<T>::back() const
{
    if (empty()) 
    {
        throw std::out_of_range("List is empty");
    }
    return tail->val;
}

template<typename T>
void DoublyList<T>::print() const
{
    if (empty()) 
    {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node* current = head;
    while (current) 
    {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
DoublyListIterator<T> DoublyList<T>::begin() {
    return DoublyListIterator<T>(head , this);
}

template<typename T>
DoublyListIterator<T>  DoublyList<T>::end() {
    return DoublyListIterator<T>(tail, this);
}

#endif // DOUBLYLIST_H
