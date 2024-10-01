#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <iostream>

template <typename T>
class DoublyList
{
    private:
        class Node
        {
            private:
                T val;
                Node* next;
                Node* prev;
            public:
                Node();
                Node(const T&);
                ~Node();
            friend class DoublyList;
        };
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
        void eraseByValue(const T&);
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        void print() const;
};

template<typename T>
DoublyList<T>::Node::Node() : val(T()), next(nullptr), prev(nullptr) {}

template<typename T>
DoublyList<T>::Node::Node(const T& val) : val(val), next(nullptr), prev(nullptr) {}

template<typename T>
DoublyList<T>::Node::~Node() {}

template<typename T>
DoublyList<T>::DoublyList() : head(nullptr), tail(nullptr), size(0)
{
}

template<typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& other) : head(nullptr), tail(nullptr), size(0)
{
    Node* current = other.head;
    if (current) 
    {
        do 
        {
            push_back(current->val);
            current = current->next;
        } while (current != other.head);
    }
}

template<typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& other)
{
    if (this != &other) 
    {
        clear();
        Node* current = other.head;
        if (current) 
        {
            do 
            {
                push_back(current->val);
                current = current->next;
            } while (current != other.head);
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
        head->next = head;
        head->prev = head;
    } 
    else 
    {
        newNode->prev = tail;
        newNode->next = head;
        tail->next = newNode;
        head->prev = newNode;
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
        head->next = head;
        head->prev = head;
    } 
    else 
    {
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
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
        tail->next = head;
        head->prev = tail;
        delete tmp;
    }
    --size;
}

template<typename T>
void DoublyList<T>::pop_front()
{
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    if (size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        Node* tmp = head;
        head = head->next;
        tail->next = head;
        head->prev = tail;
        delete tmp;
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
    node->next->prev = newNode;
    node->next = newNode;    
    if (node == tail)
    {
        tail = newNode;
    }
    if (newNode->next == head)
    {
        head = newNode;
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
    Node* tmp = node;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if(node == head)
    {
        head = node-> next;
    }
    if (node == tail) 
    {
        tail = node->prev;
    }
    delete node;
    --size;
}

template<typename T>
void DoublyList<T>::eraseByValue(const T& value)
{
    Node* cur = head;
    int s = size;
    for(int i = 0 ; i < s; i++)
    {
        Node* nxt = cur -> next;
        if(cur -> val == value)
        {
            erase(cur);
        }
        cur = nxt;
    }    
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
    do 
    {
        std::cout << current->val << " ";
        current = current->next;
    } while (current != head);
    std::cout << std::endl;
}

#endif // DOUBLYLIST_H
