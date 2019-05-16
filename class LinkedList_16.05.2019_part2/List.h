#pragma once
#include<iostream>
#include<string>
using namespace std;

template<typename T>
class List {
private:
	//внтуренний класс
	class Node {//узелок
		T el;
		Node* nextPtr;
	public:
		Node(T el, Node*nextPtr) {
			this->el = el;
			this->nextPtr = nextPtr;
		}
		T& getEl() {return el;}
		Node*& getNextPtr() {return nextPtr;}

		void setEl(T el) {this->el = el;}
		void setNextPtr(T* ptr) {this->nextPtr = ptr;}

	};

	Node *firstPtr, *lastPtr;//!!! *
	int size;

public:
	List();
	int getSize();
	void push_back(T el);
	void dump();

};

template<typename T>
inline List<T>::List()
{
	firstPtr = lastPtr = NULL;
	size = 0;
}

template<typename T>
inline int List<T>::getSize()
{
	return size;
}

template<typename T>
inline void List<T>::push_back(T el)
{
	if (size == 0) {
		Node* ptr = new Node(el, NULL);//выделяем место для нового элемента, у которого оба указателя указывают на один и тот же единственный элемент:
		firstPtr = lastPtr = ptr;
	}
	else {
		Node* ptr = new Node(el, NULL);
		lastPtr->getNextPtr() = ptr;//выделяем место в памяти и связываем новый элемент с предыдущим??
		lastPtr = ptr;//переназначение указателя
	}
	size++;
}

template<typename T>
inline void List<T>::dump()
{
	Node*ptr = firstPtr;
	while (ptr != lastPtr->getNextPtr()) {
		cout << ptr->getEl() << endl;
		ptr = ptr->getNextPtr();
	}
}
