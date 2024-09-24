#include "List.h"

List::List() : head(nullptr) , size(0) {}

List::List(int* a, int n) : head(nullptr) , size(0)
{
    Node* p = nullptr;
    for(int i = 0 ; i < n; i++)
    {
        InsertAfter(p , a[i]);
        if(!p)
        {
            p = head;
        }
        else
        {
            p = p -> next;
        }
    }
}
		
List::List(const List& other) : head(nullptr) , size(0)
{
    Node* cur = other.head;
    Node* p = nullptr;
    while(cur)
    {
        InsertAfter(p , cur -> data);
        cur = cur -> next;
        if(!p)
        {
            p = head;
        }
        else
        {
            p = p -> next;
        }
    }
}

List::~List()
{
    Node* cur = head;
    while(cur)
    {
        Node* tmp = cur -> next;
        delete cur;
        cur = tmp;
    }
    head = nullptr;
    size = 0;
}

int List::Search(int ind) const
{
    if(ind < 0 || ind >= size)
    {
        throw std::out_of_range("Wrong index");
    }
    Node* cur = head;
    for(int i = 0 ; i < ind ; i++)
    {
        cur = cur -> next;
    }
    return cur -> data;
}

void List::InsertAt(int ind , int d)
{
    if (ind < 0 || ind >= size)
    {
        throw std::out_of_range("Wrong index");
    }
    Node* p = head;
    if (ind == 0)
    {
        Node* q = new Node(d);
        q -> next = head;
        head = q;
        size++;
    }
    else
    {
        for (int i = 0; i < ind - 1; i++)
        {
            p = p -> next;
        }
        InsertAfter(p , d);
    }
}

void List::InsertAfter(Node* ptr , int d)
{
    Node* tmp = new Node(d);
    if(!ptr)
    {
        head = tmp;
    }
    else{
        tmp -> next = ptr -> next;
        ptr -> next = tmp;
    }
    size++;
}

void List::DeleteAt(int ind)
{
    if (ind < 0 || ind >= size)
    {
        throw std::out_of_range("Wrong index");
    }
    Node* p = head;
    if (ind == 0)
    {
        head = head->next;
        delete p;
        size--;
    }
    else
    {
        for (int i = 0; i < ind - 1; i++)
        {
            p = p -> next;
        }
        DeleteAfter(p);
    }
}

void List::DeleteAfter(Node* ptr)
{
    if (!ptr || !ptr->next)
    {
        return;
    }
    Node* tmp = ptr->next; 
    ptr->next = tmp->next;
    delete tmp;
    size--;
}

void List::AddElem(int d)
{
    bool check = false;
    for(int i = 0 ; i < size ; i++)
    {
        if(Search(i) == d)
        {
            check = true;
            InsertAt(i , d);
            break;
        }
    }
    if(!check)
    {
        InsertAt(0 , d);
    }
    return;
}

void List::print() const 
{
    Node* cur = head;
    while (cur) 
    {
        std::cout << cur -> data << " ";
        cur = cur -> next;
    }
    std::cout << std::endl;
}
