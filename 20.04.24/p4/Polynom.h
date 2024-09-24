#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>

class Polynom
{
	class Node
	{
        private:
            int coef;
            int pow;
            Node* next;
        public:
            Node() : coef(1) , pow(0) , next(nullptr){}
            Node(int c , int p) : coef(c) , pow(p) , next(nullptr) {}
        friend Polynom;
	};

	private:
		Node* head;
		int size;
	public:
		Polynom();
		Polynom(int*, int);
		Polynom(const Polynom&);
		~Polynom();
        int GetCoef(int) const;
        int GetPow(int) const;
        void InsertAfter(Node* , int , int);
		Polynom operator-(const Polynom&) const;
		void print() const;
};

#endif