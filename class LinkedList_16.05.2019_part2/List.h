#pragma once
#include<iostream>
#include<string>
#include<exception>//!!!
using namespace std;

//для улавливания ошибок
class my_exception : public exception {//наледуем от готового класса
public:
	virtual const char* what() const throw() //просто перегружаем метод what()
	{
		return "out of range\n";
	}
	int ErrorCode() {//прописываем свой метод ErrorCode()
		return 404;
	}
}my_ex;

//готовый класс
out_of_range lower("out of lower bound");
out_of_range upper("out of upper bound");

//exception e; //then use "throw e"

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
	List(const List&obj);
	~List();
	int getSize();
	T& operator[](int index);
	void push_back(T el);
	void push_front(T el);
	void insert_by_pos(T el, int pos);
	void pop_front();
	void pop_back();
	void del_by_pos(int pos);
	void dump();

};

template<typename T>
inline List<T>::List()
{
	firstPtr = lastPtr = NULL;
	size = 0;
}

template<typename T>
inline List<T>::List(const List & obj)
{
	Node*cur_ptr = obj.firstPtr;

	while (cur_ptr != obj.lastPtr->getNextPtr()) {
		push_back(cur_ptr->getEl());
		cur_ptr = cur_ptr->getNextPtr();
	}
}

template<typename T>
inline List<T>::~List()
{
	int general_size = size;//tmp size because size is changing every time
	for (int i = 0; i < general_size; i++)
		pop_front();
	firstPtr = lastPtr = 0;
}

template<typename T>
inline int List<T>::getSize()
{
	return size;
}

template<typename T>
inline T& List<T>::operator[](int index)throw()//значит собираемся обработать ошибку
{
	int counter = 0;
	Node*cur_ptr = firstPtr;
	//если индекс выходит за пределы списка
	if (index >= size) {//обработка исключений
		//throw my_ex;//обработай ошибку типа my_ex
		throw upper;
	}
	else if (index < 0)
		throw lower;
	else {
		//var 1
		//while (cur_ptr != lastPtr) {//проверка до ЛастПтр

		//	if (counter == index)
		//		return cur_ptr->getEl();
		//	cur_ptr = cur_ptr->getNextPtr();
		//	counter++;
		//}
		//if (counter == index) return cur_ptr->getEl();//проверка на ЛастПтр

		//var2
		while (cur_ptr != lastPtr->getNextPtr()) {//здесь сразу включая самый последний элемент

			if (counter == index)
				return cur_ptr->getEl();
			cur_ptr = cur_ptr->getNextPtr();
			counter++;
		}
	}
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
		lastPtr->getNextPtr() = ptr;//в действующем ластПтр переназначаем внутренний некстПтр на Птр, чтобы он указывал на новый ЛастПтр
		lastPtr = ptr;//переназначение самого указателя на объект, т.е. появляется новый ЛастПтр
	}
	size++;
}

template<typename T>
inline void List<T>::push_front(T el)
{
	Node *cur_ptr = new Node(el, firstPtr);//при создании сразу задаем что некстПтр нового каррент птр = старый ферстПтр
	firstPtr = cur_ptr;
	size++;
	if (size == 1)//т.е. список был пустой и после добавления всего один элемент содержит
			lastPtr = firstPtr;
}

template<typename T>
inline void List<T>::insert_by_pos(T el, int pos)throw()
{
	Node *cur_ptr = firstPtr;
	int counter = 0;

	if (pos == 0)
		push_front(el);
	else if (pos == size)
		push_back(el);
	//обработка исключений
	else if (pos<0 || pos>size)
		throw out_of_range("out of range\n");
	else if (pos > 0 && pos < size) {
		while (counter != pos - 1) {//до предыдущего идем, т.е. занимаем позицию между pos-1 и pos
			cur_ptr = cur_ptr->getNextPtr();
			counter++;
		}
		Node *newPtr = new Node(el, NULL);//указатель на новый узел, содержащий элемент типа Т и пустой указатель

		newPtr->getNextPtr() = cur_ptr->getNextPtr();//пустой указатель будет указывать на текущий Node[pos], который становится Node[pos+1]
		cur_ptr->getNextPtr() = newPtr;//Node[pos-1] будет указывать на добавленный узел, который теперь стал Node[pos]
		
		size++;
	}
	else
		cout << "Unacceptable position" << endl;
}

template<typename T>
inline void List<T>::pop_front()
{
	if (size != 0)//list is not empty
	{
		Node* cur_ptr = firstPtr;
		firstPtr = firstPtr->getNextPtr();
		delete cur_ptr;
		size--;
	}
	else
		cout << "Trying to delete from empty list" << endl;
}

template<typename T>
inline void List<T>::pop_back()
{
	if (size != 0) {
		Node*cur_ptr = firstPtr;
		Node*tmp_lastPtr = lastPtr;//сохраняем ластПтр
		while (cur_ptr->getNextPtr() != lastPtr) {//идем до последнего и когда доходим до него, то в цикл больше не войдем, т.е. остановимся на ПРЕДпоследнем
			cur_ptr = cur_ptr->getNextPtr();//переставляем на следующий
		}
		lastPtr = cur_ptr;//переставляем ластПтр на ПРЕДпоследний
		delete tmp_lastPtr;//удаляем сам старый ЛастПтр, т.е. область памяти под ним
		size--;
	}
	else
		cout << "Trying to delete from empty list" << endl;
}

template<typename T>
inline void List<T>::del_by_pos(int pos)
{
	if (size != 0) {
		if (pos == 0)
			pop_front();
		else if (pos == size-1)
			pop_back();
		//обработка исключений
		else if (pos<0 || pos>=size)
			throw out_of_range("out of range\n");
		else if (pos > 0 && pos < size) {

			Node*cur_ptr = firstPtr;
			int counter = 0;

			while (counter != pos-1) {
				cur_ptr = cur_ptr->getNextPtr();
				counter++;
			}
			Node* tmp_ptr = cur_ptr->getNextPtr();
			//здесь важно, что переставляем не сам указатель cur_ptr,а именно указатель возвращаемый от него функцией getNextPtr()! Это два совершенно разных указателя
			cur_ptr->getNextPtr() = cur_ptr->getNextPtr()->getNextPtr();
			
			delete tmp_ptr;
			size--;
		}
	}
	else
		cout << "Trying to delete from empty list" << endl;
}

template<typename T>
inline void List<T>::dump()
{
	if (size != 0)
	{
		Node*ptr = firstPtr;
		while (ptr != lastPtr->getNextPtr()) {
			cout << ptr->getEl() << endl;
			ptr = ptr->getNextPtr();
		}
	}
}
