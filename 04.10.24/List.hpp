#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <vector>

namespace mystl
{
    template<typename T>
    class List
    {
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
            friend class List;
        };
        private:
            Node* head;
            Node* tail;
        public:
            List();
            List(const List&);
            List(List&&);
            List& operator=(const List&);
            List& operator=(List&&);
            T& front();
            const T& front() const;
            T& back();
            const T& back() const;
            bool empty() const noexcept;
            void clear() noexcept;
            std::size_t size() const;
            void push_back(const T&);
            void pop_back();
            void push_front(const T&);
            void pop_front();
            void insert(std::size_t , const T&);
            void erase(std::size_t);
            void print() const;
            void createLoop(std::size_t);
            bool hasLoop() const;
            void reverseList();
            const T& findNthlastElem(std::size_t) const;
            T& begin() noexcept;
            const T& begin() const noexcept;
            const T& cbegin() const noexcept;
            ~List();
    };
}

template<typename T>
mystl::List<T>::Node::Node() : val(T()) , next(nullptr) , prev(nullptr)
{

}

template<typename T>
mystl::List<T>::Node::Node(const T& val) : val(val) , next(nullptr) , prev(nullptr)
{

}

template<typename T>
mystl::List<T>::Node::~Node()
{

}

template<typename T>
mystl::List<T>::List() : head(nullptr) , tail(nullptr)
{

}

template<typename T>
mystl::List<T>::List(const List<T>& other) : head(nullptr) , tail(nullptr)
{
    Node* cur = other.head;
    while (cur) 
    {
        push_back(cur->val);
        cur = cur -> next;
    }
}

template<typename T>
mystl::List<T>::List(List<T>&& other) : head(other.head) , tail(other.tail)
{
    other.head = nullptr;
    other.tail = nullptr;
}

template<typename T>
mystl::List<T>& mystl::List<T>::operator=(const List<T>& other)
{
    if(this != &other)
    {
        clear();
        Node* cur = other.head;
        while (cur) 
        {
            push_back(cur->val);
            cur = cur -> next;
        }
    }
    return *this;
}

template<typename T>
mystl::List<T>& mystl::List<T>::operator=(List<T>&& other)
{
    if(this != &other)
    {
        clear();
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}

template<typename T>
T& mystl::List<T>::front() 
{
    if (!head) 
    {
        throw std::out_of_range("List is empty");
    }
    return head->val;
}

template<typename T>
const T& mystl::List<T>::front() const 
{
    if (!head)
    {
        throw std::out_of_range("List is empty");
    }
    return head->val;
}

template<typename T>
T& mystl::List<T>::back() 
{
    if (!tail) 
    {
        throw std::out_of_range("List is empty");
    }
    return tail->val;
}

template<typename T>
const T& mystl::List<T>::back() const 
{
    if (!tail) 
    {
        throw std::out_of_range("List is empty");
    }
    return tail->val;
}

template<typename T>
bool mystl::List<T>::empty() const noexcept
{
    return head == nullptr;
}

template<typename T>
void mystl::List<T>::clear() noexcept
{
    std::vector<Node*> deleted;
    while(head != nullptr)
    {
        Node* tmp = head;
        bool isDeleted = false;
        for(int i = 0 ; i < deleted.size() ; i++)
        {
            if(tmp == deleted[i])
            {
                isDeleted = true;
                break;
            }
        }
        deleted.push_back(tmp);
        if(isDeleted)
        {
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = head -> next;
        delete tmp;
        tmp = nullptr;
    }
    head = nullptr;
    tail = nullptr;
    deleted.clear();
    return;
}

template<typename T>
std::size_t mystl::List<T>::size() const
{
    Node* tmp = head;
    std::size_t s = 0;
    while(tmp != nullptr)
    {
        s++;
        tmp = tmp -> next;
    }
    return s;
}

template<typename T>
void mystl::List<T>::push_back(const T& val)
{
    Node* ptr = new Node(val);
    if(tail == nullptr)
    {
        head = ptr;
        tail = ptr;
    }
    else
    {
        tail -> next = ptr;
        ptr -> prev = tail;
        ptr -> next = nullptr;
        tail = ptr;
    }
}

template<typename T>
void mystl::List<T>::pop_back()
{
    if(tail == nullptr)
    {
        throw std::runtime_error("List is empty. Cannot pop from an empty list.");
    }
    else
    {
        if(head == tail)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node* tmp = tail;
            tail = tail -> prev;
            tail -> next = nullptr;
            delete tmp;
        }
    }
}

template<typename T>
void mystl::List<T>::push_front(const T& val)
{
    Node* ptr = new Node(val);
    if(head == nullptr)
    {
        head = ptr;
        tail = ptr;
    }
    else
    {
        head -> prev = ptr;
        ptr -> next = head;
        ptr -> prev = nullptr;
        head = ptr;
    }
}

template<typename T>
void mystl::List<T>::pop_front()
{
    if(head == nullptr)
    {
        throw std::runtime_error("List is empty. Cannot pop from an empty list.");
    }
    else
    {
        if(head == tail)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node* tmp = head;
            head = head -> next;
            head -> prev = nullptr;
            delete tmp;
        }
    }
}

template<typename T>
void mystl::List<T>::insert(std::size_t pos, const T& val)
{
    Node* ptr= new Node(val);
    if(pos == 0)
    {
        push_front(val);
        return;
    }
    Node* tmp = head;
    for(std::size_t i = 0 ; i < pos ; i++)
    {
        if(tmp == nullptr)
        {
            throw std::runtime_error("List is smaller. Can't do insertion");
        }
        tmp = tmp -> next;
    }
    if (tmp == nullptr)
    {
        push_back(val);
    }
    else
    {
        Node* prevNode = tmp->prev;
        ptr->next = tmp;
        ptr->prev = prevNode;
        if (prevNode)
        {
            prevNode->next = ptr;
        }
        tmp->prev = ptr;
    }
    return;
}

template<typename T>
void mystl::List<T>::erase(std::size_t pos)
{
    if (pos == 0)
    {
        pop_front();
        return;
    }
    Node* tmp = head;
    for (std::size_t i = 0; i < pos; i++)
    {
        if (tmp == nullptr)
        {
            throw std::runtime_error("List is smaller. Can't do erase");
        }
        tmp = tmp->next;
    }
    if (tmp == nullptr)
    {
        pop_back();
    }
    else
    {
        Node* prevNode = tmp->prev;
        Node* nextNode = tmp->next;
        if (prevNode)
        {
            prevNode->next = nextNode;
        }
        if (nextNode)
        {
            nextNode->prev = prevNode;
        }
        delete tmp;
    }
}

template<typename T>
void mystl::List<T>::print() const
{
    std::vector<Node*> printed;
    Node* tmp = head;
    while(tmp != nullptr)
    {
        std::cout << tmp -> val << " ";
        bool isPrinted = false;
        for(int i = 0 ; i < printed.size() ; i++)
        {
            if(tmp == printed[i])
            {
                isPrinted = true;
                break;
            }
        }
        printed.push_back(tmp);
        if(isPrinted)
        {
            std::cout << std::endl;
            return;
        }
        tmp = tmp -> next;
    }
    std::cout << std::endl;
    printed.clear();
    return;
}

template<typename T>
void  mystl::List<T>::createLoop(std::size_t pos)
{
    std::size_t ind = 0;
    Node* ptr = nullptr;
    Node* tmp = head;
    while(tmp != nullptr)
    {
        if(ind == pos)
        {
            ptr = tmp;
            break;
        }
        tmp = tmp -> next;
        ind++;
    }
    if(ptr == nullptr)
    {
        std::cout << "Couldn't create cycle" << std::endl;
        return;
    }
    tail -> next = ptr;
    ptr -> prev = tail;
    return;
}

template<typename T>
bool mystl::List<T>::hasLoop() const
{
    Node* ptr1 = head;
    Node* ptr2 = head;
    while(ptr1 && ptr2 && ptr2 -> next)
    {
        ptr1 = ptr1 -> next;
        ptr2 = ptr2 -> next -> next;
        if(ptr1 == ptr2)
        {
            return true;
        }
    }
    return false;
}

template<typename T>
void mystl::List<T>::reverseList()
{
    if(head != tail)
    {
        Node* tmp = head;
        head = tail;
        Node* first = head;
        while(first != nullptr)
        {
            std::swap(first -> prev , first -> next);
            first = first -> next;
        }
        tail = tmp;
    }
    return;
}

template<typename T>
const T& mystl::List<T>::findNthlastElem(std::size_t n) const
{
    Node* tmp = tail;
    for(std::size_t i = 0 ; i < n ; i++)
    {
        if(tmp == nullptr)
        {
            throw std::out_of_range("List size is smaller than the element");
        }
        tmp = tmp -> prev;
    }
    return tmp -> val;
}

template<typename T>
T& mystl::List<T>::begin() noexcept
{
    return *head;
}

template<typename T>
const T& mystl::List<T>::begin() const noexcept
{
    return *head;
}

template<typename T>
const T& mystl::List<T>::cbegin() const noexcept
{
    return *head;
}

template<typename T>
mystl::List<T>::~List()
{
    clear();
}
#endif //LIST_H