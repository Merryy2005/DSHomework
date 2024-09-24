#include "Polynom.h"

Polynom::Polynom() : head(nullptr) , size(0) {}

Polynom::Polynom(int* a, int n) : head(nullptr) , size(0)
{
    Node* p = nullptr;
    for(int i = 0 ; i < n; i++)
    {
        InsertAfter(p , a[i] , n-i-1);
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
		
Polynom::Polynom(const Polynom& other) : head(nullptr) , size(0)
{
    Node* cur = other.head;
    Node* p = nullptr;
    while(cur)
    {
        InsertAfter(p , cur -> coef , cur -> pow);
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

Polynom::~Polynom()
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

int Polynom::GetCoef(int ind) const
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
    return cur -> coef;
}

int Polynom::GetPow(int ind) const
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
    return cur -> pow;
}

void Polynom::InsertAfter(Node* ptr , int c , int p)
{
    Node* tmp = new Node(c , p);
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

Polynom Polynom::operator-(const Polynom& other) const
{
    Polynom res;
    if(this -> size == other.size)
    {
        Node* p = nullptr;
        for(int i = 0 ; i < this->size ; i++)
        {
            res.InsertAfter(p , this->GetCoef(i) - other.GetCoef(i) , ((this->size)-i-1));
            if(!p)
            {
                p = res.head;
            }
            else
            {
                p = p -> next;
            }
        }
        return res;
    }
    if(this -> size > other.size)
    {
        int dif = this -> size - other.size;
        int x = this -> size - 1;
        Node* p = nullptr;
        for(int i = 0 ; i < dif ; i++)
        {
            res.InsertAfter(p , this->GetCoef(i), x--);
            if(!p)
            {
                p = res.head;
            }
            else
            {
                p = p -> next;
            }
        }
        for(int i = 0 ; i < other.size ; i++)
        {
            res.InsertAfter(p , this->GetCoef(i + dif) - other.GetCoef(i), x--);
            if(!p)
            {
                p = res.head;
            }
            else
            {
                p = p -> next;
            }
        }
        return res;
    } 
    int dif = other.size - this->size;
    int x = other.size-1;
    Node* p = nullptr;
    for(int i = 0 ; i < dif ; i++)
    {
        res.InsertAfter(p , -other.GetCoef(i), x--);
        if(!p)
        {
            p = res.head;
        }
        else
        {
            p = p -> next;
        }
    }
    for(int i = 0 ; i < this->size ; i++)
    {
        res.InsertAfter(p , this->GetCoef(i) - other.GetCoef(i+dif), x--);
        if(!p)
        {
            p = res.head;
        }
        else
        {
            p = p -> next;
        }
    }
    return res;
}

void Polynom::print() const 
{
    Node* cur = head;
    while (cur) 
    {
        if (cur->coef != 0) 
        {
            if (cur != head && cur->coef > 0) 
            {
                std::cout << " + ";
            }
            std::cout << cur->coef;
            if (cur->pow > 0) 
            {
                std::cout << "x^" << cur->pow;
            }
        }
        cur = cur->next;
    }
    std::cout << std::endl;
}
