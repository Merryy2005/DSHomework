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

int List::GetItem(int ind) const
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

void List::BubbleSort()
{
    for(int i = 0 ; i < size ; i++)
    {
        Node* cur = head;
        for(int j = i+1 ; j < size; j++)
        {
            Node* cur1 = cur -> next;
            if(cur -> data > cur1 -> data)
            {
                std::swap(cur -> data , cur1 -> data);
            }
            cur = cur1;
        }
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
