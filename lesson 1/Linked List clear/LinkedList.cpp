#pragma once
#ifndef _LinkedList_
#define _LinkedList_

#include "LinkedList.h"

template <typename T>
List<T>::List(const List& newElem) {
	std::cout << "--- insight copy constructor ---" << std::endl;
	copyList(*this, newElem);
}

template <typename T>
List<T>::List(std::initializer_list<T> val) {
	for (const auto& valTemp : val) {
		push(valTemp);
	}
}

template <typename T>
List<T>::List(List&& moveElem) noexcept : List() {
	std::cout << "-- moveConst --" << std::endl;
	swapList(*this, moveElem);
}


template <typename T>
List<T>::~List() {
	std::cout << "--- insight destructor ---" << std::endl;
	releaseList();
}

template <typename T>
void List<T>::releaseList() {
	Node<T>* currendNode = head;
	while (currendNode) {
		Node<T>* tempNode = currendNode->next;
		delete currendNode;
		currendNode = tempNode;
	}
	head = nullptr;
	tail = nullptr;
	size = 0;
}


template <typename T>
void List<T>::push(const T& value) {
	std::cout << " --- PUSH ---" << std::endl;
	Node<T>* temp = new Node<T>(value);
	if (head == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
	size++;
}

template <typename T>
void List<T>::pop() {
	deleteElement_byIndex(size - 1, true);
}

template <typename T>
void List<T>::deleteElement_byIndex(const int index, bool reverseIterator) {
	if (head != nullptr && index < size && index >= 0) {
		Node<T>* element = findElement_byIndex(index, reverseIterator);
		if (element->prev != nullptr) {
			element->prev->next = element->next;
		}
		else {
			head = element->next;
		}
		if (element->next != nullptr) {
			element->next->prev = element->prev;
		}
		else {
			tail = element->prev;
		};
		delete element;
		--size;
	}
}

template <typename T>
void List<T>::deleteElement_byIndex(std::vector<int> values) {
	if (values.empty() != true) {
		for (int vecIndex = 0; vecIndex < values.size(); vecIndex++) {
			if (values.size() == 1) {
				deleteElement_byIndex(values[vecIndex], false);
			}
			else {
				if (values[vecIndex] >= size / 2) {
					deleteElement_byIndex(values[vecIndex], true);
				}
				else {
					deleteElement_byIndex(values[vecIndex], false);
				}
				if (vecIndex != values.size() - 1) {
					if (values[vecIndex] < values[vecIndex + 1]) {
						for (int vecIndex_ = vecIndex + 1; vecIndex_ < values.size(); vecIndex_++) {
							values[vecIndex_] = values[vecIndex_] - 1;
						}
					}
				}
			}
		}
	}
}

template <typename T>
void List<T>::deleteElement_byValue(const int& val, bool allElem) {
	int countIndex = 0;
	Node<T>* currentElem = head;

	while (currentElem != nullptr) {
		if (currentElem->value == val) {
			currentElem = currentElem->next;
			deleteElement_byIndex(countIndex, false);
			if (allElem == false) { break; }
		}
		else {
			currentElem = currentElem->next;
			countIndex++;
		}
	}
}

template <typename T>
Node<T>* List<T>::findElement_byIndex(const int index, bool reverseIterator) {
	if (index < size && index >= 0) {
		if (reverseIterator == false) {
			int countIndex = 0;
			for (Node<T>* currentElem = head; currentElem != nullptr; currentElem = currentElem->next) {
				if (countIndex++ == index) {
					return currentElem;
				}
			}
		}
		else {
			int countIndex = size - 1;
			for (Node<T>* currentElem = tail; currentElem != nullptr; currentElem = currentElem->prev) {
				if (countIndex-- == index) {
					return currentElem;
				}
			}
		}
	}
	else { return nullptr; }
}

template <typename T>
std::vector<int> List<T>::findElement_byValue(const T& val) const {
	std::vector<int> indecies{};
	int countIndex = 0;
	for (const Node<T>* currentElem = head;
		currentElem != nullptr; currentElem = currentElem->next, countIndex++) {
		if (currentElem->value == val) {
			indecies.push_back(countIndex);
		}
	}
	return indecies;
}

template <typename T>
std::size_t List<T>::sizef() const { return size; }

template <typename T>
void List<T>::reverse() {
	List<T> tempList(*this);
	releaseList();
	for (const Node<T>* currentElem = tempList.tail; currentElem != nullptr; currentElem = currentElem->prev) {
		push(currentElem->value);
	}
	tempList.releaseList();
}
template <typename T>
void List<T>::swapList(List<T>& first, List<T>& second) {
	std::swap(first.head, second.head);
	std::swap(first.tail, second.tail);
	std::swap(first.size, second.size);
}


template <typename T>
List<T>& List<T>::copyList(List<T>& destination, const List<T>& right) {
	destination.releaseList();
	if (right.head != nullptr) {
		for (const Node<T>* currentElem = right.head; currentElem != nullptr; currentElem = currentElem->next) {
			destination.push(currentElem->value);
		}
	}
	return destination;
}

template <typename T>
void List<T>::printElements() const {
	if (head != nullptr) {
		for (const Node<T>* currentElem = head; currentElem != nullptr; currentElem = currentElem->next) {
			std::cout << currentElem->value << " , ";
		}
		std::cout << std::endl;
	}
}

template <typename T>
List<T>& List<T>::operator+=(const List& right) {
	for (const Node<T>* currentElem = right.head; currentElem != nullptr; currentElem = currentElem->next) {
		push(currentElem->value);
	}
	size += right.size;
	return *this;
}

template <typename T>
bool List<T>::operator==(const List& right) const {
	if (size == right.sizef()) {
		Node<T>* rightTemp = right.head;
		for (auto left = head; left != nullptr; left = left->next, rightTemp = rightTemp->next) {
			if (left->value != rightTemp->value) { return false; }
		}
		return true;
	}
	else { return false; }
}

template <typename T>
bool List<T>::operator!=(const List& right) const {
	if (size == right.sizef()) {
		Node<T>* rightTemp = right.head;
		for (auto left = head; left != nullptr; left = left->next, rightTemp = rightTemp->next) {
			if (left->value != rightTemp->value) { return true; }
		}
		return false;
	}
	else { return true; }
}

template <typename T>
List<T> List<T>::operator+(const List<T>& right) {
	std::cout << "insight operator+ ---------" << std::endl;
	List<T> temp(*this);
	for (const Node<T>* currentElem = right.head; currentElem != nullptr; currentElem = currentElem->next) {
		temp.push(currentElem->value);
	}
	return temp;
}
template <typename T>
List<T>& List<T>::operator=(List right) {
	std::cout << "--- copy assignment ---" << std::endl;
	swapList(*this, right);
	return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& right) noexcept {
	std::cout << "--- move assignment ---" << std::endl;
	swapList(*this, right);
	return *this;
}

template <typename T>
T List<T>::operator[](const int index) {
	Node<T>* eleme = findElement_byIndex(index, false);
	return eleme->value;
}
template <typename T>
void* List<T>::operator new(size_t count) { //size_t: positiv integer
	void* p = std::malloc(sizeof(List) * count);
	return p;
}
#endif

/*
template <typename T>
void List<T>::operator delete(void* p) {
	std::free(p);
}
*/
/*
template <typename T>
List<T>& List<T>::operator*(List* ptr) {
	List<T> tempList;
	tempList.head = ptr->head;
	tempList.tail = ptr->tail;
	return tempList;
}
*/
/*
int main() {
	List <int> x;
	//List <int> y(x);
	List <int> k;
	k.push(4);
	k.push(8);
	k.push(9);
	k.push(2);
	std::cout << std::endl;
	// test: pop function --------  >> works --------------------------------
	std::cout << "popfunction" << std::endl;
	k.pop();
	k.printElements();
	std::cout << std::endl;
	x.push(4);
	x.push(8);
	x.push(8);
	x.push(3);
	x.push(9);
	x.printElements();

	std::cout << std::endl;

	List<int> test({ 1,2,3,4,5,6,9,9,9 });
	test.printElements();
	test.pop();
	test.printElements();

	std::cout << std::endl;

	//test.deleteElement_byValue(5);
	//test.deleteElement_byValue(9);
	//test.printElements();

	std::cout << std::endl;

	std::cout << "test reversefunction -----------" << std::endl;
	test.reverse();
	test.printElements();

	std::cout << std::endl;

	List<int> tt({ 1,2,9,4,1,9,9,7,8 });
	tt.printElements();
	tt.deleteElement_byValue(9, true);
	std::cout << std::endl;
	tt.printElements();
	std::cout << std::endl;
	std::cout << std::endl;

	// test deletElement_byIndex(vector) ---------  works -------
	std::cout << "test deleteElement by indecies VECTOR -----------" << std::endl;
	List<int> hh({ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 });
	hh.printElements();
	std::vector<int> indicies({ 9,0 });
	hh.deleteElement_byIndex(indicies);
	std::cout << std::endl;
	hh.printElements();

	// test swap -------
	List<int> sw({ 2,2,2,2,2 });
	List<int> swsw({ 9,9,9,9,9 });
	sw.printElements();
	swsw.printElements();

	// works ------------------------------------------------------------
	std::cout << std::endl;
	List<int>::swapList(sw, swsw);
	sw.printElements();
	swsw.printElements();

	// works ------------------------------------------------------------
	std::cout << std::endl;
	std::cout << "--- assignment test -----------" << std::endl;
	sw = swsw;
	sw.printElements();
	std::cout << std::endl;

	// works ------------------------------------------------------------
	std::cout << "--- operator+ test -----------" << std::endl;
	List<int> TTT = sw + swsw;
	std::cout << "--- start -----------" << std::endl;
	TTT.printElements();
	std::cout << "--- end -----------" << std::endl;
	// works ------------------------------------------------------------
	std::cout << "--- [] operator -----------" << std::endl;
	std::cout << TTT[2] << std::endl;

	List<int>* newList = new List<int>();
	newList->push(5);
	newList->push(5);
	newList->push(5);
	newList->push(5);
	newList->printElements();
	newList->testPrint();



	//std::cout << "test << Operator -----------" << std::endl;
	//std::cout << test << std:endl;
	//std::cout << "+ operator -----------" << std::endl;
	//List<int> zz;
	//zz = test + k;
	//zz.printElements();
	//cout << " x size " << x.sizef() << endl; // same size after pop
	// test: delate by index >> works ---------------------------------
	//x.printElements();
	//cout << " --- test delete_byIndex function ------" << endl;
	//x.deleteElement_byIndex(0);
	//x.printElements();


// test: deleteElement_byValue funciton  ----- ---------------------------------------------------------------------------------------------------

	//cout << " --- test deleteElement_byValue function ------" << endl;
	//x.deleteElement_byValue(8);
	//x.printElements();
/*
	// test: findElement_byValue()  ------------------ works ---------------------------------------------
	cout << " --- test findElement function ------" << endl;
	vector<int> test = x.findElement_byValue(8);
	for (int i = 0; i < test.size(); i++) {
		cout << test[i] << endl;
	}
	if (test.size() == 0) { cout << "Element not found" << endl; }
	*//**
	//--------------------------------------------------------------------
	cout << " --- test fsize function ------" << endl;
	int s = x.sizef();
	cout << "size == " << s << endl;

	//------------------- works ------------------------------------------------
	cout << " --- test += operator ------" << endl;
	List<int> xx;
	xx.push(1);
	xx.push(1);
	xx.push(1);
	xx.push(1);
	x += k;
	x.printElements();


	//------------------ approved --------------------------------------------------
	cout << " --- test == operator ------" << endl;
	List <int> u;
	u.push(1);
	u.push(4);
	List <int> p;
	p.push(1);
	p.push(4);
	cout << "PPPPPPPPP\n";
	p.printElements();
	if (u == p) { cout << "equal" << endl; }
	else { cout << "not equal" << endl; }
	cout << "PPPPPPPPP\n";
	p.printElements();

	List<int> xxx(xx);
	xxx.printElements();

	//p.reverse();
	//p.printElements();
	cout << "----------- Test = operator ---------------------" << endl;
	k.printElements();
	cout << endl;
	x.printElements();
	cout << endl;
	x = k;
	x.printElements();
	cout << endl;
	k.printElements();

	// test: copy constructor -----------------------------------------
	cout << "--------- test move constructor ---------" << endl;
	List<int> l();
	p = l();
	p.printElements();
	// test: = operator  -----------------------------------------
	cout << "--------- test operator =  ---------" << endl;
	x.printElements();
	x = k;
	cout << "print after = " << endl;
	x.printElements();
	*/