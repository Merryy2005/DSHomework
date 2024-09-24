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
        int GetItem(int) const;
        void InsertAfter(Node* , int);
        void BubbleSort();
		void print() const;
};

#endif