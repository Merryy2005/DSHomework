#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <algorithm>

class List
{
	class Node
	{
        private:
            int data;
            Node* next;
        public:
            Node() : data(0), next(nullptr){}
            Node(int d) : data(d) , next(nullptr) {}
        friend List;
	};

	private:
		Node* head;
		int size;
	public:
		List();
		List(int*, int);
		List(const List&);
		~List();
        int Search(int) const;
        void InsertAt(int , int);
        void InsertAfter(Node* , int);
        void DeleteAt(int);
        void DeleteAfter(Node*);
        void AddElem(int);
		void print() const;
};

#endif